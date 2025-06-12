log =
    fn (type message)
        prefix = ""
        match type
            'error : (prefix = "WARNING: ")
            'warn  : (prefix = "ERROR:   ")
            'info  : (prefix = "INFO:    ")

        print prefix
        println message

log-fmt =
    fn (&format-string &fmt-args)
        fmt-call = (list (` fmt) &format-string)
        foreach &arg &fmt-args (append fmt-call &arg)
        ((fmt-call))

elog =
    fn (format-string ...)
        log 'error (log-fmt format-string ...)
wlog =
    fn (format-string ...)
        log 'warn (log-fmt format-string ...)
ilog =
    fn (format-string ...)
        log 'info (log-fmt format-string ...)
