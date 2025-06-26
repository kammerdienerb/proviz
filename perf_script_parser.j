parse-perf-script =
    fn (&profile &file &view)
        lines    = (fread-lines &file)
        length   = (len lines)
        update   = (length / (&view 'width))
        ln       = 0
        &def-evt = (&profile 'default-event)

        foreach &line lines
            if (len &line)
                if (not (startswith &line "\t"))
                    split-line = (split &line " ")

                    cmd-name = (move        (split-line 0))
                    pid      = (parse-int   (split-line 1))
                    time     = (parse-float (split-line 2))
                    count    = (parse-int   (split-line 3))
                    event    = (((split-line 4) =~ "(.*):$") 1)
                    stack    = ""

                    if (&def-evt == nil)
                        &def-evt = event

                else
                    matches = (&line =~ "[[:space:]]*([^[:space:]]+)[[:space:]]+([^+]+)")

                    sym = (move (matches 2))
                    if (startswith sym "[unknown]")
                        sym = (fmt "0x%%" (matches 1) (substr sym 9 ((len sym) - 9)))

                    if (len stack)
                        stack = (fmt "%;%" sym stack)
                    else
                        stack = sym

            else
                stack = (fmt "%;%;%" cmd-name pid (select (len stack) stack "[unknown]"))
                &profile @
                    'push-sample
                        object
                            'type  : event
                            'count : count
                            'time  : time
                            'stack : (&profile @ ('string-id stack))

            if (((++ ln) % update) == 0)
                &view @ ('loading-bar-update ((float ln) / length))

looks-like-perf-script =
    fn (&file)
        or
            endswith (&file '__path__) ".perf"
            endswith (&file '__path__) ".perf_script"
            do
                first-line = (fread-line &file)
                frewind &file
                matches = (first-line =~ "[[:space:]]*([^[:space:]]+)[[:space:]]+([^+]+)")
                matches != nil

register-parser          "perf-script" (' parse-perf-script)
register-format-detector "perf-script" (' looks-like-perf-script)
