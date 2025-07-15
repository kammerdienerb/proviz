define-class Flame-Graph-Frame
    'label                  : ""
    'type                   : nil
    'color                  : 0x0
    'count                  : 0
    'children               : (object)
    'sorted-children-labels : (list)
    'row                    : 0
    'col                    : 0
    'width                  : 0

    'new :
        fn (label)
            frame = (new-instance Flame-Graph-Frame)

            type = 'unknown

            if (startswith label "py::")
                type = 'python
            elif (contains label "::")
                type = 'cpp
            elif (endswith label "_[k]")
                type = 'kernel
                label = (substr label 0 ((len label) - 4))
            elif (endswith label "_[g]")
                type = 'gpu-inst
                label = (substr label 0 ((len label) - 4))
            elif (endswith label "_[G]")
                type = 'gpu-symbol
                label = (substr label 0 ((len label) - 4))
            elif (label == "-")
                type = 'divider

            (frame 'label) = (move label)
            (frame 'type)  = type
            (frame 'color) = ((Flame-Graph-Frame 'get-color) type (rand))

            move frame

    'add-flame :
        fn (&self &stack &count)
            if (len &stack)
                fname = (move (&stack 0))
                erase &stack 0

                &child = (get-or-insert (&self 'children) fname ((Flame-Graph-Frame 'new) fname))
                &child @ ('add-flame &stack &count)

            (&self 'count) += &count

    'sort :
        fn (&self)
            &children = (&self 'children)
            if (len &children)
                sorted-children-labels = (list)

                foreach label &children
                    (&children label) @ ('sort)
                    append sorted-children-labels (label : ((&children label) 'count))

                sorted-children-labels = (sorted (move sorted-children-labels) (fn (a b) ((a 1) > (b 1))))

                foreach &pair sorted-children-labels
                    append (&self 'sorted-children-labels) (move (&pair 0))
            nil

    'get-color :
        fn (&type &r)
            h = 0.0
            s = 0.5
            v = 0.75

            match &type
                'loading
                    h = 4.79966
                    s = &r
                    v = 0.75
                'divider
                    s = 0.0
                    v = 0.5
                'kernel
                    h = (0.15 * 3.14159)
                'cpp
                    h = (0.25 * 3.14159)
                'python
                    h = 0.0
                    s = 0.25
                'gpu-symbol
                    h = 3.14159
                'gpu-inst
                    h = (0.6 * 3.14159)

            if (&type != 'divider)
                v += (((float ((&r % 1000) + 1)) / 1000.0) * 0.15)

            R = 0.0
            G = 0.0
            B = 0.0
            C = (v * s)
            X = (C * (1 - (abs (((h / (3.14159 / 3.0)) % 2.0) - 1))))
            m = (v - C)

            if ((h >= 0.0) and (h < (3.14159 / 3.0)))
                R = C
                G = X
                B = 0
            elif ((h >= (3.14159 / 3.0)) and (h < ((2.0 * 3.14159) / 3.0)))
                R = X
                G = C
                B = 0
            elif ((h >= ((2.0 * 3.14159) / 3.0)) and (h < 3.14159))
                R = 0
                G = C
                B = X
            elif ((h >= (3.14159 / 2.0)) and (h < ((4.0 * 3.14159) / 3.0)))
                R = 0
                G = X
                B = C
            elif ((h >= ((4.0 * 3.14159) / 3.0)) and (h < ((5.0 * 3.14159) / 3.0)))
                R = X
                G = 0
                B = C
            elif ((h >= ((5.0 * 3.14159) / 3.0)) and (h < (2.0 * 3.14159)))
                R = C
                G = 0
                B = X

            (((sint ((R + m) * 255)) & 255) << 16) |
                (((sint ((G + m) * 255)) & 255) << 8) |
                    (sint ((B + m) * 255)) & 255

    'paint :
        fn (&self &row &start-col &width)
            if ((&width >= 1) and (&row > 1))
                text = (&self 'label)

                (&self 'row)   = &row
                (&self 'col)   = &start-col
                (&self 'width) = &width

                if (&width > 1)
                    if (((len text) > (&width - 1)) and (&width > 2))
                        text = (fmt "%.." (substr text 0 (&width - 3)))
                    if ((len text) > 0)
                        text = (substr text 0 (&width - 1))
                else
                    text = ""

                repeat i &width
                    @term:set-cell-bg &row (&start-col + i) (&self 'color)
                i = 0
                foreach &c (chars text)
                    @term:set-cell-fg   &row (&start-col + i) 0x000000
                    @term:set-cell-char &row (&start-col + i) &c
                    i += 1

                &children = (&self 'children)

                child-offset = 0
                foreach &label (&self 'sorted-children-labels)
                    &child = (&children &label)

                    child-width = (sint (((float (&child 'count)) / (float (&self 'count))) * &width))
                    if (child-width < 1) (child-width = 1)

                    if ((child-offset + child-width) >= &width)
                        child-width = (&width - child-offset)

                    if (child-width > 0)
                        &child @ ('paint (&row - 1) (&start-col + child-offset) child-width)

                    child-offset += child-width
                    unref &child

define-class Flame-Graph
    'base          : nil
    'zoom-stack    : ""
    'last-sel-row  : 0
    'last-sel-col  : 0

    'new :
        fn (&profile &event &start &length &vert-offset)
            flame = (new-instance Flame-Graph)

            &base = (flame 'base)
            &base = ((Flame-Graph-Frame 'new) "all")

            counts = (object)
            repeat i &length
                &interval = ((&profile 'intervals) (i + &start))
                if (&event in (&interval 'events-by-type))
                    foreach &sample ((&interval 'events-by-type) &event)
                        if (('stack in &sample) and ((&sample 'stack) != 0))
                            (get-or-insert counts (&sample 'stack) 0) += (&sample 'count)

            foreach stack-id counts
                flame-stack = (splits (&profile @ ('get-string stack-id)) ";")
                &base @ ('add-flame flame-stack (counts stack-id))

            flame @ ('sort)

            unref &base
            move flame

    'sort :
        fn (&self)
            (&self 'base) @ ('sort)

    'paint-hover-frame :
        fn (&self &view &row &col &color)
            &cur-frame = (&self 'base)

            foreach zframe (splits (&self 'zoom-stack) ";")
                if (zframe in (&cur-frame 'children))
                    &new-cur-frame = ((&cur-frame 'children) zframe)
                    unref &cur-frame
                    &cur-frame = &new-cur-frame
                    unref &new-cur-frame

            out-of-bounds = 0
            while ((not out-of-bounds) and ((&cur-frame 'row) != &row))
                matching-label = nil
                foreach label (&cur-frame 'children)
                    &child = ((&cur-frame 'children) label)
                    if ((&col >= (&child 'col)) and (&col < ((&child 'col) + (&child 'width))))
                        matching-label = label
                    unref &child

                if (matching-label == nil)
                    out-of-bounds = 1
                else
                    &new-frame = ((&cur-frame 'children) matching-label)
                    unref &cur-frame
                    &cur-frame = &new-frame
                    unref &new-frame

            if (not out-of-bounds)
                if (&color == nil)
                    (&cur-frame 'color) = (&cur-frame 'save-color)
                    &cur-frame -> 'save-color
                else
                    &cur-frame <- ('save-color : (&cur-frame 'color))
                    (&cur-frame 'color) = &color

                &cur-frame @ ('paint (&cur-frame 'row) (&cur-frame 'col) (&cur-frame 'width))

                &view @ ('status-text (fmt "Frame: % Samples: %" (&cur-frame 'label) (&cur-frame 'count)))

            not out-of-bounds

    'paint :
        fn (&self &view &vert-offset &horiz-offset)
            &view @ ('clear)

            if ((&self 'last-sel-row) and (&self 'last-sel-col))
                &self @ ('paint-hover-frame &view (&self 'last-sel-row) (&self 'last-sel-col) nil)

            &view @ ('status-text "")
            (&self 'last-sel-row) = 0
            (&self 'last-sel-col) = 0

            &base = (&self 'base)

            foreach zframe (splits (&self 'zoom-stack) ";")
                if (zframe in (&base 'children))
                    &new-base = ((&base 'children) zframe)
                    unref &base
                    &base = &new-base
                    unref &new-base

            &base @ ('paint ((&view 'height) + &vert-offset) 1 (&view 'width))

    'reset-zoom :
        fn (&self &view)
            if ((&self 'last-sel-row) and (&self 'last-sel-col))
                &self @ ('paint-hover-frame &view (&self 'last-sel-row) (&self 'last-sel-col) nil)

            &view @ ('status-text "")
            (&self 'last-sel-row) = 0
            (&self 'last-sel-col) = 0

            (&self 'zoom-stack) = ""

            &self @ ('paint &view (&view 'vert-offset) (&view 'horiz-offset))

            @term:flush

    'mouse-click :
        fn (&self &view &row &col)
            &cur-frame = (&self 'base)

            foreach zframe (splits (&self 'zoom-stack) ";")
                if (zframe in (&cur-frame 'children))
                    &new-cur-frame = ((&cur-frame 'children) zframe)
                    unref &cur-frame
                    &cur-frame = &new-cur-frame
                    unref &new-cur-frame

            new-zstack = (&self 'zoom-stack)

            out-of-bounds = 0
            while ((not out-of-bounds) and ((&cur-frame 'row) != &row))
                matching-label = nil
                foreach label (&cur-frame 'children)
                    &child = ((&cur-frame 'children) label)
                    if ((&col >= (&child 'col)) and (&col < ((&child 'col) + (&child 'width))))
                        matching-label = label
                    unref &child

                if (matching-label == nil)
                    out-of-bounds = 1
                else
                    new-zstack = (fmt "%;%" (move new-zstack) matching-label)
                    &new-frame = ((&cur-frame 'children) matching-label)
                    unref &cur-frame
                    &cur-frame = &new-frame
                    unref &new-frame

            if (not out-of-bounds)
                if (startswith new-zstack ";")
                    new-zstack = (substr new-zstack 1 ((len new-zstack) - 1))

                if ((&self 'last-sel-row) and (&self 'last-sel-col))
                    &self @ ('paint-hover-frame &view (&self 'last-sel-row) (&self 'last-sel-col) nil)

                &view @ ('status-text "")
                (&self 'last-sel-row) = 0
                (&self 'last-sel-col) = 0

                (&self 'zoom-stack) = new-zstack

                &self @ ('paint &view (&view 'vert-offset) (&view 'horiz-offset))

                @term:flush

    'mouse-over :
        fn (&self &view &row &col)
            if ((&self 'last-sel-row) and (&self 'last-sel-col))
                &self @ ('paint-hover-frame &view (&self 'last-sel-row) (&self 'last-sel-col) nil)
            painted = (&self @ ('paint-hover-frame &view &row &col 0xff00ff))

            if painted
                (&self 'last-sel-row) = &row
                (&self 'last-sel-col) = &col
            else
                &view @ ('status-text "")
                (&self 'last-sel-row) = 0
                (&self 'last-sel-col) = 0

            @term:flush
