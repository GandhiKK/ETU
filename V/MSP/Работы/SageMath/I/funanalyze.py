def find_and_show_roots(fun, size, col, thick, g, name, main, a, b):
    # find roots
    root = solve(fun, x, solution_dict=True)
    print(name, root)
    roots = []
    for i in root:
        roots.append(i.get(x))

    # show roots
    for i in roots:
        if (n(i) > a and n(i) < b and i in RR):
            g += circle((i, main(x=i)), size, color=col, thickness=thick)
    return roots, g


@interact
def analyze(f=input_box(default='(x + 1)/(x^2 + 1)', label='Enter your function'), a=(-10, 0), b=(0, 10)):
    ## a ##
    g = Graphics()
    g += plot(f, (x, a, b), color='red', thickness=1.7, legend_label='$fun$')

    ## b + c ##    
    r, g = find_and_show_roots(f, 0.05, 'black', 1, g, '(b) The roots of a function:', f, a, b)

    ## d ##
    df = diff(f, var('x'))
    print('(d) The derivative of a function:')
    show(df)

    ## e ##
    g += plot(df, (a, b), color='blue', thickness=0.5, legend_label='$df$')

    ## f + g ##
    r, g = find_and_show_roots(df, 0.04, 'magenta', 0.6, g, '(f) The roots of a derivative:', f, a, b)

    ## h ##    
    t = []
    print('(h)')
    for i in r:
        t = [n(df(i - 0.1)), n(df(i + 0.1))]
        if (t[0] > t[1]):
            print('   ', i, ': maximum')
            if (n(i) > a and n(i) < b and i in RR):
                g += circle((i, f(i)), 0.04, color='#00ff00', thickness=0.6)
        elif (t[0] < t[1]):
            print('   ', i, ': minimum')
            if (n(i) > a and n(i) < b and i in RR):
                g += circle((i, f(i)), 0.04, color='#003399', thickness=0.6)
        else:
            print('   ', i, ': none')

    ## i ##
    df2 = diff(f, var('x'), 2)
    print('(i) The second derivative of a function:')
    show(df2)

    ## j ##
    g += plot(df2, (a, b), color='green', thickness=0.4, legend_label='$df2$')

    ## k + l ##    
    r, g = find_and_show_roots(df2, 0.03, '#660000', 0.5, g, '(k) The roots of a second derivative:', f, a, b)

    ## m ##    
    # fucntion: find_and_show_roots()

    ## n ##    
    k = limit(f / x, x=oo)
    bk = limit(f - k * x, x=oo)
    y = k * var('x') + bk

    try:
        if (y(0) in RR):
            print('(n) Slant asymptotes: y =', y)
            g += plot(y, (x, a, b), linestyle='--')
        else:
            print('(n) y : Complex number')
    except Exception:
        if (y in RR):
            print('(n) Slant asymptotes: y =', y)
            g += plot(y, (x, a, b), linestyle='--')
        else:
            print('(n) y : Complex number')

            ## o ##
    ans = solve(1 / f == 0, x)
    y = ans[0].rhs()

    if (y in RR):
        print('(o) Vertical asymptotes: x =', y)
        g += plot(y, (x, a, b), linestyle='--')
    else:
        print('(o) Vertical asymptotes: x = Complex number')

        ## show ##
    g.show(figsize=10)