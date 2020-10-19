#{
  A = [1, 2, 3;
       7, 5, 4];    
  task4(A)
#}

function A1 = task4 (A)
  A1 = A;
  mat = (mod(A1, 2) == 1);
  A1(mat) *= 2;
endfunction
