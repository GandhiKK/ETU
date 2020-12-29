##[x, y] = all_lines_intersections (fname)

function [x, y] = all_lines_intersections (fname)
  name = strcat(fname, ".txt");
  f = fopen(name, "at");  
  mat = dlmread(name);
  
  MainMatrix = cat(2, mat(:, 1), mat(:, 2));
  XMatrix = cat(2, -mat(:, 3), mat(:, 2));
  YMatrix = cat(2, mat(:, 1), -mat(:, 3));  
  detMain = all2dets(MainMatrix);
  detX = all2dets(XMatrix);
  detY = all2dets(YMatrix);  
  x = detX ./ detMain;
  y = detY ./ detMain;  
  
  fclose("all");
endfunction

function Y = all2dets (X)
  n = rows(X);
  matA = repmat(X(:, 1), 1, n);
  matB = repmat(X(:, 2), 1, n)';
  matC = matA';
  matD = matB';
  Y = matA .* matB - matC .* matD;
endfunction