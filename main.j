current-view := nil
profile      := nil

@on-init =
    fn (&rows &cols)

        current-view :=
            new-view
                'name : "main view"
                'rows : rows
                'cols : cols

        profile := (new-instance Profile)

        f = (fopen-rd ((argv) 1))

        (parsers "iaprof") profile f current-view

        @term:exit
