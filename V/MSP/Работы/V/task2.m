function x = task2 (p, a)  
  x = fzero(@(x) f(x, p, a), 0);
endfunction

function y = f(x, p, a)
    p = fliplr(p); y = 0;
    for i = length(p):-1:1
      y += p(i)*(x^(i-1))*exp(x);
    endfor  
    y -= a; 
endfunction