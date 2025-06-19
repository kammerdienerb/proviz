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
    'height     : 0
    'blips      : (list)
    'state      : 'no-selection
    'anchor-col : nil
    'tail-col   : nil


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
#                 if (not (startswith leaf "0x"))
                if (not (leaf in leaves))
                    append leaves leaf

            map = (new-instance Thief-Scope)

            (map 'height) = (len leaves)

            foreach &interval (&profile 'intervals)
                total = 0
                if (&event in (&interval 'events-by-type))
                    foreach &sample ((&interval 'events-by-type) &event)
                        total += (&sample 'count)
                &interval <- ('count : total)

            &height = (map 'height)

            col = 1
            foreach &interval (&profile 'intervals)
                total = (&interval 'count)
                row = 2
                foreach &leaf leaves
                    count = 0
                    if (&event in (&interval 'events-by-type))
                        foreach &sample ((&interval 'events-by-type) &event)
                            leaf = (last (split ((&profile 'strings) (&sample 'stack)) ";"))
                            if (leaf == &leaf)
                                count += (&sample 'count)

                    value  = (select (total == 0) 0.0 ((float count) / total))
                    color  = (select (value == 0.0) 0x000000 ((sint ((value * 225) + 30)) << 16))

                    append (map 'blips)
                        (Thief-Scope-Blip 'new) row col color

                    row += 1

                col += 1

            map <- ('leaves : leaves)

            move map

    'paint :
        fn (&self &view)
            foreach &blip (&self 'blips)
                &blip @ ('paint &view)

    'coord-to-blip-idx :
        fn (&self &row &col)
            ((&col - 1) * (&self 'height)) + (&row - 2)

    'set-col-color-mask :
        fn (&self &view &col &mask)
            repeat i (&self 'height)
                idx = (((&col - 1) * (&self 'height)) + i)
                &blip = ((&self 'blips) idx)
                (&blip 'color) |= &mask
                &blip @ ('paint &view)

    'reset-col-color :
        fn (&self &view &col)
            repeat i (&self 'height)
                idx = (((&col - 1) * (&self 'height)) + i)
                &blip = ((&self 'blips) idx)
                (&blip 'color) = 0x00ffff
                &blip @ ('paint &view)

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

                'tail-hover
                    range  = (&self @ ('get-selected-range))
                    start  = (range 0)
                    length = (range 1)

                    repeat i length
                        i += (start + 1)
                        &self @ ('reset-col-color &view i)

                    (&self 'anchor-col) = nil
                    (&self 'tail-col) = nil

            (&self 'state) = 'no-selection

    'mouse-over :
        fn (&self &view &row &col)
            response = nil
            if ((&row > 1) and (&row <= ((&self 'height) + 1)))
                repeat c (&view 'width)
                    @term:set-cell-bg   1 (c + 1) 0x000000
                    @term:set-cell-char 1 (c + 1) " "
                c = 1
                foreach char (chars ((&self 'leaves) (&row - 2)))
                    @term:set-cell-fg   1 c 0xffffff
                    @term:set-cell-char 1 c char
                    c += 1

                idx = (&self @ ('coord-to-blip-idx &row &col))
                if (idx < (len (&self 'blips)))
                    match (&self 'state)
                        'no-selection
                            (&self 'anchor-col) = &col
                            &self @ ('set-col-color-mask &view &col 0x0000b0)

                            (&self 'state) = 'anchor-hover

                        'anchor-hover
                            &self @ ('reset-col-color &view (&self 'anchor-col))
                            &self @ ('set-col-color-mask &view &col 0x0000b0)
                            (&self 'anchor-col) = &col

                        'tail-hover
                            range  = (&self @ ('get-selected-range))
                            start  = (range 0)
                            length = (range 1)

                            repeat i length
                                i += (start + 1)
                                &self @ ('reset-col-color &view i)

                            (&self 'tail-col) = &col

                            range  = (&self @ ('get-selected-range))
                            start  = (range 0)
                            length = (range 1)

                            repeat i length
                                i += (start + 1)
                                &self @ ('set-col-color-mask &view i 0x00007f)

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
                            (&self 'anchor-col) = &col
                            (&self 'tail-col) = &col
                            &self @ ('set-col-color-mask &view &col 0x0000ff)

                            (&self 'state) = 'tail-hover

                        'anchor-hover
                            (&self 'anchor-col) = &col
                            (&self 'tail-col)   = &col
                            &self @ ('set-col-color-mask &view &col 0x0000ff)

                            (&self 'state) = 'tail-hover

                        'tail-hover
                            (&self 'tail-col) = &col
                            response = 'range-selected

                    @term:flush
            response
