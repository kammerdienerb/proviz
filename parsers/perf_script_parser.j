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
                    
                    # Find the last field that ends in a colon. We'll assume that this
                    # is the event name. We'll also only consider the 5th, 6th, or 7th fields.
                    event-field = 0
                    repeat i line-len
                        event-match  = ((split-line i) =~ ends-in-colon-regex)
                        if (event-match != nil)
                            event = (event-match 1)
                            event-field = i
                    if (event-field == 0)
                        wlog (fmt "Failed to parse event from: %" &line)
                    
                    # Potentially get count from the second-to-last field
                    if (endswith (split-line (event-field - 1)) ":")
                        # Time is the second-to-last field, so there's no count
                        count = 1
                        time-field = (event-field - 1)
                    else
                        # Count is the second-to-last field, and time is the third-to-last
                        count = (parse-int (move (split-line (event-field - 1))))
                        time-field = (event-field - 2)
                    
                    # Based on if count was there or not, get time (which will end in a colon)
                    time-match = ((move (split-line time-field)) =~ ends-in-colon-regex)
                    if (time-match != nil)
                        time = (parse-float (time-match 1))
                    else
                        wlog (fmt "Failed to parse time from: %" &line)
                        time = 0
                      
                    # If the bracketed number is present, the PID is one field earlier
                    pid-field = (time-field - 1)
                    if (startswith ((split-line pid-field)) "[")
                        -- pid-field
                        
                    pid-match = ((split-line pid-field) =~ pid-regex)
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
