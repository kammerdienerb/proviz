# The heatmap and its blips
make-blip =
    fn (time count)
        o = 
            object
                'time : time
                'count : count
        o
newest-blip = (' (heatmap ((len heatmap) - 1)) )
heatmap := (list)
heatmap-largest-count := 0

# Globals
interval-time     := 0.02
heatmap-start-row := 5
heatmap-start-col := 1
heatmap-height    := (sint (1 / interval-time))

# Colors
heatmap-anchor-color := 0x0000ff
heatmap-hover-color := 0x0000b0
heatmap-range-color := 0x00007f
heatmap-select-mask  := 0xffff00

unclick-rect =
    fn (anchor)
        if (anchor)
            (&heatmap-select-anchor 'color) &= heatmap-select-mask
            ((&heatmap-select-anchor 'paint-fn)) &heatmap-select-anchor
            if ('clicked in &heatmap-select-anchor)
                &heatmap-select-anchor -> 'clicked
            unref &heatmap-select-anchor
        else
            (&heatmap-select-tail 'color) &= heatmap-select-mask
            ((&heatmap-select-tail 'paint-fn)) &heatmap-select-tail
            if ('clicked in &heatmap-select-tail)
                &heatmap-select-tail -> 'clicked
            unref &heatmap-select-tail
            
heatmap-on-click =
    fn (&rect row col)
        &blip = (heatmap (&rect 'blip-index))
        should-flamegraph = 0
        
        if (is-bound &heatmap-select-anchor)
            &heatmap-select-tail := &rect
            &rect <- ('clicked : 1)
            (&heatmap-select-tail 'color) |= heatmap-anchor-color
            ((&heatmap-select-tail 'paint-fn)) &heatmap-select-tail
            
            # The user selected a range. Render the flamegraph.
            &anchor-blip = (heatmap (&heatmap-select-anchor 'blip-index))
            if ((&blip 'time) < (&anchor-blip 'time))
                start-index := (&blip 'rect-index)
                end-index := (&anchor-blip 'rect-index)
            else
                start-index := (&anchor-blip 'rect-index)
                end-index := (&blip 'rect-index)
            
            should-flamegraph = 1
            
            unclick-rect 0
            unclick-rect 1
        else
            # The user is selecting the anchor
            &heatmap-select-anchor := &rect
            &rect <- ('clicked : 1)
            (&heatmap-select-anchor 'color) |= heatmap-anchor-color
            ((&heatmap-select-anchor 'paint-fn)) &heatmap-select-anchor
            
        @term:flush
        should-flamegraph
        
heatmap-on-hover =
    fn (&rect row col)
        # Color the new rectangle if it hasn't been clicked
        if (not ('clicked in &rect))
            &rect <- ('prev-color : (&rect 'color))
            (&rect 'color) |= heatmap-hover-color
            ((&rect 'paint-fn)) &rect
            @term:flush
            
        # Recolor the previously-highlighted one, if it hasn't
        # been clicked
        if (is-bound &prev-hover)
            if (not ('clicked in &prev-hover))
                (&prev-hover 'color) = (&prev-hover 'prev-color)
                ((&prev-hover 'paint-fn)) &prev-hover
                @term:flush
            unref &prev-hover
            
        if (is-bound &heatmap-select-anchor)
            &blip = (heatmap (&rect 'blip-index))
            &anchor-blip = (heatmap (&heatmap-select-anchor 'blip-index))
            anchor-is-first = 0
            if ((&blip 'time) < (&anchor-blip 'time))
                start-index = (&blip 'rect-index)
                end-index = (&anchor-blip 'rect-index)
            else
                start-index = (&anchor-blip 'rect-index)
                end-index = (&blip 'rect-index)
                anchor-is-first = 1
            repeat i (end-index - start-index)
                &cur-rect = (elements ((start-index + i) + anchor-is-first))
                (&cur-rect 'color) |= heatmap-range-color
                ((&cur-rect 'paint-fn)) &cur-rect
                unref &cur-rect
            @term:flush
            repeat i (end-index - start-index)
                &cur-rect = (elements ((start-index + i) + anchor-is-first))
                (&cur-rect 'color) &= heatmap-select-mask
                ((&cur-rect 'paint-fn)) &cur-rect
                unref &cur-rect
            
        &prev-hover := &rect

parse-heatmap-input =
    fn ()
        # Loading bar for loading the heatmap
        add-element
            loading-bar 1 "AGGREGATE"
        &agg-bar = (newest-element)
        loading-bar-update &agg-bar 0.0
        
        # Parse the profile
        profile := (make-profile)
        parse-profile ((argv) 1) profile
        
        # Construct the heatmap from the profile
        length = (len (profile 'intervals))
        update = (length / cols)
        index = 0
        total-count = 0
        foreach &interval (profile 'intervals)
            time = (&interval 'start)
            count = (&interval 'count)
            
            append heatmap
                make-blip time count
            
            if (count > heatmap-largest-count)
                heatmap-largest-count := count
            total-count += count
                
            if ((index % update) == 0)
                loading-bar-update &agg-bar ((float index) / length)
                
            index += 1
            
        loading-bar-update &agg-bar 1.0
        append elements
            text 3 1 (fmt "Total Samples: %" total-count) ('color : 0xffffff)
        append elements
            text 4 1 (fmt "# Intervals: %" (len heatmap)) ('color : 0xffffff)
        paint
        
render-heatmap =
    fn ()
        row = (heatmap-start-row + (heatmap-height - 1))
        col = heatmap-start-col
        index = 0
        foreach &blip heatmap
            value = ((float (&blip 'count)) / heatmap-largest-count)
            append elements
                rect row col 1 1 (select (value == 0.0) 0x000000 ((sint ((value * 225) + 30)) << 16))
                    'on-click   : heatmap-on-click
                    'on-hover   : heatmap-on-hover
                    'blip-index : index
            &blip <- ('rect-index : ((len elements) - 1))
            
            if (row == heatmap-start-row)
                col += 1
                row = (heatmap-start-row + (heatmap-height - 1))
            else
                row -= 1
            index += 1
        
key-actions =
    object
        "q" : (' (@term:exit) )

@on-key =
    fn (key)
        if (key in key-actions)
            (key-actions key)

@on-mouse =
    fn (type action button row col)
        should-flamegraph = 0
        if ((action == 'down) and (button == 'left))
            foreach &elem elements
                if (('on-click in &elem) and (in-element &elem row col))
                    should-flamegraph = ((&elem 'on-click) &elem row col)
        if (action == 'over)
            foreach &elem elements
                if (('on-hover in &elem) and (in-element &elem row col))
                    (&elem 'on-hover) &elem row col
                    
        if (should-flamegraph)
            if (is-bound &prev-hover)
                unref &prev-hover
            render-flamegraph profile start-index end-index

redraw =
    fn (rows cols)
        rows := rows
        cols := cols
        elements := (list)
        paint

@on-init =
    fn (rows cols)
        redraw rows cols
        elements := (list)
        paint
        
        parse-heatmap-input
        render-heatmap
        paint
