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
            foreach widget-name (&view 'widgets)
                &widget = ((&view 'widgets) widget-name)
                response = nil
                if ((&action == 'down) and (&button == 'left))
                    response = (&widget @ ('mouse-click &view &row &col))
                elif (&action == 'over)
                    response = (&widget @ ('mouse-over &view &row &col))
    
                if (response == 'range-selected)
                    range = (&widget @ ('get-selected-range))
    
                    &widget @ ('reset-selection &view)
    
                    flamegraph-view :=
                        (View 'new) rows cols
                            'name          : "Flame Graph"
                            'input-handler : (new-instance FlameGraph-View-Input-Handler)
    
                    set-view flamegraph-view
    
                    &current-view @
                        'add-widget "flamegraph"
                            (Flame-Graph 'new) profile (&widget 'event) (range 0) (range 1)
    
                    &current-view @ ('paint)
                unref &widget

@on-init =
    fn (&rows &cols)
        rows := &rows
        cols := &cols

        parse-cmdline-options (argv)

        heatmap-view :=
            (View 'new) &rows &cols
                'name          : "main view"
                'input-handler : (new-instance Heatmap-View-Input-Handler)

        set-view heatmap-view

        profile := ((Profile 'new))

        foreach pair (options 'FILES)
            path   = (pair 0)
            format = (pair 1)

            f = (fopen-rd path)

            &current-view @ ('loading-bar-init (fmt "Loading %" (f '__path__)))
            parse format profile f &current-view
            &current-view @ ('loading-bar-fini)

            fclose f

        &current-view @ ('loading-bar-init (fmt "Processing profile..."))
        profile @ ('postprocess &current-view)
        &current-view @ ('loading-bar-fini)

        match (options 'COMMAND)
            "flamescope"
                offset = 2
                foreach event (profile 'num-events-by-type)
                    name = (fmt "heatmap/%" event)
                    &current-view @
                        'add-widget name
                            (SSO-Heatmap 'new) profile event offset
                    offset = ((offset + (((&current-view 'widgets) name) 'height)) + 1)

            "thiefscope"
                offset = 2
                foreach event (profile 'num-events-by-type)
                    name = (fmt "thiefscope/%" event)
                    &current-view @
                        'add-widget name
                            (Thief-Scope 'new) profile event offset
                    offset = ((offset + (((&current-view 'widgets) name) 'height)) + 1)

        &current-view @ ('paint)

@on-key =
    fn (&key)
        &current-view @ ('on-key &key)

@on-mouse =
    fn (&type &action &button &row &col)
        &current-view @ ('on-mouse &type &action &button &row &col)
