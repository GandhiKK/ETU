function plot_lines (coef_line, xrange, yrange)
  x = -10:0.01:10;
  f = A(:, 2);
  q = A(:, 1)./-f;
  r = A(:, 3)./-f;  
  plot(x, q*x+r)
  axis(xrange, yrange)
endfunction