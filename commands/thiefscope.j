define-class Thief-Sub-FlameGraph-View-Input-Handler
    'on-key :
        fn (&self &view &key)
            match &key
                "q"
                    set-view "main"
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
        foreach event (&profile 'num-events-by-type)
            name = (fmt "thiefscope/%" event)
            &current-view @
                'add-widget name
                    (Thief-Scope 'new) &profile event offset
            offset = ((offset + (((&current-view 'widgets) name) 'height)) + 1)
