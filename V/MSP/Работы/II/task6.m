#{
  M = [50, 5;
       160, 1;
       165, 1;
       160, 2;
       165, 2;
       168, 2;
       150, 3;
       160, 3;
       170, 4;
       180, 4;
       210, 4;
       100, 5;];    
  [a, b, c] = task6(M)
#}

function [sh, sht, shv] = task6 (M)
  
  function ret = avg (v)
    if length(v) == 0
      ret = NaN;
    else
      ret = sum(v)/length(v);
    endif
  endfunction
   
  n = rows(M);
  sh = zeros(5, 1);
  sht = zeros(5, 1);
  shv = zeros(5, 1);
  H = M(:,2);
  G = M(:,1); 
  
  for i = 1:5
    k = G(H == i);
    sh(i) = sum(k);    
    sz = rows(k);
    t = reshape(k, 1, sz);
    sht(i) = avg(t);
    t = t(t >= 100 & t <= 200);
    shv(i) = avg(t);
  endfor
  
endfunction






