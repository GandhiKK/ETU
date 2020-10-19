function [x, y] = task3 ()
  x = 0:0.01:1;
  t = fsolve(@f, [0, 1]);  
  plot (x, 1 - cos(x), "k",
        x, asin(1 - x), "m"), grid on  
  hold on
  x = t(1); y = t(2);
  plot (x , y, "r*")
endfunction

function y = f(x)
    y = [x(1) + sin(x(2)) - 1,
         x(2) + cos(x(1)) - 1];
endfunction
