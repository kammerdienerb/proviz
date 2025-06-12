define-class View

new-view =
    fn (...)
        view = (new-instance View)
        foreach &arg ... (view <- &arg)
        view
