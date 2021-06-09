function [x, y] = task2 (n = 3)
  x = -10:0.1:10;    
  t = diag(1:n);
  y = sum(inv(t) * sin(t * repmat(x, n, 1)));   
  plot(x, y, ";task2;b-o"), grid on
endfunction
