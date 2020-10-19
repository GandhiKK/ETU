function task5 (coef_line, xrange, yrange)
  x1 = xrange(1);
  x2 = xrange(2);
  y1 = yrange(1);
  y2 = yrange(2);
  
  a = coef_line(1);
  b = coef_line(2);
  c = coef_line(3);  
  
  yr1 = (-a*x1-c)/b;
  yr2 = (-a*x2-c)/b;
  xr1 = (-b*y1-c)/a;
  xr2 = (-b*y2-c)/a;
  
  [xr2 yr1]
  [xr1 yr2]
  
endfunction
