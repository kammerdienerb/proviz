make-eustall =
    fn (&count &stack)
        object
            'type  : "EU Stall"
            'count : &count
            'stack : &stack

parse-iaprof =
    fn (&profile &file &view)
        lines  = (fread-lines &file)
        length = (len lines)

        &interval-time = (options 'interval-time)
        &strings       = (&profile 'strings)

        cur-time = 0
        foreach &line lines
            split-line = (split &line "\t")
            match (split-line 0)
                "e"
                    &profile @
                        'push-event "EU Stall"
                            make-eustall (parse-int (split-line 4)) (split-line 1)

                "string"
                    &strings <- ((split-line 1) : (split-line 2))

                "interval_start"
                    time = (parse-float (split-line 2))

                    if (cur-time == 0)
                        cur-time = time
                        &profile @ ('push-interval cur-time (cur-time + (&interval-time)))

                    elif (time >= (cur-time + (&interval-time)))
                        num-elapsed = (sint ((time - cur-time) / &interval-time))
                        repeat i num-elapsed
                            &profile @ ('push-interval (cur-time + (&interval-time * (i))) (cur-time + (&interval-time * (i + 1))))
                        cur-time += (&interval-time * num-elapsed)


register-parser "iaprof" parse-iaprof
