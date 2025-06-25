parsers   := (object)
detectors := (object)

register-parser =
    fn (&format-name &parser-fn-sym)
        if (&format-name in parsers)
            wlog "reregistering % parser" &format-name
            (parsers &format-name) = &parser-fn-sym
        else
            parsers <- (&format-name : &parser-fn-sym)

register-format-detector =
    fn (&format-name &detector-fn-sym)
        if (&format-name in detectors)
            wlog "reregistering % detector" &format-name
            (detectors &format-name) = &detector-fn-sym
        else
            detectors <- (&format-name : &detector-fn-sym)

parse =
    fn (format &profile &file &view)
        if (format == "auto-detect")
            format = nil
            foreach f detectors
                if ((format == nil) and (((detectors f)) &file))
                    format = f
            if (format == nil)
                die "unable to auto-detect format for %" (&file '__path__)

        if (format in parsers)
            ((parsers format)) &profile &file &view
        else
            die "parser '%' not registered" format
