define-class SSO-Heatmap-Blip
    'row   : 0
    'col   : 0
    'color : 0x000000
    'char  : ""

    'new :
        fn (&row &col &color)
            blip = (new-instance SSO-Heatmap-Blip)

            (blip 'row)   = &row
            (blip 'col)   = &col
            (blip 'color) = &color

            move blip

    'paint :
        fn (&self &view &vert-offset)
            @term:set-cell-bg
                ((&self 'row) + &vert-offset)
                (&self 'col)
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
                color  = (select (value == 0.0) 0x000000 ((sint ((value * 225) + 30)) << 16))

                append (map 'blips)
                    (SSO-Heatmap-Blip 'new) row col color

                if (row == (&start-row + 1))
                    row = (&start-row + &grid-height)
                    col += 1
                else
                    row -= 1

            move map

    'paint :
        fn (&self &view &vert-offset)
            (&self 'vert-offset) = &vert-offset
            row = ((&self 'start-row) + &vert-offset)
            c = 1
            foreach char (chars (&self 'event))
                @term:set-cell-fg   row c 0xffffff
                @term:set-cell-char row c char
                c += 1
            foreach &blip (&self 'blips)
                &blip @ ('paint &view &vert-offset)

    'coord-to-blip-idx :
        fn (&self &view &row &col)
            &grid-height = (&self 'grid-height)
            start-row = (((&self 'start-row) + (&view 'vert-offset)) + 1)
            start-col = 1
            ((&col - start-col) * &grid-height) + ((&grid-height - 1) + (start-row - &row))

    'set-blip-color-mask :
        fn (&self &view &idx &mask)
            &blip = ((&self 'blips) &idx)
            (&blip 'color) |= &mask
            &blip @ ('paint &view (&self 'vert-offset))

    'reset-blip-color :
        fn (&self &view &idx)
            &blip = ((&self 'blips) &idx)
            (&blip 'color) &= 0xffff00
            &blip @ ('paint &view (&self 'vert-offset))

    'get-selected-range :
        fn (&self)
            &a = (&self 'anchor-idx)
            &t = (&self 'tail-idx)
            select (&a <= &t)
                &a : ((&t - &a) + 1)
                &t : ((&a - &t) + 1)

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

            (&self 'state) = 'no-selection

    'mouse-over :
        fn (&self &view &row &col)
            response = nil
            start-row = (((&self 'start-row) + (&view 'vert-offset)) + 1)
            if ((&row >= start-row) and (&row < ((&self 'grid-height) + start-row)))
                idx = (&self @ ('coord-to-blip-idx &view &row &col))
                if (idx < (len (&self 'blips)))
                    match (&self 'state)
                        'no-selection
                            (&self 'anchor-idx) = idx
                            &self @ ('set-blip-color-mask &view idx 0x0000b0)

                            (&self 'state) = 'anchor-hover

                        'anchor-hover
                            &self @ ('reset-blip-color &view (&self 'anchor-idx))
                            &self @ ('set-blip-color-mask &view idx 0x0000b0)
                            (&self 'anchor-idx) = idx

                        'tail-hover
                            range  = (&self @ ('get-selected-range))
                            start  = (range 0)
                            length = (range 1)

                            if (length > 2)
                                repeat i (length - 2)
                                    i += (start + 1)
                                    &self @ ('reset-blip-color &view i)

                            if ((&self 'tail-idx) != (&self 'anchor-idx))
                                &self @ ('reset-blip-color &view (&self 'tail-idx))

                            if (idx != (&self 'anchor-idx))
                                &self @ ('set-blip-color-mask &view idx 0x00007f)

                            (&self 'tail-idx) = idx

                            range  = (&self @ ('get-selected-range))
                            start  = (range 0)
                            length = (range 1)

                            if (length > 2)
                                repeat i (length - 2)
                                    i += (start + 1)
                                    &self @ ('set-blip-color-mask &view i 0x00007f)

                    @term:flush
            response

    'mouse-click :
        fn (&self &view &row &col)
            response = nil
            start-row = (((&self 'start-row) + (&view 'vert-offset)) + 1)
            if ((&row >= start-row) and (&row < ((&self 'grid-height) + start-row)))
                idx = (&self @ ('coord-to-blip-idx &view &row &col))
                if (idx < (len (&self 'blips)))
                    match (&self 'state)
                        'no-selection
                            (&self 'anchor-idx) = idx
                            (&self 'tail-idx) = idx
                            &self @ ('set-blip-color-mask &view idx 0x0000ff)

                            (&self 'state) = 'tail-hover

                        'anchor-hover
                            (&self 'anchor-idx) = idx
                            (&self 'tail-idx)   = idx
                            &self @ ('set-blip-color-mask &view idx 0x0000ff)

                            (&self 'state) = 'tail-hover

                        'tail-hover
                            (&self 'tail-idx) = idx
                            response = 'range-selected

                    @term:flush
            response
