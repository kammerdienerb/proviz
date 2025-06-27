ends-in-colon-regex = "(.*):$"
pid-regex = "([0-9]+)/([0-9])"

parse-perf-script =
    fn (&profile &file &view)
        lines    = (fread-lines &file)
        length   = (len lines)
        update   = (length / (&view 'width))
        ln       = 0

        foreach &line lines
            if (len &line)
                if ((not (startswith &line "\t")) and (not (startswith &line "#")))
                    split-line = (split &line " ")
                    line-len = (len split-line)
                    
                    # The last field is always the event name
                    event-match  = ((move (split-line (line-len - 1))) =~ ends-in-colon-regex)
                    event = (event-match 1)
                    
                    # Potentially get count from the second-to-last field
                    if (endswith (split-line (line-len - 2)) ":")
                        # Time is the second-to-last field, so there's no count
                        count = 1
                        time-field = 2
                    else
                        # Count is the second-to-last field, and time is the third-to-last
                        count = (parse-int (move (split-line (line-len - 2))))
                        time-field = 3
                    
                    # Based on if count was there or not, get time (which will end in a colon)
                    time-match = ((move (split-line (line-len - time-field))) =~ ends-in-colon-regex)
                    if (time-match != nil)
                        time = (parse-float (time-match 1))
                    else
                        wlog (fmt "Failed to parse time from: %" &line)
                        time = 0
                      
                    # If the bracketed number is present, the PID is one field earlier
                    pid-field = (time-field + 1)
                    if (startswith ((split-line (line-len - pid-field))) "[")
                        pid-field = (pid-field + 1)
                        
                    pid-match = ((split-line (line-len - pid-field)) =~ pid-regex)
                    if (pid-match != nil)
                        # We got a PID and TID
                        pid = (parse-int (pid-match 1))
                    else
                        pid = (parse-int (move (split-line (line-len - pid-field))))
                        
                    cmd-name = ""
                    repeat i (line-len - pid-field)
                        if (cmd-name == "")
                            cmd-name = (move (split-line i))
                        else
                            cmd-name = (fmt "% %" cmd-name (move (split-line i)))
                        
                    stack = ""
                    leaf = "[unknown]"
                elif (not (startswith &line "#"))
                        
                    matches = (&line =~ "[[:space:]]*([^[:space:]]+)[[:space:]]+([^+]+)")

                    sym = (move (matches 2))
                    if (startswith sym "[unknown]")
                        sym = (fmt "0x%%" (matches 1) (substr sym 9 ((len sym) - 9)))

                    if (len stack)
                        stack = (fmt "%;%" sym stack)
                    else
                        stack = sym
                        leaf  = sym

            else
                stack = (fmt "%;%;%" cmd-name pid (select (len stack) stack leaf))
                &profile @
                    'push-sample
                        object
                            'type  : event
                            'count : count
                            'time  : time
                            'stack : (&profile @ ('string-id stack))
                            'leaf  : (&profile @ ('string-id leaf))

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
