parse-perf-script =
    fn (&profile &file &view)
        lines  = (fread-lines &file)
        length = (len lines)

        &interval-time = (options 'interval-time)
        &strings       = (&profile 'strings)

        &view @ ('loading-bar-init "Loading profile")

        update = (length / (&view 'width))

        stacks = (object)
        sid = 1

        ln = 0
        cur-time = 0
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

                    if (cur-time == 0)
                        cur-time = time
                        &profile @
                            'push-interval
                                cur-time
                                cur-time + &interval-time

                        (&profile 'default-event) = event

                    elif (time >= (cur-time + &interval-time))
                        num-elapsed = (sint ((time - cur-time) / &interval-time))
                        repeat i num-elapsed
                            &profile @
                                'push-interval
                                    cur-time + (&interval-time * i)
                                    cur-time + (&interval-time * (i + 1))
                        cur-time += (&interval-time * num-elapsed)
                else
                    matches = (&line =~ "[[:space:]]*([^[:space:]]+)[[:space:]]+([^+]+)")
                    sym = (move (matches 2))
#                     if (startswith sym "[unknown]")
#                         sym = (fmt "0x%%" (matches 1) (substr sym 9 ((len sym) - 9)))
#                     stack =
#                         select (len stack)
#                             fmt "%;%" sym stack
#                             sym
                    if (not (startswith sym "[unknown]"))
                        stack =
                            select (len stack)
                                fmt "%;%" sym stack
                                sym
            else
                sample =
                    object
                        'count : count
                if (len stack)
                    stack = (fmt "%;%;%" cmd-name pid stack)
                    if (stack in stacks)
                        stack-id = (stacks stack)
                    else
                        stacks <- (stack : sid)
                        stack-id = sid
                        sid += 1
                    sample <- ('stack : stack-id)
                &profile @ ('push-event event (move sample))


            ln += 1
            if ((ln % update) == 0)
                &view @ ('loading-bar-update ((float ln) / length))

        &view @ ('loading-bar-fini)

        foreach stack stacks
            &strings <- ((stacks stack) : stack)


register-parser "perf-script" (' parse-perf-script)
