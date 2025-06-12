parsers := (object)

register-parser =
    fn (format-name &parser-fn)
        if (format-name in parsers)
            wlog "reregistering % parser" format-name
            (parsers format-name) = &parser-fn
        else
            parsers <- (format-name : &parser-fn)
