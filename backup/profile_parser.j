make-profile =
    fn (...)
        o =
            object
                'largest-count : 0
                'intervals     : (list)
                'interval-time : 0.02
                'strings       : (object)
        foreach &arg ...
            o <- &arg
        o

make-interval =
    fn (start end)
        object
            'start  : start
            'end    : end
            'count  : 0
            'stalls : (list)

newest-interval = (' ((&profile 'intervals) ((len (&profile 'intervals)) - 1)) )

make-stall =
    fn (count stack)
        object
            'count : count
            'stack : stack
            
parse-profile =
    fn (filename &profile &loading-bar)
        f = (fopen-rd filename)
        lines = (fread-lines f)
        length = (len lines)
        
        loading-bar-update &loading-bar 0.0
        
        &interval-time = (&profile 'interval-time)
        &intervals     = (&profile 'intervals)
        &strings       = (&profile 'strings)
        
        index = 0
        cur-time = 0
        update = (length / ((&loading-bar 'view) 'cols))
        foreach &line lines
            split-line = (split &line "\t")
            match (split-line 0)
                "e"
                    count = (parse-int (split-line 4))
                    append &cur-stalls
                        make-stall count (split-line 1)
                    &cur-count += count

                "string"
                    &strings <- ((split-line 1) : (split-line 2))
                    
                "interval_start"
                    time = (parse-float (split-line 2))
                    
                    # Initial interval
                    if (cur-time == 0)
                        cur-time = time
                        append &intervals
                            make-interval cur-time (cur-time + (&interval-time))
                        &cur-interval = (newest-interval)
                        &cur-stalls   = (&cur-interval 'stalls)
                        &cur-count    = (&cur-interval 'count)
                        
                    # Should we create more intervals? */
                    if (time >= (cur-time + (&interval-time)))
                    
                        # Update largest-count
                        if (&cur-count > (&profile 'largest-count))
                            (&profile 'largest-count) = &cur-count
                            
                        # Create num-elapsed intervals
                        num-elapsed = (sint ((time - cur-time) / &interval-time))
                        repeat i num-elapsed
                            append &intervals
                                make-interval (cur-time + (&interval-time * (i))) (cur-time + (&interval-time * (i + 1)))
                        cur-time += (&interval-time * num-elapsed)
                        
                        # Update cur-interval
                        unref &cur-interval
                        unref &cur-stalls
                        unref &cur-count
                        &cur-interval = (newest-interval)
                        &cur-stalls   = (&cur-interval 'stalls)
                        &cur-count    = (&cur-interval 'count)
            
            if ((index % update) == 0)
                loading-bar-update &loading-bar ((float index) / length)
                
            index += 1
        loading-bar-update &loading-bar 1.0
            
        fclose f
