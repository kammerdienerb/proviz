define-class Flame-Graph-Frame
    'label                  : ""
    'type                   : nil
    'color                  : 0x0
    'count                  : 0
    'children               : (object)
    'sorted-children-labels : (list)


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

                sorted-children-labels = (sorted (move sorted-children-labels) (fn (&a &b) ((&a 1) > (&b 1))))

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

                if (&width > 1)
                    if (((len text) > (&width - 1)) and (&width > 2))
                        text = (fmt "%.." (substr text 0 (&width - 3)))
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
    'base : nil


    'new :
        fn (&profile &event &start &length)
            flame = (new-instance Flame-Graph)

            &base = (flame 'base)
            &base = ((Flame-Graph-Frame 'new) "all")

            counts = (object)
            repeat i &length
                &interval = ((&profile 'intervals) (i + &start))
                if (&event in (&interval 'events-by-type))
                    foreach &sample ((&interval 'events-by-type) &event)
                        if ('stack in &sample)
                            (get-or-insert counts (&sample 'stack) 0) += (&sample 'count)

            # Construct the flame graph from the stacks object
            foreach stack-id counts
                flame-stack = (splits ((&profile 'strings) stack-id) ";")
                &base @ ('add-flame flame-stack (counts stack-id))

            flame @ ('sort)

            unref &base
            move flame

    'sort :
        fn (&self)
            (&self 'base) @ ('sort)

    'paint :
        fn (&self &view)
            (&self 'base) @ ('paint (&view 'height) 1 (&view 'width))
