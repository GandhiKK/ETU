function [x, y] = task1 ()
  x = -2*pi:0.1:2*pi;
  y = sin(x) + cos(3*x);
  plot(x, y, ";sinx + cos3x;b"), grid on
endfunction
