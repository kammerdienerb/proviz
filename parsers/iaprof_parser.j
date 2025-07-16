parse-iaprof =
    fn (&profile &file &view)
        lines         = (fread-lines &file)
        length        = (len lines)
        update        = (length / (&view 'width))
        ln            = 0
        string-id-map = (object)

        foreach &line lines
            split-line = (split &line "\t")

            match (split-line 0)
                "e"
                    &profile @
                        'push-sample
                            object
                                'type  : "iaprof:EU-stall"
                                'time  : time
                                'stack : (string-id-map (parse-int (split-line 1)))
                                'count : (parse-int (split-line 4))

                "string"
                    string-id-map <-
                        (parse-int (split-line 1)) :
                            &profile @ ('string-id (split-line 2))

                "interval_start"
                    time = (parse-float (split-line 2))

                "metric"
                    &profile @
                        'push-sample
                            object
                                'type  : (fmt "iaprof:%" (move (split-line 1)))
                                'time  : time
                                'stack : 0
                                'count : (parse-int (split-line 2))

            if (((++ ln) % update) == 0)
                &view @ ('loading-bar-update ((float ln) / length))

looks-like-iaprof =
    fn (&file)
        or
            endswith (&file '__path__) ".iaprof"
            do
                first-line = (fread-line &file)
                frewind &file
                first-line == "string\t1\t[unknown file]"

register-parser          "iaprof" (' parse-iaprof)
register-format-detector "iaprof" (' looks-like-iaprof)

register-accum-fn "iaprof:frequency-MHz" (' sample-accum-avg)
register-accum-fn "iaprof:busy-percent"  (' sample-accum-avg)
