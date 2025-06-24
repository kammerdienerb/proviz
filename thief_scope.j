define-class Thief-Scope-Blip
    'row   : 0
    'col   : 0
    'color : 0x000000


    'new :
        fn (&row &col &color)
            blip = (new-instance Thief-Scope-Blip)

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

define-class Thief-Scope
    'height             : 0
    'width              : 0
    'max-interval-count : 0
    'leaves             : (list)
    'blips              : (list)
    'guide-blips        : (list)
    'state              : 'no-selection
    'anchor-col         : nil
    'tail-col           : nil
    'leaf-row           : nil


    'new :
        fn (&profile &event)
            stacks = (object)

            foreach &interval (&profile 'intervals)
                if (&event in (&interval 'events-by-type))
                    foreach &sample ((&interval 'events-by-type) &event)
                        if ('stack in &sample)
                            stacks <- (((&profile 'strings) (&sample 'stack)) : 1)

            stacks = (sorted (keys stacks))

            leaves = (list)

            foreach stack stacks
                leaf = (last (split stack ";"))
                if (not (leaf in leaves))
                    append leaves leaf

            map = (new-instance Thief-Scope)

            (map 'height) = (len leaves)
            (map 'width)  = (len (&profile 'intervals))
            (map 'leaves) = (move leaves)

            largest-count = 0
            foreach &interval (&profile 'intervals)
                total = 0
                &interval <- ('count-by-leaf : (object))
                foreach &leaf (map 'leaves)
                    (&interval 'count-by-leaf) <- (&leaf : 0)

                if (&event in (&interval 'events-by-type))
                    foreach &sample ((&interval 'events-by-type) &event)
                        ((&interval 'count-by-leaf) (&sample 'leaf)) += (&sample 'count)
                        total += (&sample 'count)

                foreach count (values (&interval 'count-by-leaf))
                    largest-count = (max largest-count count)

                &interval <- ('total-count : total)
                (map 'max-interval-count) = (max (map 'max-interval-count) total)

            col = 1
            foreach &interval (&profile 'intervals)
                value = (select ((map 'max-interval-count) == 0) 0.0 ((float (&interval 'total-count)) / (map 'max-interval-count)))
                r = (sint ((value * 225) + 30))
                g = (r / 2)
                color = (select (value == 0.0) 0x000000 ((r << 16) | (g << 8)))
                append (map 'guide-blips)
                    (Thief-Scope-Blip 'new) 1 col color

                row = 3
                foreach &leaf (map 'leaves)
                    count = ((&interval 'count-by-leaf) &leaf)
                    value = (select (largest-count == 0) 0.0 ((float count) / largest-count))
                    color = (select (value == 0.0) 0x000000 ((sint ((value * 225) + 30)) << 16))

                    append (map 'blips)
                        (Thief-Scope-Blip 'new) row col color

                    row += 1

                col += 1

            move map

    'paint :
        fn (&self &view)
            repeat c (&view 'width)
                @term:set-cell-bg   2 (c + 1) 0x002000
                @term:set-cell-char 2 (c + 1) " "
            foreach &blip (&self 'guide-blips)
                &blip @ ('paint &view)
            foreach &blip (&self 'blips)
                &blip @ ('paint &view)

    'coord-to-blip-idx :
        fn (&self &row &col)
            ((&col - 1) * (&self 'height)) + (&row - 3)

    'set-col-color-mask :
        fn (&self &view &col &mask)
            repeat i (&self 'height)
                idx = (((&col - 1) * (&self 'height)) + i)
                &blip = ((&self 'blips) idx)
                (&blip 'color) |= &mask
                &blip @ ('paint &view)
                unref &blip

    'reset-col-color :
        fn (&self &view &col)
            repeat i (&self 'height)
                idx = (((&col - 1) * (&self 'height)) + i)
                &blip = ((&self 'blips) idx)
                (&blip 'color) &= 0xff0000
                &blip @ ('paint &view)
                unref &blip

    'set-row-color-mask :
        fn (&self &view &row &mask)
            repeat i (&self 'width)
                idx = ((i * (&self 'height)) + (&row - 3))
                &blip = ((&self 'blips) idx)
                (&blip 'color) |= &mask
                &blip @ ('paint &view)
                unref &blip

    'reset-row-color :
        fn (&self &view &row)
            repeat i (&self 'width)
                idx = ((i * (&self 'height)) + (&row - 3))
                &blip = ((&self 'blips) idx)
                (&blip 'color) &= 0xff0000
                &blip @ ('paint &view)
                unref &blip

    'get-selected-range :
        fn (&self)
            &a = (&self 'anchor-col)
            &t = (&self 'tail-col)
            select (&a <= &t)
                (&a - 1) : ((&t - &a) + 1)
                (&t - 1) : ((&a - &t) + 1)

    'reset-selection :
        fn (&self &view)
            match (&self 'state)
                'anchor-hover
                    &self @ ('reset-col-color &view (&self 'anchor-col))
                    (&self 'anchor-col) = nil
                    &self @ ('reset-row-color &view (&self 'leaf-row))
                    (&self 'leaf-row) = nil

                'tail-hover
                    range  = (&self @ ('get-selected-range))
                    start  = (range 0)
                    length = (range 1)

                    repeat i length
                        i += (start + 1)
                        &self @ ('reset-col-color &view i)

                    (&self 'anchor-col) = nil
                    (&self 'tail-col) = nil

                    &self @ ('reset-row-color &view (&self 'leaf-row))
                    (&self 'leaf-row) = nil

            (&self 'state) = 'no-selection

    'mouse-over :
        fn (&self &view &row &col)
            response = nil
            if ((&row > 2) and (&row <= ((&self 'height) + 1)))
                repeat c (&view 'width)
                    @term:set-cell-bg   2 (c + 1) 0x002000
                    @term:set-cell-char 2 (c + 1) " "
                c = 1
                foreach char (chars ((&self 'leaves) (&row - 3)))
                    @term:set-cell-fg   2 c 0xffffff
                    @term:set-cell-char 2 c char
                    c += 1

                idx = (&self @ ('coord-to-blip-idx &row &col))
                if (idx < (len (&self 'blips)))
                    match (&self 'state)
                        'no-selection
                            (&self 'anchor-col) = &col
                            &self @ ('set-col-color-mask &view &col 0x000040)

                            (&self 'leaf-row) = &row

                            (&self 'state) = 'anchor-hover

                        'anchor-hover
                            &self @ ('reset-col-color &view (&self 'anchor-col))
                            &self @ ('reset-row-color &view (&self 'leaf-row))

                            (&self 'anchor-col) = &col
                            &self @ ('set-col-color-mask &view &col 0x000040)

                            (&self 'leaf-row) = &row
                            &self @ ('set-row-color-mask &view &row 0x002000)

                        'tail-hover
                            range  = (&self @ ('get-selected-range))
                            start  = (range 0)
                            length = (range 1)

                            repeat i length
                                i += (start + 1)
                                &self @ ('reset-col-color &view i)

                            &self @ ('reset-row-color &view (&self 'leaf-row))
                            (&self 'leaf-row) = &row
                            &self @ ('set-row-color-mask &view &row 0x002000)

                            (&self 'tail-col) = &col

                            range  = (&self @ ('get-selected-range))
                            start  = (range 0)
                            length = (range 1)

                            repeat i length
                                i += (start + 1)
                                &self @ ('set-col-color-mask &view i 0x000040)

                @term:flush
            response

    'mouse-click :
        fn (&self &view &row &col)
            response = nil
            if ((&row > 2) and (&row <= ((&self 'height) + 1)))
                idx = (&self @ ('coord-to-blip-idx &row &col))
                if (idx < (len (&self 'blips)))
                    match (&self 'state)
                        'no-selection
                            (&self 'anchor-col) = &col
                            (&self 'tail-col) = &col
                            &self @ ('set-col-color-mask &view &col 0x00007f)

                            (&self 'state) = 'tail-hover

                        'anchor-hover
                            (&self 'anchor-col) = &col
                            (&self 'tail-col)   = &col
                            &self @ ('set-col-color-mask &view &col 0x00007f)

                            (&self 'state) = 'tail-hover

                        'tail-hover
                            (&self 'tail-col) = &col
                            response = 'range-selected

                    @term:flush
            response
