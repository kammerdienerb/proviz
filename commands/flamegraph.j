define-class FlameGraph-View-Input-Handler
    'on-key :
        fn (&self &view &key)
            match &key
                "q"
                    @term:exit
                "up"
                    ++ (&view 'vert-offset)
                    &view @ ('clear)
                    &view @ ('paint)
                "down"
                    if ((&view 'vert-offset) > 0)
                        -- (&view 'vert-offset)
                        &view @ ('clear)
                        &view @ ('paint)
    'on-mouse :
        fn (&self &view &type &action &button &row &col)
            foreach widget-name (&view 'widgets)
                &widget = ((&view 'widgets) widget-name)
                response = nil
                if (&action == 'over)
                    response = (&widget @ ('mouse-over &view &row &col))

flamegraph-command =
    fn (&profile)
        &current-view @ ('set-input-handler (new-instance FlameGraph-View-Input-Handler))
        name = (fmt "flamegraph/%" (&profile 'default-event))
        &current-view @
            'add-widget name
                (Flame-Graph 'new) &profile (&profile 'default-event) 0 (len (&profile 'intervals)) 2
