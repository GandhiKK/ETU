#{
  a = [1, 2, -2, 4];
  x = 2;  
  task7(a, x)
#}

function y = task7 (a, x)  
  c = 0:length(a)-1;   # [0, 1, 2, 3]
  b = ones(1, length(a))*x;   # [2, 2, 2, 2]
  d = b .^ c   # [1 2 4 8]
  y = sum(a.*d);   # [1*1+2*2+(-2)*4+4*8] 
endfunction
