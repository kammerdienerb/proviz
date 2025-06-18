parsers := (object)

register-parser =
    fn (&format-name &parser-fn-sym)
        if (&format-name in parsers)
            wlog "reregistering % parser" &format-name
            (parsers &format-name) = &parser-fn-sym
        else
            parsers <- (&format-name : &parser-fn-sym)

parse =
    fn (&format-name &profile &file &view)
        if (&format-name in parsers)
            &sym = (parsers &format-name)
            (&sym) &profile &file &view
        else
            elog "parser '%' not registered" &format-name

