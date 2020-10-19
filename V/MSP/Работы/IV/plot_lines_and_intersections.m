function plot_lines_and_intersections (coef_line)
  function [x, y] = all_lines_intersections (mat)  
    MainMatrix = cat(2, mat(:, 1), mat(:, 2));
    XMatrix = cat(2, -mat(:, 3), mat(:, 2));
    YMatrix = cat(2, mat(:, 1), -mat(:, 3));  
    detMain = all2dets(MainMatrix);
    detX = all2dets(XMatrix);
    detY = all2dets(YMatrix);  
    x = detX ./ detMain;
    y = detY ./ detMain;  
    x(isnan(x)) = 0;
    y(isnan(y)) = 0;
  endfunction

  function Y = all2dets (X)
    n = rows(X);
    matA = repmat(X(:, 1), 1, n);
    matB = repmat(X(:, 2), 1, n)';
    matC = matA';
    matD = matB';
    Y = matA .* matB - matC .* matD;
  endfunction

  hold on;
  grid on;
  x = -10:0.01:10;
  A = [1 2 3; 3 2 1; 5 2 4];
  [p, k] = all_lines_intersections (A)
  plot(p, k, ";per;o")
  f = A(:, 2);
  q = A(:, 1)./-f;
  r = A(:, 3)./-f;  
  plot(x, q*x+r)
  
  #axis(xrange, yrange);  
endfunction