##sieve(a)

function a = sieve (n)
  a = 2:n;
  for i = 2:n
    a = filter_multiples(a, i);
  endfor
endfunction  

function a1 = filter_multiples (a, k)
  i = 1; a1 = a;
  while i <= length(a1)
    if a1(i) > k && rem(a1(i), k) == 0 
      a1(i) = [];
    else
      i++;
    endif
  endwhile
endfunction
