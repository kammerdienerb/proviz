define-class Thief-Sub-FlameGraph-View-Input-Handler
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
                    if ((&action == 'down) and (&button == 'left))
                        response = (&widget @ ('mouse-click &view &row &col))
                    elif (&action == 'over)
                        response = (&widget @ ('mouse-over &view &row &col))
                    unref &widget

define-class ThiefScope-View-Input-Handler
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

                    &view <- ('last-right-button-row : &row)
                    &view <- ('last-right-button-col : &col)

                    &view @ ('clear)
                    &view @ ('paint)
            else
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

                        views <-
                            "flamegraph" :
                                (View 'new) rows cols
                                    'name          : "Flame Graph"
                                    'input-handler : (new-instance Thief-Sub-FlameGraph-View-Input-Handler)

                        set-view "flamegraph"

                        &current-view @
                            'add-widget "flamegraph"
                                (Flame-Graph 'new) profile (&widget 'event) (range 0) (range 1) 2

                        &current-view @ ('paint)
                    unref &widget

thiefscope-command =
    fn (&profile)
        &current-view @ ('set-input-handler (new-instance ThiefScope-View-Input-Handler))

        offset = 2
        foreach event (&profile 'event-count-by-type)
            name = (fmt "thiefscope/%" event)
            &current-view @
                'add-widget name
                    (Thief-Scope 'new) &profile event offset
            offset = ((offset + (((&current-view 'widgets) name) 'height)) + 1)
