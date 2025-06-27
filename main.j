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

    'on-mouse :
        fn (&self &view &type &action &button &row &col)
            nil

define-class Heatmap-View-Input-Handler
    'on-key :
        fn (&self &view &key)
            match &key
                "q"
                    @term:exit

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
                            (Flame-Graph 'new) profile (profile 'default-event) (range 0) (range 1)
    
                    &current-view @ ('paint)

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
                foreach event (profile 'num-events-by-type)
                    &current-view @
                        'add-widget "heatmap"
                            (SSO-Heatmap 'new) profile event

            "thiefscope"
                &current-view @
                    'add-widget "heatmap"
                        (Thief-Scope 'new) profile (profile 'default-event)

        &current-view @ ('paint)

@on-key =
    fn (&key)
        &current-view @ ('on-key &key)

@on-mouse =
    fn (&type &action &button &row &col)
        &current-view @ ('on-mouse &type &action &button &row &col)
