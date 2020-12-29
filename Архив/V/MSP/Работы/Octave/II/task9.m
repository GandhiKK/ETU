#{
  A = [1, 1, 1;
       1, 2, 3;
       3, 2, 1;
       2, 4, 3;]; 
  task9(A)
#}

function B = task9 (A)
  f = A(:, 2);
  q = A(:, 1)./-f;
  r = A(:, 3)./-f;
  B = [q, r];
endfunction

