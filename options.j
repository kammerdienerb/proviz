options-def :=
    object
        'interval-time :
            list
                "float"
                0.05
                "Quantize samples into intervals of this time period (seconds)."
        'max-time-skip :
            list
                "float"
                10.0
                "Throw an error when the time between two consecutive samples exceeds this value (seconds)."
        'new-metric :
            list
                "string"
                nil
                "Create a new metric. String must be of the form 'METRIC-NAME = JULIE-EXPRESSION'. Valid event names in the profile can be referenced in the expression. May be repeated."
        'metrics-file :
            list
                "string"
                nil
                "Path to a file containing Julie code used to define new metrics. The last expression must be an object that maps metric names to thier values."

list-cmds :=
    list
        "report"
        "plot"
        "flamegraph"
        "flamescope"
        "thiefscope"

options := (object)
foreach name options-def
    default-value = ((options-def name) 1)
    options <- (name : default-value)

options <- ('FILES               : (list))
options <- ('METRICS             : (object))
options <- ('METRICS-FILE-STRING : "")

option-name-to-arg =
    fn (&option-name)
        s = (string &option-name)
        s = (substr s 1 -1)
        s = (fmt "--%" s)
        s

usage =
    fn ()
        u =      "USAGE: proviz COMMAND [OPTIONS...] [FILE...]\n\n"
        u =
            fmt "%COMMAND may be one of the following:\n" u
        foreach cmd list-cmds
            u = (fmt "%  %\n" u cmd)
        u = (fmt "%\n" u)
        u =
            fmt "%Each input FILE may be of the form FILE,FORMAT where FORMAT is one of the following:\n" u
        foreach format (keys parsers)
            u = (fmt "%  %\n" u format)
        u = (fmt "%\n" u)
        u =
            fmt "%OPTIONS:\n" u
        foreach option (keys options-def)
            u =
                fmt "%  % % %\n    %\n\n"
                    u
                    option-name-to-arg option
                    (options-def option) 0
                    select (((options-def option) 1) == nil) "" (fmt "(default: %)" ((options-def option) 1))
                    (options-def option) 2
        u =
            fmt "%  --help\n    Show this help.\n\n" u
        u

parse-cmdline-options =
    fn (args)
        shift = (lambda (&args) (erase &args 0))

        shift args # don't want argv[0]

        arg-map = (object)
        foreach option (keys options-def)
            arg-map <- ((option-name-to-arg option) : option)

        got-cmd = 0

        while (len args)
            arg = (args 0)

            if (startswith arg "-")
                if (arg == "--help")
                    print (usage)
                    @term:exit

                if (not (arg in arg-map))
                    die "unknown option '%'\n\n%" arg (usage)

                option = (arg-map arg)

                shift args

                if ((len args) == 0)
                    die "missing value for arg %\n\n%" arg (usage)

                value = (args 0)

                match ((options-def option) 0)
                    "string"
                        value = value

                    "int"
                        i = (parse-int value)
                        if (i == nil)
                            die "bad int value '%' for arg %\n\n%" value arg (usage)
                        value = i

                    "float"
                        f = (parse-float value)
                        if (f == nil)
                            die "bad float value '%' for arg %\n\n%" value arg (usage)
                        value = f

                if (option == 'new-metric)
                    matches = (value =~ "[[:space:]]*([^[:space:]()]+)[[:space:]]*=[[:space:]]*(.*)")
                    if (matches == nil)
                        die "invalid new-metric string '%'\n\n%" value (usage)

                    (options 'METRICS) <- ((matches 1) : (matches 2))

                elif (option == 'metrics-file)
                    (options option) = value

                    f = (fopen-rd value)
                    if (f == nil)
                        die "unable to open metrics-file '%'" value

                    s = ""
                    delim = ""
                    foreach &line (fread-lines f)
                        s = (fmt "%%%" (move s) delim (move &line))
                        delim = "\n"

                    fclose f

                    (options 'METRICS-FILE-STRING) = (move s)

                else
                    (options option) = value

            elif got-cmd
                parts = (split arg ",")

                if ((len parts) == 1)
                    path   = arg
                    format = "auto-detect"

                elif ((len parts) == 2)
                    path   = (parts 0)
                    format = (parts 1)

                else
                    die "invalid argument '%'\n\n%" arg (usage)

                append (options 'FILES) (path : format)

            else
                if (not (arg in list-cmds))
                    die "unknown command '%'\n\n%" arg (usage)

                options <- ('COMMAND : arg)
                got-cmd = 1

            shift args

        if (not got-cmd)
            die "missing COMMAND\n\n%" (usage)
