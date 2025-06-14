define-class Interval
    'start-time     : 0
    'end-time       : 0
    'events-by-type : (object)

    'push-event :
        fn (&self &type &sample)
            append
                get-or-insert (&self 'events-by-type) &type (list)
                move &sample

new-interval =
    fn (&start-time &end-time)
        interval = (new-instance Interval)
        (interval 'start-time) = &start-time
        (interval 'end-time)   = &end-time
        interval

define-class Profile
    'strings   : (object)
    'intervals : (list)

    'push-interval :
        fn (&self &start-time &end-time)
            append (&self 'intervals)
                new-interval &start-time &end-time

    'push-event :
        fn (&self &type &sample)
            &intervals = (&self 'intervals)
            &last-interval = (&intervals ((len &intervals) - 1))
            &last-interval @ ('push-event &type &sample)
