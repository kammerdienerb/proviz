define-class Report-View-Input-Handler
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
                    -- (&view 'vert-offset)
                    &view @ ('clear)
                    &view @ ('paint)
                "right"
                    -- (&view 'horiz-offset)
                    &view @ ('clear)
                    &view @ ('paint)
                "left"
                    ++ (&view 'horiz-offset)
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
                    if ('last-right-button-col in &view)
                        (&view 'horiz-offset) += (&col - (&view 'last-right-button-col))
                        (&view 'horiz-offset) = (min (&view 'horiz-offset) 0)

                    &view <- ('last-right-button-row : &row)
                    &view <- ('last-right-button-col : &col)

                    &view @ ('clear)
                    &view @ ('paint)

            else
                menu-response = nil

                foreach widget-name (&view 'widgets)
                    &widget = ((&view 'widgets) widget-name)
                    response = nil
                    if ((&action == 'down) and (&button == 'left))
                        response = (&widget @ ('mouse-click &view &row &col))
                    elif (&action == 'over)
                        response = (&widget @ ('mouse-over &view &row &col))

                    if (widget-name == "menu")
                        menu-response = response

                    unref &widget

                match menu-response
                    'report-add-widget
                        &menu = ((&view 'widgets) "menu")
                        event = ((&menu 'events) (&menu 'selected-idx))
                        &view @
                            'add-widget (fmt "flamescope/%" event)
                                (SSO-Heatmap 'new) &report-profile event 1
                        &view @ ('paint)

report-command =
    fn (&profile)
        # Global ref to profile looked for by Report-Menu widget.
        &report-profile := &profile

        &current-view @ ('set-input-handler (new-instance Report-View-Input-Handler))
        &current-view @ ('add-widget "menu" ((Report-Menu 'new)))

        (&current-view 'horiz-offset) = ((((&current-view 'widgets) "menu") 'width) + 1)
