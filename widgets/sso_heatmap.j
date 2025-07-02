define-class SSO-Heatmap-Blip
    'row   : 0
    'col   : 0
    'color : 0x000000
    'count : 0

    'new :
        fn (&row &col &color &count)
            blip = (new-instance SSO-Heatmap-Blip)

            (blip 'row)   = &row
            (blip 'col)   = &col
            (blip 'color) = &color
            (blip 'count) = &count

            move blip

    'paint :
        fn (&self &view &vert-offset &horiz-offset)
            @term:set-cell-bg
                ((&self 'row) + &vert-offset)
                ((&self 'col) + &horiz-offset)
                (&self 'color)

define-class SSO-Heatmap
    'height      : 0
    'start-row   : 0

    'grid-height : 0
    'blips       : (list)
    'state       : 'no-selection
    'anchor-idx  : nil
    'tail-idx    : nil
    'vert-offset : 0
    'horiz-offset : 0
    'event       : ""

    'new :
        fn (&profile &event &start-row)
            map = (new-instance SSO-Heatmap)

            (map 'grid-height) = (sint (1.0 / (options 'interval-time)))
            (map 'height) = ((map 'grid-height) + 1)
            (map 'start-row) = &start-row
            (map 'event) = &event

            largest-count = 0
            foreach &interval (&profile 'intervals)
                count = 0
                if (&event in (&interval 'events-by-type))
                    foreach &sample ((&interval 'events-by-type) &event)
                        count += (&sample 'count)
                    largest-count = (max largest-count count)
                &interval <- ('eustall-count : count)

            &grid-height = (map 'grid-height)

            row = (&start-row + &grid-height)
            col = 1
            foreach &interval (&profile 'intervals)
                &count = (&interval 'eustall-count)
                value  = (select (largest-count == 0) 0.0 ((float &count) / largest-count))
                color  =
                    0xff0000 |
                        ((sint ((1.0 - value) * 255)) << 8) |
                            sint ((1.0 - value) * 255)

                append (map 'blips)
                    (SSO-Heatmap-Blip 'new) row col color &count

                if (row == (&start-row + 1))
                    row = (&start-row + &grid-height)
                    col += 1
                else
                    row -= 1

            move map

    'paint :
        fn (&self &view &vert-offset &horiz-offset)
            (&self 'vert-offset) = &vert-offset
            (&self 'horiz-offset) = &horiz-offset
            row = ((&self 'start-row) + &vert-offset)
            c = 1
            foreach char (chars (&self 'event))
                @term:set-cell-fg   row c 0xffffff
                @term:set-cell-char row c char
                c += 1
            foreach &blip (&self 'blips)
                &blip @ ('paint &view &vert-offset &horiz-offset)

    'coord-to-blip-idx :
        fn (&self &view &row &col)
            &grid-height = (&self 'grid-height)
            start-row = (((&self 'start-row) + (&view 'vert-offset)) + 1)
            start-col = ((&self 'horiz-offset) + 1)
            ((&col - start-col) * &grid-height) + ((&grid-height - 1) + (start-row - &row))

    'set-blip-color-mask :
        fn (&self &view &idx)
            &blip = ((&self 'blips) &idx)
            (&blip 'color) &= 0x00ffff
            &blip @ ('paint &view (&self 'vert-offset) (&self 'horiz-offset))

    'reset-blip-color :
        fn (&self &view &idx)
            &blip = ((&self 'blips) &idx)
            (&blip 'color) |= 0xff0000
            &blip @ ('paint &view (&self 'vert-offset) (&self 'horiz-offset))

    'get-selected-range :
        fn (&self)
            &a = (&self 'anchor-idx)
            &t = (&self 'tail-idx)

            if (&t == nil)
                range = (&a : 1)
            else
                range =
                    select (&a <= &t)
                        &a : ((&t - &a) + 1)
                        &t : ((&a - &t) + 1)
            move range

    'reset-selection :
        fn (&self &view)
            match (&self 'state)
                'anchor-hover
                    &self @ ('reset-blip-color &view (&self 'anchor-idx))
                    (&self 'anchor-idx) = nil

                'tail-hover
                    range  = (&self @ ('get-selected-range))
                    start  = (range 0)
                    length = (range 1)

                    repeat i length
                        i += start
                        &self @ ('reset-blip-color &view i)

                    (&self 'anchor-idx) = nil
                    (&self 'tail-idx) = nil

                'mirror
                    range  = (&self @ ('get-selected-range))
                    start  = (range 0)
                    length = (range 1)

                    repeat i length
                        i += start
                        &self @ ('reset-blip-color &view i)

                    (&self 'anchor-idx) = nil
                    (&self 'tail-idx) = nil

            (&self 'state) = 'no-selection

    'set-mirror-range :
        fn (&self &view &range)
            &self @ ('reset-selection &view)

            &start  = (&range 0)
            &length = (&range 1)

            repeat i &length
                i += &start
                &self @ ('set-blip-color-mask &view i)

            (&self 'anchor-idx) = &start
            (&self 'tail-idx)   = ((&start + &length) - 1)
            (&self 'state)      = 'mirror

    'mouse-over :
        fn (&self &view &row &col)
            response = nil
            start-row = (((&self 'start-row) + (&view 'vert-offset)) + 1)
            if
                and
                    &row >= start-row
                    &row < ((&self 'grid-height) + start-row)
                    &col >= (1 + (&self 'horiz-offset))

                idx = (&self @ ('coord-to-blip-idx &view &row &col))
                if (idx < (len (&self 'blips)))
                    match (&self 'state)
                        'mirror
                            &self @ ('reset-selection &view)

                            (&self 'anchor-idx) = idx
                            &self @ ('set-blip-color-mask &view idx)
                            (&self 'state) = 'anchor-hover
                            &view @ ('status-text (fmt "Samples: %" (((&self 'blips) idx) 'count)))

                            response = 'range-hover

                        'no-selection
                            (&self 'anchor-idx) = idx
                            &self @ ('set-blip-color-mask &view idx)
                            (&self 'state) = 'anchor-hover
                            &view @ ('status-text (fmt "Samples: %" (((&self 'blips) idx) 'count)))

                            response = 'range-hover

                        'anchor-hover
                            &self @ ('reset-blip-color &view (&self 'anchor-idx))
                            &self @ ('set-blip-color-mask &view idx)
                            (&self 'anchor-idx) = idx
                            &view @ ('status-text (fmt "Samples: %" (((&self 'blips) idx) 'count)))

                            response = 'range-hover

                        'tail-hover
                            range  = (&self @ ('get-selected-range))
                            start  = (range 0)
                            length = (range 1)

                            repeat i length
                                i += start
                                &self @ ('reset-blip-color &view i)

                            if ((&self 'tail-idx) != (&self 'anchor-idx))
                                &self @ ('reset-blip-color &view (&self 'tail-idx))

                            if (idx != (&self 'anchor-idx))
                                &self @ ('set-blip-color-mask &view idx)

                            (&self 'tail-idx) = idx

                            range  = (&self @ ('get-selected-range))
                            start  = (range 0)
                            length = (range 1)
                            count  = 0

                            repeat i length
                                i += start
                                count += (((&self 'blips) i) 'count)
                                &self @ ('set-blip-color-mask &view i)
                                    
                            &view @ ('status-text (fmt "Samples: % | Seconds: %" count (length * (options 'interval-time))))

                            response = 'range-hover

                    @term:flush
            response

    'mouse-click :
        fn (&self &view &row &col)
            response = nil
            start-row = (((&self 'start-row) + (&view 'vert-offset)) + 1)
            if
                and
                    &row >= start-row
                    &row < ((&self 'grid-height) + start-row)
                    &col >= (1 + (&self 'horiz-offset))

                idx = (&self @ ('coord-to-blip-idx &view &row &col))
                if (idx < (len (&self 'blips)))
                    match (&self 'state)
                        'mirror
                            &self @ ('reset-selection &view)

                            (&self 'anchor-idx) = idx
                            (&self 'tail-idx) = idx
                            &self @ ('set-blip-color-mask &view idx)

                            (&self 'state) = 'tail-hover

                            response = 'range-hover

                        'no-selection
                            (&self 'anchor-idx) = idx
                            (&self 'tail-idx) = idx
                            &self @ ('set-blip-color-mask &view idx)

                            (&self 'state) = 'tail-hover

                            response = 'range-hover

                        'anchor-hover
                            (&self 'anchor-idx) = idx
                            (&self 'tail-idx)   = idx
                            &self @ ('set-blip-color-mask &view idx)

                            (&self 'state) = 'tail-hover

                            response = 'range-hover

                        'tail-hover
                            (&self 'tail-idx) = idx
                            response = 'range-selected

                    @term:flush
            response
