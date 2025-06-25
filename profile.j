define-class Interval
    'start-time     : 0
    'end-time       : 0
    'events-by-type : (object)

    'push-sample :
        fn (&self &sample)
            append
                get-or-insert (&self 'events-by-type) (&sample 'type) (list)
                move &sample

sample-time-cmp =
    fn (&a &b)
        (&a 'time) < (&b 'time)

define-class Profile
    'strings       : (object)
    'sid           : 0
    'samples       : (list)
    'intervals     : (list)
    'default-event : nil


    'new :
        fn ()
            new-instance Profile

    'string-id :
        fn (&self &s)
            get-or-insert (&self 'strings) &s (++ (&self 'sid))

    'get-string :
        fn (&id)
            (&self 'strings) &id

    'push-sample :
        fn (&self &sample)
            sorted-insert (&self 'samples) (move &sample) sample-time-cmp

    'postprocess :
        fn (&self &view)
            length         = ((len (&self 'samples)) + (len (&self 'strings)))
            update         = (length / (&view 'width))
            ln             = 0
            cur-time       = 0
            &def-evt       = (&self 'default-event)
            &interval-time = (options 'interval-time)

            foreach &sample (&self 'samples)
                if (&def-evt == nil)
                    &def-evt = (&sample 'type)

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

            foreach s strings
                (&self 'strings) <- ((strings s) : (move s))

                if (((++ ln) % update) == 0)
                    &view @ ('loading-bar-update ((float ln) / length))
