### DRAWING ###
make-view =
    fn (rows cols ...)
        o =
            object
                'elements : (list)
                'rows     : rows
                'cols     : cols
        foreach arg ... (o <- arg)
        o

paint-view =
    fn (&view)
        @term:clear
        foreach &element (&view 'elements)
            ((&element 'paint-fn)) &element
        @term:flush

add-element =
    fn (&view elem)
        append (&view 'elements) elem
newest-element-index =
    fn (&view)
        ((len (&view 'elements)) - 1)

make-text =
    fn (row col s ...)
        o =
            object
                'type     : 'rect
                'paint-fn : (' paint-text)
                'row      : row
                'col      : col
                's        : s
        foreach arg ... (o <- arg)
        o

paint-text =
    fn (&text)
        row    = (&text 'row)
        col    = (&text 'col)
        tcolor = (select ('color in &text) (&text 'color) nil)
        foreach char (chars (&text 's))
            if (tcolor != nil)
                @term:set-cell-fg row col tcolor
            @term:set-cell-char row col char
            col += 1

make-rect =
    fn (row col height width color ...)
        o =
            object
                'type     : 'rect
                'paint-fn : (' paint-rect)
                'row      : row
                'col      : col
                'height   : height
                'width    : width
                'color    : color
        foreach arg ... (o <- arg)
        o

paint-rect =
    fn (&rect)
        &r     = (&rect 'row)
        &c     = (&rect 'col)
        &h     = (&rect 'height)
        &w     = (&rect 'width)
        &color = (&rect 'color)

        repeat r &h
            r += &r
            repeat c &w
                c += &c
                @term:set-cell-bg r c &color
        if ('text in &rect)
            c = &c
            tcolor = (select ('text-color in &rect) (&rect 'text-color) nil)
            foreach char (chars (&rect 'text))
                if (tcolor != nil)
                    @term:set-cell-fg &r c tcolor
                @term:set-cell-char &r c char
                c += 1

in-element =
    fn (&element row col)
        select ((&element 'type) == 'rect)
            and
                row >= (&element 'row)
                row  < ((&element 'row) + (&element 'height))
                col >= (&element 'col)
                col  < ((&element 'col) + (&element 'width))
            0
            
reset-loading-bar =
    fn (&loading-bar thing)
        text = (chars (fmt "LOADING %" thing))
        (&loading-bar 'text) = text
        ((&loading-bar 'view) 'elements) = (list)
        paint-view (&loading-bar 'view)
            
make-loading-bar =
    fn (&view row thing ...)
        text = (chars (fmt "LOADING %" thing))
        o =
            object
                'row      : row
                'text     : text
                'width    : 0
                'view     : &view
        foreach arg ... (o <- arg)
        o

loading-bar-text-push =
    fn (&loading-bar ratio)
        cols = ((&loading-bar 'view) 'cols)
        width = (sint (ratio * cols))
        
        index = 1
        foreach character (&loading-bar 'text)
            color = 0xffffff
            if (index <= width)
                color = 0x000000
            text =
                make-text
                    &loading-bar 'row
                    index
                    character
                    'color : color
            ((text 'paint-fn)) text
            index += 1
        @term:flush
        
loading-bar-update =
    fn (&loading-bar ratio)
        cols = ((&loading-bar 'view) 'cols)
        width = (sint (ratio * cols))
        &view = (&loading-bar 'view)
        
        col = ((&loading-bar 'width) + 1)
        while (col <= width)
            r = (sint (0xbf - (((float col) / cols) * 0x4f)))
            g = (sint (0xbf - (((float col) / cols) * 0xbf)))
            color = ((0xbf + (r << 16)) + (g << 8))
            append
                &view 'elements
                make-rect
                    &loading-bar 'row
                    col
                    1
                    1
                    color
            &element = ((&view 'elements) (newest-element-index &view))
            ((&element 'paint-fn)) &element
            col += 1
        (&loading-bar 'width) = width
        @term:flush
        
        loading-bar-text-push &loading-bar ratio

get-color =
    fn (type r)
        h = 0.0
        s = 0.5
        v = 0.75

        match type
            'loading
                h = 4.79966
                s = r
                v = 0.75
            'divider
                s = 0.0
                v = 0.5
            'kernel
                h = (0.15 * 3.14159)
            'cpp
                h = (0.25 * 3.14159)
            'python
                h = 0.0
                s = 0.25
            'gpu-symbol
                h = 3.14159
            'gpu-inst
                h = (0.6 * 3.14159)

        if (type != 'divider)
            v += (((float ((r % 1000) + 1)) / 1000.0) * 0.15)

        R = 0.0
        G = 0.0
        B = 0.0
        C = (v * s)
        X = (C * (1 - (abs (((h / (3.14159 / 3.0)) % 2.0) - 1))))
        m = (v - C)

        if ((h >= 0.0) and (h < (3.14159 / 3.0)))
            R = C
            G = X
            B = 0
        elif ((h >= (3.14159 / 3.0)) and (h < ((2.0 * 3.14159) / 3.0)))
            R = X
            G = C
            B = 0
        elif ((h >= ((2.0 * 3.14159) / 3.0)) and (h < 3.14159))
            R = 0
            G = C
            B = X
        elif ((h >= (3.14159 / 2.0)) and (h < ((4.0 * 3.14159) / 3.0)))
            R = 0
            G = X
            B = C
        elif ((h >= ((4.0 * 3.14159) / 3.0)) and (h < ((5.0 * 3.14159) / 3.0)))
            R = X
            G = 0
            B = C
        elif ((h >= ((5.0 * 3.14159) / 3.0)) and (h < (2.0 * 3.14159)))
            R = C
            G = 0
            B = X

        (((sint ((R + m) * 255)) & 255) << 16) |
            (((sint ((G + m) * 255)) & 255) << 8) |
                (sint ((B + m) * 255)) & 255
