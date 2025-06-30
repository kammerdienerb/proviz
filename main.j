rows    := 0
cols    := 0
profile := nil

@on-init =
    fn (&rows &cols)
        rows := &rows
        cols := &cols

        parse-cmdline-options (argv)

        views <-
            "main" :
                (View 'new) &rows &cols
                    'name          : "main view"
                    'input-handler : nil

        set-view "main"

        profile := ((Profile 'new))

        foreach pair (options 'FILES)
            path   = (pair 0)
            format = (pair 1)

            f = (fopen-rd path)

            &current-view @ ('loading-bar-init (fmt "Loading %" (f '__path__)))
            parse format profile f &current-view
            &current-view @ ('loading-bar-fini)

            fclose f

        &current-view @ ('loading-bar-init (fmt "Processing profile..."))
        profile @ ('postprocess &current-view)
        &current-view @ ('loading-bar-fini)

        match (options 'COMMAND)
            "flamescope"
                (flamescope-command profile)
                
            "thiefscope"
                (thiefscope-command profile)
            
            "flamegraph"
                (flamegraph-command profile)

        &current-view @ ('paint)

@on-key =
    fn (&key)
        &current-view @ ('on-key &key)

@on-mouse =
    fn (&type &action &button &row &col)
        &current-view @ ('on-mouse &type &action &button &row &col)
        
@on-resize =
    fn (&rows &cols)
        (&current-view 'height) = &rows
        (&current-view 'width) = &cols
        &current-view @ ('paint)
