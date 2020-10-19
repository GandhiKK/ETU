#{
  X = [1 4;
       5 2;
       3 6;];
  all2dets(X)   
#}

function Y = all2dets (X)
  n = rows(X);
  matA = repmat(X(:, 1), 1, n);
  matB = repmat(X(:, 2), 1, n)';
  matC = matA';
  matD = matB';
  Y = matA .* matB - matC .* matD;
endfunction
