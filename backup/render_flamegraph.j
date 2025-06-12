### CONTENT ###

draw-flame =
    fn (&frame row start-col width)
        if ((width >= 1) and (row > 1))
            text = (&frame 'label)

            if (width > 1)
                if (((len text) > (width - 1)) and (width > 2))
                    text = (fmt "%.." (substr text 0 (width - 3)))
                text = (substr text 0 (width - 1))
            else
                text = ""

            add-element
                flame-graph-view
                make-rect row start-col 1 width (&frame 'color)
                    'text       : text
                    'text-color : 0x000000

            &children = (&frame 'children)

            child-offset = 0
            foreach &label (&frame 'sorted-children-labels)
                &child = (&children &label)

                child-width = (sint (((float (&child 'count)) / (float (&frame 'count))) * width))
                if (child-width < 1) (child-width = 1)

                if ((child-offset + child-width) >= width)
                    child-width = (width - child-offset)

                if (child-width > 0)
                    draw-flame &child (row - 1) (start-col + child-offset) child-width

                child-offset += child-width
                unref &child

create-flame-elements =
    fn ()
        elements := (list)

        if (flame-graph != nil)
            draw-flame flame-graph (flame-graph-view 'rows) 1 (flame-graph-view 'cols)

        add-element
            flame-graph-view
            make-text 1 1 "press 'q' to quit"
        

### INPUT ###

flame-graph = nil

new-frame =
    fn (label)
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

        object
            'label                  : label
            'type                   : type
            'color                  : (get-color type (rand))
            'count                  : 0
            'children               : (object)
            'sorted-children-labels : (list)

add-flame =
    fn (&frame &stack &count)
        if (len &stack)
            fname = (&stack 0)
            erase &stack 0

            &child = (&frame 'children)
            add-flame (get-or-insert &child fname (new-frame fname)) &stack &count

        (&frame 'count) += &count

get-sorted =
    fn (&frame)
        &children = (&frame 'children)
        if (len &children)
            sorted-children-labels = (list)

            foreach label &children
                &child = (&children label)
                get-sorted &child
                append sorted-children-labels (label : ((&children label) 'count))
                unref &child

            sorted-children-labels = (sorted sorted-children-labels (fn (a b) ((a 1) > (b 1))))

            foreach &pair sorted-children-labels
                append (&frame 'sorted-children-labels) (&pair 0)
        nil
        
render-flamegraph =
    fn (&profile start end rows cols &loading-bar)
        flame-graph-view := (make-view rows cols)
        
        reset-loading-bar &loading-bar "AGGREGATE PROFILE"
        loading-bar-update &loading-bar 0.0
        
        flame-graph := (new-frame "all")
        
        length = ((end - start) + 1)
        update = (length / cols)
        counts = (object)
        repeat i length
            &interval = ((&profile 'intervals) (i + start))
            foreach &stall (&interval 'stalls)
                (get-or-insert counts (&stall 'stack) 0) += (&stall 'count)
            if ((i % update) == 0)
                loading-bar-update &loading-bar ((float i) / length)
        loading-bar-update &loading-bar 1.0
        
        reset-loading-bar &loading-bar "FLAME GRAPH"
        loading-bar-update &loading-bar 0.0
        
        # Construct the flame graph from the stacks object
        index = 0
        length = (len counts)
        update = (length / cols)
        foreach stack-id counts
            flame-stack = (split ((&profile 'strings) stack-id) ";")
            count = (counts stack-id)
            add-flame flame-graph flame-stack count
            if ((index % update) == 0)
                loading-bar-update &loading-bar ((float index) / length)
            index += 1
        loading-bar-update &loading-bar 1.0
        
        get-sorted flame-graph
        create-flame-elements
        @term:exit
        paint-view flame-graph-view
