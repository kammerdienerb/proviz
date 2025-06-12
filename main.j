current-view := nil

@on-init =
    fn (rows cols)

        current-view :=
            new-view
                'name : "main view"
                'rows : rows
                'cols : cols

        println current-view
        println parsers

        @term:exit
