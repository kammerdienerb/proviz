parse-iaprof =
    fn (&file &view)
        ilog "iaprof parser"

register-parser "iaprof" parse-iaprof
