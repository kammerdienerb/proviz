define-class Report-Menu
    'height            : 0
    'width             : 0
    'layer             : 1
    'events            : (list)
    'event-width       : 0
    'count-width       : 0
    'start-row         : 0
    'num-rows          : 0
    'selected-idx      : nil
    'activated-indices : (list)

    'new :
        fn ()
            menu = (new-instance Report-Menu)

            max-event-width = 0
            max-count-width = 0

            (menu 'events) = (sorted (keys (&report-profile 'event-count-by-type)))

            foreach event (menu 'events)
                event-width = (len (chars event))
                count-width = (len (chars (string ((&report-profile 'event-count-by-type) event))))

                max-event-width = (max max-event-width event-width)
                max-count-width = (max max-count-width count-width)

                ++ (menu 'num-rows)

            (menu 'width)       = ((max-event-width + max-count-width) + 12)
            (menu 'event-width) = max-event-width
            (menu 'count-width) = max-count-width

            menu

    'paint :
        fn (&self &view &vert-offset &horiz-offset)
            (&self 'height) = ((&view 'height) - 1)

            repeat row (&self 'height)
                row += 2
                repeat col (&self 'width)
                    col += 1
                    @term:unset-cell-bg row col
                    @term:set-cell-fg   row col 0xffffff
                    @term:set-cell-char row col " "

            row = 2
            foreach event (&self 'events)
                text =
                    fmt " % % samples "
                        spad (0 - (&self 'event-width)) event
                        spad (&self 'count-width) (string ((&report-profile 'event-count-by-type) event))

                idx = (row - 2)

                col = 1
                foreach char (chars text)
                    if ((&self 'selected-idx) == idx)
                        @term:set-cell-bg   row col 0xffffff
                        @term:set-cell-fg   row col 0x000000
                    elif (idx in (&self 'activated-indices))
                        @term:set-cell-bg   row col 0x505050
                        @term:set-cell-fg   row col 0xffffff
                    else
                        @term:unset-cell-bg row col
                        @term:set-cell-fg   row col 0xffffff

                    @term:set-cell-char row col char
                    ++ col

                ++ row

            col = (&self 'width)
            repeat row (&self 'height)
                row += 2
                @term:set-cell-fg   row col 0xffffff
                @term:set-cell-char row col "│"


    'mouse-over :
        fn (&self &view &row &col)
            response = nil
            if
                and
                    &row > 1
                    &row < ((&self 'num-rows) + 2)
                    &col < (&self 'width)

                (&self 'selected-idx) = (&row - 2)
                &self @ ('paint &view 0 0)
                @term:flush

            else
                had-selection = ((&self 'selected-idx) != nil)
                (&self 'selected-idx) = nil
                if had-selection
                    &self @ ('paint &view 0 0)
                    @term:flush

            response

    'mouse-click :
        fn (&self &view &row &col)
            response = nil

            if
                and
                    &row > 1
                    &row < ((&self 'num-rows) + 2)
                    &col < (&self 'width)

                idx = (&row - 2)
                (&self 'selected-idx) = idx


                if (idx in (&self 'activated-indices))
                    erase (&self 'activated-indices)
                        index (&self 'activated-indices) idx
                    response = 'report-remove-widget
                else
                    append (&self 'activated-indices) idx
                    response = 'report-add-widget

            response
