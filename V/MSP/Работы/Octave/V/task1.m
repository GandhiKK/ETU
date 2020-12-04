function x = task1 (n = 3)
  p = ones(1, n+1);
  y = roots(p);
  x = reshape(y, 1, rows(y));
  a = real(x); b = imag(x);
  plot(a, b, ';roots;ro')
  grid on;
  xlabel('X'); ylabel('Y');
endfunction
