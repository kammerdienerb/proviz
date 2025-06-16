define-class SSO-Heatmap-Blip
    'row   : 0
    'col   : 0
    'color : 0x000000


    'new :
        fn (&row &col &color)
            blip = (new-instance SSO-Heatmap-Blip)

            (blip 'row)   = &row
            (blip 'col)   = &col
            (blip 'color) = &color

            move blip

    'paint :
        fn (&self &view)
            @term:set-cell-bg
                (&self 'row)
                (&self 'col)
                (&self 'color)

define-class SSO-Heatmap
    'height     : 0
    'blips      : (list)
    'state      : 'no-selection
    'anchor-idx : nil
    'tail-idx   : nil


    'new :
        fn (&profile &event)
            map = (new-instance SSO-Heatmap)

            (map 'height) = (sint (1.0 / (options 'interval-time)))

            largest-count = 0
            foreach &interval (&profile 'intervals)
                count = 0
                if (&event in (&interval 'events-by-type))
                    foreach &sample ((&interval 'events-by-type) &event)
                        count += (&sample 'count)
                    if (count > largest-count)
                        largest-count = count
                &interval <- ('eustall-count : count)

            &height = (map 'height)

            row = (&height + 1)
            col = 1
            foreach &interval (&profile 'intervals)
                count = (&interval 'eustall-count)
                value = (select (largest-count == 0) 0.0 ((float count) / largest-count))
                color = (select (value == 0.0) 0x000000 ((sint ((value * 225) + 30)) << 16))

                append (map 'blips)
                    (SSO-Heatmap-Blip 'new) row col color

                if (row == 2)
                    col += 1
                    row = (&height + 1)
                else
                    row -= 1

            move map

    'paint :
        fn (&self &view)
            foreach &blip (&self 'blips)
                &blip @ ('paint &view)

    'coord-to-blip-idx :
        fn (&self &row &col)
            ((&col - 1) * (&self 'height)) + (((&self 'height) - &row) + 1)

    'set-blip-color-mask :
        fn (&self &view &idx &mask)
            &blip = ((&self 'blips) &idx)
            (&blip 'color) |= &mask
            &blip @ ('paint &view)

    'reset-blip-color :
        fn (&self &view &idx)
            &blip = ((&self 'blips) &idx)
            (&blip 'color) &= 0xffff00
            &blip @ ('paint &view)

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

                    (&self 'state) = 'no-selection

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
            if ((&row > 1) and (&row <= ((&self 'height) + 1)))
                idx = (&self @ ('coord-to-blip-idx &row &col))
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
            if ((&row > 1) and (&row <= ((&self 'height) + 1)))
                idx = (&self @ ('coord-to-blip-idx &row &col))
                if (idx < (len (&self 'blips)))
                    match (&self 'state)
                        'no-selection
                            (&self 'anchor-idx) = idx
                            &self @ ('set-blip-color-mask &view idx 0x0000ff)

                            (&self 'state) = 'tail-hover

                        'anchor-hover
                            (&self 'anchor-idx) = idx
                            (&self 'tail-idx)   = idx
                            &self @ ('set-blip-color-mask &view idx 0x0000ff)

                            (&self 'state) = 'tail-hover

                        'tail-hover
                            response = 'range-selected

                    @term:flush
            response























