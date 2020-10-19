function task7 (y0 = 1, y1 = 0)
  x = 0:0.01:10;
  y = lsode(@df, [y0, y1], x); 
  plot (x, y(:, 1) , "r;y = y (x);",
        x, y(:, 2) , "b;g = y’(x);"), grid on
endfunction

function v = df(f, x)
    y = f(1);
    g = f(2);
    v = [g, -y*(cos(x)+1)];
  endfunction  