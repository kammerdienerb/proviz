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
                        (Flame-Graph 'new) profile "EU Stall" (range 0) (range 1)

                &current-view @ ('paint)

@on-init =
    fn (&rows &cols)
        rows := &rows
        cols := &cols

        heatmap-view :=
            (View 'new) &rows &cols
                'name          : "Flame Scope"
                'input-handler : (new-instance Heatmap-View-Input-Handler)

        set-view heatmap-view

        profile := ((Profile 'new))

        f = (fopen-rd ((argv) 1))

        parse "iaprof" profile f &current-view

        &current-view @
            'add-widget "heatmap"
                (SSO-Heatmap 'new) profile "EU Stall"

        &current-view @ ('paint)

@on-key =
    fn (&key)
        &current-view @ ('on-key &key)

@on-mouse =
    fn (&type &action &button &row &col)
        &current-view @ ('on-mouse &type &action &button &row &col)
