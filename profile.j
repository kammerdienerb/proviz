sample-accum-fns := (object)

register-accum-fn =
    fn (&event-name &accum-fn-sym)
        if (&event-name in sample-accum-fns)
            wlog "reregistering % accumulator function" &event-name
            (sample-accum-fns &event-name) = &accum-fn-sym
        else
            sample-accum-fns <- (&event-name : &accum-fn-sym)

sample-accum-sum =
    fn (&samples)
        sum = 0
        foreach &sample &samples
            sum += (&sample 'count)
        sum

sample-accum-avg =
    fn (&samples)
        sum = 0
        if (len &samples)
            foreach &sample &samples
                sum += (&sample 'count)
            sum /= (len &samples)
        sum

accum-samples =
    fn (&event-name &samples)
        select (&event-name in sample-accum-fns)
            ((sample-accum-fns &event-name)) &samples
            sample-accum-sum &samples

define-class Interval
    'start-time          : 0
    'end-time            : 0
    'events-by-type      : (object)
    'event-count-by-type : (object)
    'event-accum-by-type : (object)

    'push-sample :
        fn (&self &sample)
            (get-or-insert (&self 'event-count-by-type) (&sample 'type) 0) += (&sample 'count)
            append
                get-or-insert (&self 'events-by-type) (&sample 'type) (list)
                move &sample

    'accum :
        fn (&self)
            foreach event-name (&self 'events-by-type)
                (&self 'event-accum-by-type) <-
                    event-name : (accum-samples event-name ((&self 'events-by-type) event-name))

sample-time-cmp =
    fn (&a &b)
        (&a 'time) < (&b 'time)

define-class Profile
    'strings             : (object)
    'sid                 : 0
    'samples             : (list)
    'intervals           : (list)
    'event-count-by-type : (object)
    'default-event       : nil

    'new :
        fn ()
            p = (new-instance Profile)

            (p 'strings) <- ("" : 0)

            p

    'string-id :
        fn (&self &s)
            get-or-insert (&self 'strings) &s (++ (&self 'sid))

    'get-string :
        fn (&self &id)
            (&self 'strings) &id

    'push-sample :
        fn (&self &sample)
            sorted-insert (&self 'samples) (move &sample) sample-time-cmp

    'postprocess :
        fn (&self &view)
            length         = (len (&self 'samples))
            update         = (length / (&view 'width))
            ln             = 0
            cur-time       = 0
            &interval-time = (options 'interval-time)
            &def-evt       = (&self 'default-event)

            foreach &sample (&self 'samples)
                if (&def-evt == nil)
                    &def-evt = (&sample 'type)
                ++ (get-or-insert (&self 'event-count-by-type) (&sample 'type) 0)

                time = (&sample 'time)

                if (cur-time == 0)
                    cur-time = time

                    interval = (new-instance Interval)
                    (interval 'start-time) = cur-time
                    (interval 'end-time)   = (cur-time + &interval-time)
                    append (&self 'intervals) (move interval)

                    &cur-interval = (last (&self 'intervals))

                elif (time >= (cur-time + &interval-time))
                    if ((time - cur-time) > (options 'max-time-skip))
                        die "% seconds between samples exceeds max-time-skip" (time - cur-time)

                    num-elapsed = (sint ((time - cur-time) / &interval-time))
                    repeat i num-elapsed
                        interval = (new-instance Interval)
                        (interval 'start-time) = (cur-time + (&interval-time * i))
                        (interval 'end-time)   = (cur-time + (&interval-time * (i + 1)))
                        append (&self 'intervals) (move interval)

                    cur-time += (&interval-time * num-elapsed)

                    unref &cur-interval
                    &cur-interval = (last (&self 'intervals))

                &cur-interval @ ('push-sample &sample)

                if (((++ ln) % update) == 0)
                    &view @ ('loading-bar-update ((float ln) / length))

            &self -> 'samples

            strings = (move (&self 'strings))
            (&self 'strings) = (object)

            length = (len (&self 'strings))
            update = (length / (&view 'width))
            ln     = 0

            foreach s strings
                (&self 'strings) <- ((strings s) : (move s))

                if (((++ ln) % update) == 0)
                    &view @ ('loading-bar-update ((float ln) / length))

            length = (len (&self 'intervals))
            update = (length / (&view 'width))
            ln     = 0

            init-bindings = (object)
            foreach event (&self 'event-count-by-type)
                init-bindings <- ((symbol event) : 0)

            foreach &interval (&self 'intervals)
                &interval @ ('accum)

                foreach user-metric (options 'METRICS)
                    bindings = init-bindings
                    foreach event (&interval 'event-accum-by-type)
                        bindings <- ((symbol event) : ((&interval 'event-accum-by-type) event))

                    formula = ((options 'METRICS) user-metric)
                    result  = (eval-sandboxed formula bindings)
                    count   = (result 0)
                    t       = (typeof count)

                    if (((result 1) 'status) != 0)
                        die "problem computing new-metric expression\n%" ((result 1) 'error-message)
                    elif
                        or
                            t == "signed integer"
                            t == "unsigned integer"
                            t == "float"

                        &interval @
                            'push-sample
                                object
                                    'type  : user-metric
                                    'time  : (&interval 'start-time)
                                    'count : count

                        (&interval 'event-accum-by-type) <-
                            user-metric : (accum-samples user-metric ((&interval 'events-by-type) user-metric))

                        ++ (get-or-insert (&self 'event-count-by-type) user-metric 0)

                if (((++ ln) % update) == 0)
                    &view @ ('loading-bar-update ((float ln) / length))
