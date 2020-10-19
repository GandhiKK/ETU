#{
  x = [1; 2; 3]; 
  task8(x)
#}

function A = task8 (x)
  n = rows(x);
  y = repmat(x, 1, n);
  z = y';
  A = y-z;
endfunction
