rows            := 0
cols            := 0
profile         := nil
heatmap-view    := nil
flamegraph-view := nil

set-view =
    fn (&new-view)
        if (is-bound &current-view)
            @term:clear
            unref &current-view
        &current-view := &new-view
        (&current-view 'height) = rows
        (&current-view 'width)  = cols
        &current-view @ ('paint)

define-class FlameGraph-View-Input-Handler
    'on-key :
        fn (&self &view &key)
            match &key
                "q"
                    set-view heatmap-view
                "up"
                    (&view 'vert-offset) = ((&view 'vert-offset) + 1)
                    &view @ ('clear)
                    &view @ ('paint)
                "down"
                    if ((&view 'vert-offset) > 0)
                        (&view 'vert-offset) = ((&view 'vert-offset) - 1)
                        &view @ ('clear)
                        &view @ ('paint)

    'on-mouse :
        fn (&self &view &type &action &button &row &col)
            nil

define-class Heatmap-View-Input-Handler
    'on-key :
        fn (&self &view &key)
            match &key
                "q"
                    @term:exit
                "up"
                    (&view 'vert-offset) = ((&view 'vert-offset) + 1)
                    &view @ ('clear)
                    &view @ ('paint)
                "down"
                    (&view 'vert-offset) = ((&view 'vert-offset) - 1)
                    &view @ ('clear)
                    &view @ ('paint)

    'on-mouse :
        fn (&self &view &type &action &button &row &col)
            response = nil
            if ((&action == 'down) and (&button == 'left))
                response = (((&view 'widgets) "heatmap") @ ('mouse-click &view &row &col))
            elif (&action == 'over)
                response = (((&view 'widgets) "heatmap") @ ('mouse-over &view &row &col))

            if (response == 'range-selected)
                range = (((&view 'widgets) "heatmap") @ ('get-selected-range))

                ((&view 'widgets) "heatmap") @ ('reset-selection &view)

                flamegraph-view :=
                    (View 'new) rows cols
                        'name          : "Flame Graph"
                        'input-handler : (new-instance FlameGraph-View-Input-Handler)

                set-view flamegraph-view

                &current-view @
                    'add-widget "flamegraph"
                        (Flame-Graph 'new) profile (profile 'default-event) (range 0) (range 1)

                &current-view @ ('paint)
                
define-class Dual-Heatmap-View-Input-Handler
    'on-key :
        fn (&self &view &key)
            match &key
                "q"
                    @term:exit
                "up"
                    (&view 'vert-offset) = ((&view 'vert-offset) + 1)
                    &view @ ('clear)
                    &view @ ('paint)
                "down"
                    (&view 'vert-offset) = ((&view 'vert-offset) - 1)
                    &view @ ('clear)
                    &view @ ('paint)

    'on-mouse :
        fn (&self &view &type &action &button &row &col)
            response = nil
            
            # Handle the CPU heatmap if we're in that range
            if ((&action == 'down) and (&button == 'left))
                response = (((&view 'widgets) "cpu-heatmap") @ ('mouse-click &view &row &col))
            elif (&action == 'over)
                response = (((&view 'widgets) "cpu-heatmap") @ ('mouse-over &view &row &col))
                
            # If the user selected a range, handle it in the CPU heatmap
            if (response == 'range-selected)
                range = (((&view 'widgets) "cpu-heatmap") @ ('get-selected-range))
                ((&view 'widgets) "cpu-heatmap") @ ('reset-selection &view)

                flamegraph-view :=
                    (View 'new) rows cols
                        'name          : "Flame Graph"
                        'input-handler : (new-instance FlameGraph-View-Input-Handler)

                set-view flamegraph-view

                &current-view @
                    'add-widget "flamegraph"
                        (Flame-Graph 'new) profile (profile 'default-event) (range 0) (range 1)

                &current-view @ ('paint)
                
            # If the hover/click wasn't in the CPU heatmap, handle the GPU one.
            elif (response == nil)
                if ((&action == 'down) and (&button == 'left))
                    response = (((&view 'widgets) "gpu-heatmap") @ ('mouse-click &view &row &col))
                elif (&action == 'over)
                    response = (((&view 'widgets) "gpu-heatmap") @ ('mouse-over &view &row &col))
                if (response == 'range-selected)
                    range = (((&view 'widgets) "gpu-heatmap") @ ('get-selected-range))
                    ((&view 'widgets) "gpu-heatmap") @ ('reset-selection &view)
    
                    flamegraph-view :=
                        (View 'new) rows cols
                            'name          : "Flame Graph"
                            'input-handler : (new-instance FlameGraph-View-Input-Handler)
    
                    set-view flamegraph-view
    
                    &current-view @
                        'add-widget "flamegraph"
                            (Flame-Graph 'new) profile (profile 'default-event) (range 0) (range 1)
    
                    &current-view @ ('paint)

@on-init =
    fn (&rows &cols)
        rows := &rows
        cols := &cols

        mode = ((argv) 1)
        path = ((argv) 2)

        profile := ((Profile 'new))

        f = (fopen-rd path)

        match mode
            "flamescope"
                # Set up the view
                heatmap-view :=
                    (View 'new) &rows &cols
                        'name          : "main view"
                        'input-handler : (new-instance Heatmap-View-Input-Handler)
                set-view heatmap-view
                
                # Parse the profile
                parse "iaprof" profile f &current-view
                
                # Add the widget
                &current-view @
                    'add-widget "heatmap"
                        (SSO-Heatmap 'new) profile (profile 'default-event) 2
                        
            "combined-flamescope"
                # Set up the view
                heatmap-view :=
                    (View 'new) &rows &cols
                        'name          : "main view"
                        'input-handler : (new-instance Dual-Heatmap-View-Input-Handler)
                set-view heatmap-view
            
                # Parse the profiles
                path2 = ((argv) 3)
                f2 = (fopen-rd path2)
                parse "perf-script" profile f &current-view
                parse "iaprof" profile f2 &current-view
                
                &current-view @
                    'add-widget "cpu-heatmap"
                        (SSO-Heatmap 'new) profile "inst_retired.prec_dist" 2
                &current-view @
                    'add-widget "gpu-heatmap"
                        (SSO-Heatmap 'new) profile "EU Stall" 23

            "thief"
                &current-view @
                    'add-widget "heatmap"
                        (Thief-Scope 'new) profile "EU Stall"

        &current-view @ ('paint)

@on-key =
    fn (&key)
        &current-view @ ('on-key &key)

@on-mouse =
    fn (&type &action &button &row &col)
        &current-view @ ('on-mouse &type &action &button &row &col)
