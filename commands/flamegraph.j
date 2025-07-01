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
            if (&button == 'right)
                if (&action == 'down)
                    &view <- ('last-right-button-row : &row)
                    &view <- ('last-right-button-col : &col)
                elif (&action == 'up)
                    &view -> 'last-right-button-row
                    &view -> 'last-right-button-col
                elif (&action == 'drag)
                    if ('last-right-button-row in &view)
                        (&view 'vert-offset) += (&row - (&view 'last-right-button-row))
                        (&view 'vert-offset) = (max (&view 'vert-offset) 0)
#                     if ('last-right-button-col in &view)
#                         (&view 'horiz-offset) += (&col - (&view 'last-right-button-col))

                    &view <- ('last-right-button-row : &row)
                    &view <- ('last-right-button-col : &col)

                    &view @ ('clear)
                    &view @ ('paint)
            else
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
