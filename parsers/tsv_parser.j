parse-tsv =
    fn (&profile &file &view)
        lines         = (fread-lines &file)
        length        = (len lines)
        update        = (length / (&view 'width))
        ln            = 0

        foreach &line lines
            split-line = (split &line "\t")

            if ((len split-line) >= 3)
                stack = 0

                if ((len split-line) >= 4)
                    stack = (&profile @ ('string-id (split-line 3)))

                &profile @
                    'push-sample
                        object
                            'type  : (split-line 0)
                            'time  : (parse-float (split-line 1))
                            'stack : stack
                            'count : (parse-int (split-line 2))

            if (((++ ln) % update) == 0)
                &view @ ('loading-bar-update ((float ln) / length))

looks-like-tsv =
    fn (&file)
        endswith (&file '__path__) ".tsv"

register-parser          "tsv" (' parse-tsv)
register-format-detector "tsv" (' looks-like-tsv)
