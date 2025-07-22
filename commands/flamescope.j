define-class FlameScope-Sub-FlameGraph-View-Input-Handler
    'on-key :
        fn (&self &view &key)
            match &key
                "q"
                    set-view "main"
                "esc"
                    foreach widget-name (&view 'widgets)
                        &widget = ((&view 'widgets) widget-name)
                        if ((&widget '__class__) == (' Flame-Graph))
                            &widget @ ('reset-zoom &view)
                        unref &widget
                "up"
                    ++ (&view 'vert-offset)
                    &view @ ('paint)
                "down"
                    if ((&view 'vert-offset) > 0)
                        -- (&view 'vert-offset)
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

                    &view <- ('last-right-button-row : &row)
                    &view <- ('last-right-button-col : &col)

                    &view @ ('paint)
            else
                foreach widget-name (&view 'widgets)
                    &widget = ((&view 'widgets) widget-name)
                    response = nil
                    if ((&action == 'down) and (&button == 'left))
                        response = (&widget @ ('mouse-click &view &row &col))
                    elif (&action == 'over)
                        response = (&widget @ ('mouse-over &view &row &col))
                    unref &widget

define-class FlameScope-View-Input-Handler
    'on-key :
        fn (&self &view &key)
            match &key
                "q"
                    @term:exit
                "up"
                    (&view 'vert-offset) += (&view 'height)
                    (&view 'vert-offset) = (min (&view 'vert-offset) 0)
                    &view @ ('paint)
                "down"
                    (&view 'vert-offset) -= (&view 'height)
                    &view @ ('paint)
                "right"
                    (&view 'horiz-offset) -= (&view 'width)
                    &view @ ('paint)
                "left"
                    (&view 'horiz-offset) += (&view 'width)
                    (&view 'horiz-offset) = (min (&view 'horiz-offset) 0)
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
                        (&view 'vert-offset) = (min (&view 'vert-offset) 0)
                    if ('last-right-button-col in &view)
                        (&view 'horiz-offset) += (&col - (&view 'last-right-button-col))
                        (&view 'horiz-offset) = (min (&view 'horiz-offset) 0)

                    &view <- ('last-right-button-row : &row)
                    &view <- ('last-right-button-col : &col)

                    &view @ ('paint)
            else
                range-hover-widget-name = nil

                foreach widget-name (&view 'widgets)
                    &widget = ((&view 'widgets) widget-name)
                    response = nil
                    if ((&action == 'down) and (&button == 'left))
                        response = (&widget @ ('mouse-click &view &row &col))
                    elif (&action == 'over)
                        response = (&widget @ ('mouse-over &view &row &col))

                    match response
                        'range-hover
                            if (range-hover-widget-name == nil)
                                range-hover-widget-name = widget-name

                        'range-selected
                            range = (&widget @ ('get-selected-range))

                            foreach heatmap-widget-name (&view 'widgets)
                                &heatmap-widget = ((&view 'widgets) heatmap-widget-name)
                                if ((&heatmap-widget '__class__) == (' SSO-Heatmap))
                                    &heatmap-widget @ ('reset-selection &view)
                                unref &heatmap-widget

                            views <-
                                "flamegraph" :
                                    (View 'new) rows cols
                                        'name          : "Flame Graph"
                                        'input-handler : (new-instance FlameScope-Sub-FlameGraph-View-Input-Handler)

                            set-view "flamegraph"

                            &current-view @
                                'add-widget "flamegraph"
                                    (Flame-Graph 'new) profile (&widget 'event) (range 0) (range 1) 2

                            &current-view @ ('paint)

                    unref &widget

                if (range-hover-widget-name != nil)
                    range = (((&view 'widgets) range-hover-widget-name) @ ('get-selected-range))

                    did-paint-other-range = 0

                    foreach widget-name (&view 'widgets)
                        &widget = ((&view 'widgets) widget-name)
                        if ((widget-name != range-hover-widget-name) and ('set-mirror-range in ((&widget '__class__))))
                            &widget @ ('set-mirror-range &view range)
                            did-paint-other-range = 1
                        unref &widget

                    if did-paint-other-range
                        @term:flush

flamescope-command =
    fn (&profile)
        &current-view @ ('set-input-handler (new-instance FlameScope-View-Input-Handler))

        offset = 2
        foreach event (&profile 'event-count-by-type)
            name = (fmt "heatmap/%" event)
            &current-view @
                'add-widget name
                    (SSO-Heatmap 'new) &profile event offset 0
            offset = ((offset + (((&current-view 'widgets) name) 'height)) + 1)
