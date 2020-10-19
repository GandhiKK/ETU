function task4 (n)
  hold on;
  i = 0:360;
  r = 1:n;
  plot(r .* cos(i/180*pi)', r .* sin(i/180*pi)')
endfunction
