#{
x = [1, 2, 3, 6, 5, 9, 18, 7, 3, 12, 15];    
task3(x)
#}

function x1 = task3 (x)
  x1 = [];
  x1 = x(rem(x, 3) == 0);
endfunction
