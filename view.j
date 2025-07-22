views = (object)

define-class View
    'height            : 0
    'width             : 0
    'loading-bar-label : ""
    'widgets           : (object)
    'vert-offset       : 0
    'horiz-offset      : 0

    'new :
        fn (&height &width ...)
            view = (new-instance View)
            view <- ('height : &height)
            view <- ('width  : &width)
            foreach &arg ... (view <- &arg)
            move view

    'add-widget :
        fn (&self &name &widget)
            (&self 'widgets) <- (&name : &widget)

    'clear :
        fn (&self)
            @term:clear

    'status-text :
        fn (&self &text)
            @term:clear-row 1
            col = 1
            foreach char (chars &text)
                @term:set-cell-fg   1 col 0x00ffff
                @term:set-cell-char 1 col char
                ++ col

    'paint :
        fn (&self)
            &self @ ('clear)

            by-layer = (list)

            foreach widget-name (&self 'widgets)
                append by-layer
                    widget-name :
                        get-or-insert ((&self 'widgets) widget-name) 'layer 0

            by-layer =
                sorted (move by-layer)
                    fn (a b) ((a 1) < (b 1))

            foreach &pair by-layer
                widget-name = (&pair 0)
                ((&self 'widgets) widget-name) @ ('paint &self (&self 'vert-offset) (&self 'horiz-offset))
            @term:flush

    'loading-bar-init :
        fn (&self &label)
            (&self 'loading-bar-label) = &label

            text = (fmt "% 0\%" &label)

            @term:clear-row 1
            col = 1
            foreach char (chars text)
                @term:set-cell-fg   1 col 0x0000ff
                @term:set-cell-char 1 col char
                col += 1
            @term:flush

    'loading-bar-fini :
        fn (&self)
            (&self 'loading-bar-label) = ""
            @term:clear-row 1
            @term:flush

    'loading-bar-update :
        fn (&self &ratio)
            repeat col (sint (&ratio * (&self 'width)))
                @term:set-cell-bg   1 (col + 1) 0xffffff
                @term:set-cell-char 1 (col + 1) " "

            text = (fmt "% %\%" (&self 'loading-bar-label) (sint (100.0 * &ratio)))

            col = 1
            foreach char (chars text)
                @term:set-cell-fg   1 col 0x0000ff
                @term:set-cell-char 1 col char
                col += 1

            @term:flush

    'on-key :
        fn (&self &key)
            if ('input-handler in &self)
                (&self 'input-handler) @ ('on-key &self &key)

    'on-mouse :
        fn (&self &type &action &button &row &col)
            if ('input-handler in &self)
                (&self 'input-handler) @ ('on-mouse &self &type &action &button &row &col)

    'set-input-handler :
        fn (&self &input-handler)
            (&self 'input-handler) = &input-handler

set-view =
    fn (&view-name)
        if (is-bound &current-view)
            @term:clear
            unref &current-view
        if (not (&view-name in views))
            die "no view named %" &view-name
        &current-view := (views &view-name)
        (&current-view 'height) = rows
        (&current-view 'width)  = cols
        &current-view @ ('paint)
