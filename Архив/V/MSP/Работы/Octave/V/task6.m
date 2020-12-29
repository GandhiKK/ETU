function [x, y1, y2] = task6 ()
  x = linspace(0, 1, 100);
  y1 = lsode('df', 1, x);
  y2 = 0.5*x + exp(-2*x);
  plot(x, y1, 'm;df1;',
       x, y2, 'b;df2;'), grid on
  xlabel('X'); ylabel('Y');
  y1 = y1'; y2 = y2';
endfunction

function y = df(x, t)
  y = - 2*x + t + 0.5;
endfunction
