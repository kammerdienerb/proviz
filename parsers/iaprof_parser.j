parse-iaprof =
    fn (&profile &file &view)
        lines                = (fread-lines &file)
        length               = (len lines)
        update               = (length / (&view 'width))
        ln                   = 0
        string-map           = (object)
        stall-reasons        = (list "active" "control" "pipestall" "send" "dist_acc" "sbid" "sync" "inst_fetch" "other" "tdr")
        current-kernel-stack = ""

        string-map <- ("0" : "<unknown>")

        foreach &line lines
            split-line = (split &line "\t")

            match (split-line 0)
                "eustall"
                    i = 3
                    foreach &reason stall-reasons
                        count = (parse-int (split-line i))
                        if (count > 0)
                            stack =
                                fmt "%;%_[g];%_[g];%_[g]"
                                    current-kernel-stack
                                    string-map (split-line 2)
                                    &reason
                                    (split-line 1)
                            &profile @
                                'push-sample
                                    object
                                        'type  : "iaprof:EU-stall"
                                        'time  : time
                                        'stack : (&profile @ ('string-id stack))
                                        'count : count
                        i += 1

                "kernel"
                    current-kernel-stack =
                        fmt "%;%;%;-;%_[G];%_[G]"
                            string-map (split-line 2)
                            parse-int  (split-line 3)
                            string-map (split-line 4)
                            string-map (split-line 5)
                            string-map (split-line 6)

                "string"
                    string-map <- ((split-line 1) : (split-line 2))

                "interval"
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
