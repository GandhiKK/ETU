#{
A = [1, 1, 1, 1, 1, 1;
     2, 2, 2, 2, 2, 2;
     3, 3, 3, 3, 3, 3;
     4, 4, 4, 4, 4, 4;
     5, 5, 5, 5, 5, 5;
     6, 6, 6, 6, 6, 6];     
task2(A)
#}

function A1 = task2 (A)
  n = rows(A); 
  A1 = A';
  reshape(A1, 1, n*n); 
  A2 = A1(1:end/2);
  A3 = A1(end/2+1:end);
  A1 = [A3, A2];
  A1 = reshape(A1, n, n); 
  A1 = A1';
endfunction