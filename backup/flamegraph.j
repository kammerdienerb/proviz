###########################################################
# Flame Graph Command
###########################################################

key-actions =
    object
        "q" : (' (@term:exit) )

@on-key =
    fn (key)
        if (key in key-actions)
            (key-actions key)

@on-mouse =
    fn (type action button row col)
        if ((action == 'down) and (button == 'left))
            foreach &elem (view 'elements)
                if (('on-click in &elem) and (in-element &elem row col))
                    (&elem 'on-click) &elem row col

# redraw =
#     fn (rows cols)
#         flame-graph-view := (make-view rows cols)
#         create-flame-elements
#         paint view

@on-init =
    fn (rows cols)
        loading-bar-view := (make-view rows cols)
        loading-bar      := (make-loading-bar loading-bar-view 1 "PROFILE")
        profile          := (make-profile)
        
        # Parse the profile
        parse-profile ((argv) 1) profile loading-bar
        
        render-flamegraph profile 0 ((len (profile 'intervals)) - 1) rows cols loading-bar

# @on-resize =
#     fn (rows cols)
#         redraw rows cols
