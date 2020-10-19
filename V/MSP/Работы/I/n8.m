n = 5;
x = ones(1,n);
x(2:2:end) = 2;
v = zeros(n);

for i=-(n-1):(n-1)
  v1 = diag(x(1:end-abs(i)), i);
  v += v1;
endfor

disp(v);
