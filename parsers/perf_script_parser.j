# Parses perf-script output. This is a bit of a complicated output
# due to the number of possible fields on the first line of each sample.
# As far as I can tell, the possibilities are:
# 1. The process name
# 2. The PID
# 3. (Optional) the TID
# 4. (Optional) square bracket number
# 5. Time, followed by a colon
# 6. (Optional) Count
# 7. Event name
# 8. Tracepoint fields. Can have multiple, separated by a comma and space.

parse-perf-script =
    fn (&profile &file &view)
        lines      = (fread-lines &file)
        length     = (len lines)
        update     = (length / (&view 'width))
        ln         = 0
        want-stack = 0

        foreach &line lines
            if (len &line)
                if (not (startswith &line "#"))
                    if (not (startswith &line "\t"))
                        split-line = (split &line " ")
                        line-len = (len split-line)

                        # Find the first field that ends with a colon. This is the time.
                        time-field = 0
                        event-field = 0
                        repeat i line-len
                            if (endswith (split-line i) ":")
                                if (time-field == 0)
                                    time-field = i
                                    time = (parse-float (split-line i))
                                elif (event-field == 0)
                                    event-field = i
                                    event = (fmt "perf:%" (substr (split-line i) 0 -1))

                        if (time-field == 0)
                            wlog (fmt "Failed to parse time from: %" &line)
                        if (event-field == 0)
                            wlog (fmt "Failed to parse event from: %" &line)

                        # Potentially get count from the second-to-last field
                        if (event-field == (time-field + 1))
                            count = 1
                        else
                            count = (parse-int (move (split-line (time-field + 1))))

                        # If the bracketed number is present, the PID is one field earlier
                        pid-field = (time-field - 1)
                        if (startswith ((split-line pid-field)) "[")
                            -- pid-field

                        pid-match = ((split-line pid-field) =~ "([0-9]+)/([0-9])")
                        if (pid-match != nil)
                            # We got a PID and TID
                            pid = (parse-int (pid-match 1))
                        else
                            pid = (parse-int (move (split-line pid-field)))

                        cmd-name = ""
                        repeat i pid-field
                            if (cmd-name == "")
                                cmd-name = (move (split-line i))
                            else
                                cmd-name = (fmt "% %" cmd-name (move (split-line i)))

                        addr-field = (event-field + 1)
                        if ((addr-field < line-len) and ((parse-hex (split-line addr-field)) != nil))
                            rest    = (move (last (split &line ":")))
                            matches = (rest =~ "[[:space:]]*([^[:space:]]+)[[:space:]]+([^+]+)")
                            sym     = (move (matches 2))

                            if (startswith sym "[unknown]")
                                sym = (fmt "0x%%" (matches 1) (substr sym 9 -9))

                            stack = (fmt "%;%;%" cmd-name pid sym)
                            &profile @
                                'push-sample
                                    object
                                        'type  : event
                                        'count : count
                                        'time  : time
                                        'stack : (&profile @ ('string-id stack))
                            want-stack = 0
                        else
                            stack = ""
                            want-stack = 1

                    elif want-stack
                        matches = (&line =~ "[[:space:]]*([^[:space:]]+)[[:space:]]+([^+]+)")

                        sym = (move (matches 2))
                        if (startswith sym "[unknown]")
                            sym = (fmt "0x%%" (matches 1) (substr sym 9 -9))

                        if (len stack)
                            stack = (fmt "%;%" sym stack)
                        else
                            stack = sym

            elif want-stack
                stack = (fmt "%;%;%" cmd-name pid (select (len stack) stack "[unknown]"))
                &profile @
                    'push-sample
                        object
                            'type  : event
                            'count : count
                            'time  : time
                            'stack : (&profile @ ('string-id stack))
                want-stack = 0

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
