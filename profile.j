define-class Interval
    'start-time     : 0
    'end-time       : 0
    'events-by-type : (object)

    'push-event :
        fn (&self &type &sample)
            append
                get-or-insert (&self 'events-by-type) &type (list)
                move &sample

define-class Profile
    'strings       : (object)
    'intervals     : (list)
    'default-event : ""


    'new :
        fn ()
            new-instance Profile

    'push-interval :
        fn (&self &start-time &end-time)
            interval = (new-instance Interval)
            (interval 'start-time) = &start-time
            (interval 'end-time)   = &end-time

            append (&self 'intervals) (move interval)

    'push-event :
        fn (&self &type &sample)
            (last (&self 'intervals)) @ ('push-event &type &sample)
