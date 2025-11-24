define-class Line-Graph
    'height       : 0
    'start-row    : 0
    'label-offset : 0
    'state        : 'no-selection
    'anchor-idx   : nil
    'tail-idx     : nil
    'event        : ""
    'points       : (list)
    'color        : 0
    'glyphs       :
        object
            -1             : "⡀"
            -2             : "⠄"
            -3             : "⠂"
            -4             : "⠁"

            (0 | (0 << 2)) : "⣀"
            (0 | (1 << 2)) : "⡠"
            (0 | (2 << 2)) : "⡐"
            (0 | (3 << 2)) : "⡈"

            (1 | (0 << 2)) : "⠢"
            (1 | (1 << 2)) : "⠤"
            (1 | (2 << 2)) : "⠔"
            (1 | (3 << 2)) : "⠌"

            (2 | (0 << 2)) : "⢂"
            (2 | (1 << 2)) : "⠢"
            (2 | (2 << 2)) : "⠒"
            (2 | (3 << 2)) : "⠊"

            (3 | (0 << 2)) : "⢁"
            (3 | (1 << 2)) : "⠡"
            (3 | (2 << 2)) : "⠑"
            (3 | (3 << 2)) : "⠉"

    'new :
        fn (&profile &event &start-row &label-offset)
            graph = (new-instance Line-Graph)

            (graph 'height)       = 6
            (graph 'start-row)    = &start-row
            (graph 'label-offset) = &label-offset
            (graph 'event)        = &event

            largest-count = 0
            foreach &interval (&profile 'intervals)
                if (&event in (&interval 'event-accum-by-type))
                    largest-count = (max largest-count ((&interval 'event-accum-by-type) &event))

            printf "%: %\n" &event largest-count

            foreach &interval (&profile 'intervals)
                count = (select (&event in (&interval 'event-accum-by-type)) ((&interval 'event-accum-by-type) &event) 0)
                value = ((float count) /? largest-count)
                append (graph 'points)
                    object ('count : count) ('value : value)

            (graph 'color) |= (156 + ((rand) % 100))
            (graph 'color) |= ((156 + ((rand) % 100)) << 8)
            (graph 'color) |= ((156 + ((rand) % 100)) << 16)

            graph

    'get-braille-glyph :
        fn (&self &value &next-value)
            h = ((&self 'height) - 1)

            lscaled = (h * &value)
            lrem    = (lscaled - (sint lscaled))
            l       = (sint (lrem / 0.25))

            if (&next-value != nil)
                rscaled = (h * &next-value)

                d = ((sint rscaled) - (sint lscaled))

                if (d > 0)
                    r = 3
                elif (d < 0)
                    r = 0
                else
                    rrem = (rscaled - (sint rscaled))
                    r    = (sint (rrem / 0.25))

                gkey = (l | (r << 2))
            else
                gkey = (0 - (l + 1))

            (&self 'glyphs) gkey

    'paint :
        fn (&self &view &vert-offset &horiz-offset)
            start-row = ((&self 'start-row) + &vert-offset)

            c = (1 + (&self 'label-offset))
            foreach char (chars (&self 'event))
                @term:set-cell-fg   start-row c (&self 'color)
                @term:set-cell-char start-row c char
                ++ c


            offset = (max 0 (0 - &horiz-offset))

            bottom = (start-row + ((&self 'height) - 1))

            c = 1
            repeat idx (&view 'width)
                idx += offset

                if (idx < (len (&self 'points)))
                    &point = ((&self 'points) idx)
                    if (idx < ((len (&self 'points)) - 1))
                        &next-point = ((&self 'points) (idx + 1))

                    value      = (min (&point 'value) 0.999)
                    next-value = (select (is-bound &next-point) (min (&next-point 'value) 0.999) nil)

                    r =
                        select (value == 1.0)
                            (start-row + 1)
                            (bottom - (sint (value * ((&self 'height) - 1))))

                    glyph = (&self @ ('get-braille-glyph value next-value))

                    @term:set-cell-char r c glyph
                    @term:set-cell-fg   r c (&self 'color)

                    unref &point
                    if (is-bound &next-point)
                        unref &next-point

                    ++ c

    'set-col-color :
        fn (&self &view &idx)
            c = ((&idx + 1) + (&view 'horiz-offset))
            repeat r ((&self 'height) - 1)
                r += ((&view 'vert-offset) + ((&self 'start-row) + 1))
                @term:set-cell-bg r c 0x007f7f

    'reset-col-color :
        fn (&self &view &idx)
            c = ((&idx + 1) + (&view 'horiz-offset))
            repeat r ((&self 'height) - 1)
                r += ((&view 'vert-offset) + ((&self 'start-row) + 1))
                @term:unset-cell-bg r c

    'get-selected-range :
        fn (&self)
            &a = (&self 'anchor-idx)
            &t = (&self 'tail-idx)

            select (&t == nil)
                &a : 1
                select (&a <= &t)
                    &a : ((&t - &a) + 1)
                    &t : ((&a - &t) + 1)

    'reset-selection :
        fn (&self &view)
            match (&self 'state)
                'anchor-hover
                    &self @ ('reset-col-color &view (&self 'anchor-idx))
                    (&self 'anchor-idx) = nil

                'tail-hover
                    range  = (&self @ ('get-selected-range))
                    start  = (range 0)
                    length = (range 1)

                    repeat i length
                        i += start
                        &self @ ('reset-col-color &view i)

                    (&self 'anchor-idx) = nil
                    (&self 'tail-idx) = nil

                'mirror
                    range  = (&self @ ('get-selected-range))
                    start  = (range 0)
                    length = (range 1)

                    repeat i length
                        i += start
                        &self @ ('reset-col-color &view i)

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
                &self @ ('set-col-color &view i)

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
                    &row < ((&self 'height) + start-row)
                    &col >= (1 + (&view 'horiz-offset))

                idx = ((&col - (&view 'horiz-offset)) - 1)

                if (idx < (len (&self 'points)))
                    match (&self 'state)
                        'mirror
                            &self @ ('reset-selection &view)

                            (&self 'anchor-idx) = idx
                            &self @ ('set-col-color &view idx)
                            (&self 'state) = 'anchor-hover
                            &view @ ('status-text (fmt "%: %" (&self 'event) (((&self 'points) idx) 'count)))

                            response = 'range-hover

                        'no-selection
                            (&self 'anchor-idx) = idx
                            &self @ ('set-col-color &view idx)
                            (&self 'state) = 'anchor-hover
                            &view @ ('status-text (fmt "%: %" (&self 'event) (((&self 'points) idx) 'count)))

                            response = 'range-hover

                        'anchor-hover
                            &self @ ('reset-col-color &view (&self 'anchor-idx))
                            &self @ ('set-col-color &view idx)
                            (&self 'anchor-idx) = idx
                            &view @ ('status-text (fmt "%: % | Index: %" (&self 'event) (((&self 'points) idx) 'count) idx))

                            response = 'range-hover

                        'tail-hover
                            range  = (&self @ ('get-selected-range))
                            start  = (range 0)
                            length = (range 1)

                            repeat i length
                                i += start
                                &self @ ('reset-col-color &view i)

                            if ((&self 'tail-idx) != (&self 'anchor-idx))
                                &self @ ('reset-col-color &view (&self 'tail-idx))

                            if (idx != (&self 'anchor-idx))
                                &self @ ('set-col-color &view idx)

                            (&self 'tail-idx) = idx

                            range  = (&self @ ('get-selected-range))
                            start  = (range 0)
                            length = (range 1)

                            accum-points = (list)

                            repeat i length
                                i += start
                                &self @ ('set-col-color &view i)
                                append accum-points ((&self 'points) i)

                            accum = (accum-samples (&self 'event) accum-points)

                            &view @ ('status-text (fmt "%: % | Seconds: %" (&self 'event) accum (length * (options 'interval-time))))

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
                    &row < ((&self 'height) + start-row)
                    &col >= (1 + (&view 'horiz-offset))

                idx = ((&col - (&view 'horiz-offset)) - 1)
                if (idx < (len (&self 'points)))
                    match (&self 'state)
                        'mirror
                            &self @ ('reset-selection &view)

                            (&self 'anchor-idx) = idx
                            (&self 'tail-idx) = idx
                            &self @ ('set-col-color &view idx)

                            (&self 'state) = 'tail-hover

                            response = 'range-hover

                        'no-selection
                            (&self 'anchor-idx) = idx
                            (&self 'tail-idx) = idx
                            &self @ ('set-col-color &view idx)

                            (&self 'state) = 'tail-hover

                            response = 'range-hover

                        'anchor-hover
                            (&self 'anchor-idx) = idx
                            (&self 'tail-idx)   = idx
                            &self @ ('set-col-color &view idx)

                            (&self 'state) = 'tail-hover

                            response = 'range-hover

                        'tail-hover
                            (&self 'tail-idx) = idx
                            response = 'range-selected

                    @term:flush
            response
