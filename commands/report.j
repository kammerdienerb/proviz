report-widget-offset := 0

define-class Report-Sub-FlameGraph-View-Input-Handler
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


define-class Report-View-Input-Handler
    'on-key :
        fn (&self &view &key)
            &menu = ((&view 'widgets) "menu")

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
                    (&view 'horiz-offset) -= ((&view 'width) - (&menu 'width))
                    &view @ ('paint)
                "left"
                    (&view 'horiz-offset) += ((&view 'width) - (&menu 'width))
                    (&view 'horiz-offset) = (min (&view 'horiz-offset) (&menu 'width))
                    &view @ ('paint)

    'on-mouse :
        fn (&self &view &type &action &button &row &col)
            &menu = ((&view 'widgets) "menu")

            in-menu =
                fn (&menu &row &col)
                    and
                        &row > 1
                        &row <= (&menu 'height)
                        &col <= (&menu 'width)

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
                if (in-menu &menu &row &col)
                    &view @ ('status-text "")

                    response = nil
                    if ((&action == 'down) and (&button == 'left))
                        response = (&menu @ ('mouse-click &view &row &col))
                    elif (&action == 'over)
                        response = (&menu @ ('mouse-over &view &row &col))

                    match response
                        'report-add-widget
                            event = ((&menu 'events) (&menu 'selected-idx))

                            new-widget =
                                (SSO-Heatmap 'new) &report-profile event (2 + report-widget-offset) (&menu 'width)

                            report-widget-offset += ((new-widget 'height) + 1)

                            &view @
                                'add-widget (fmt "flamescope/%" event)
                                    new-widget
                            &view @ ('paint)

                        'report-remove-widget
                            event = ((&menu 'events) (&menu 'selected-idx))
                            name  = (fmt "flamescope/%" event)
                            &widget = ((&view 'widgets) name)

                            foreach other-widget-name (&view 'widgets)
                                if (startswith other-widget-name "flamescope/")
                                    &other-widget = ((&view 'widgets) other-widget-name)
                                    if ((&other-widget 'start-row) > (&widget 'start-row))
                                        (&other-widget 'start-row) -= ((&widget 'height) + 1)
                                    unref &other-widget

                            report-widget-offset -= ((&widget 'height) + 1)
                            unref &widget
                            (&view 'widgets) -> name
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

                                foreach selection-widget-name (&view 'widgets)
                                    &selection-widget = ((&view 'widgets) selection-widget-name)
                                    if ('reset-selection in ((&selection-widget '__class__)))
                                        &selection-widget @ ('reset-selection &view)
                                    unref &selection-widget

                                views <-
                                    "flamegraph" :
                                        (View 'new) rows cols
                                            'name          : "Flame Graph"
                                            'input-handler : (new-instance Report-Sub-FlameGraph-View-Input-Handler)

                                set-view "flamegraph"

                                &current-view @
                                    'add-widget "flamegraph"
                                        (Flame-Graph 'new) &report-profile (&widget 'event) (range 0) (range 1) 2

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

report-command =
    fn (&profile)
        # Global ref to profile looked for by Report-Menu widget.
        &report-profile := &profile

        &current-view @ ('set-input-handler (new-instance Report-View-Input-Handler))
        &current-view @ ('add-widget "menu" ((Report-Menu 'new)))

        (&current-view 'horiz-offset) = (((&current-view 'widgets) "menu") 'width)
