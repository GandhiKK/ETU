function [xs, xz, xe, dx] = task4 (a = 1000000)
  xs = fsolve(@(x) f(x, a), 10);
  xz = fzero(@(x) f(x, a), [-100, 100]);
  xe = log((a + sqrt(a^2 + 4)) / 2);
  dx = xs-xe;
endfunction

function y = f(x, a)
  y = exp(x) - exp(-x) - a;
endfunction
