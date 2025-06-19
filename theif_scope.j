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
    'anchor-idx : nil
    'tail-idx   : nil


    'new :
        fn (&profile &event)
            stacks = (object)

            foreach &interval (&profile 'intervals)
                if (&event in (&interval 'events-by-type))
                    foreach &sample ((&interval 'events-by-type) &event)
                        if ('stack in &sample)
                            stacks <- (((&profile 'strings) (&sample 'stack)) : 1)

            stacks = (sorted (keys stacks))

            println stacks

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
                repeat c (&view 'width)
                    @term:set-cell-bg   1 (c + 1) 0x000000
                    @term:set-cell-char 1 (c + 1) " "
                c = 1
                foreach char (chars ((&self 'leaves) (&row - 2)))
                    @term:set-cell-fg   1 c 0xffffff
                    @term:set-cell-char 1 c char
                    c += 1

                @term:flush


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
