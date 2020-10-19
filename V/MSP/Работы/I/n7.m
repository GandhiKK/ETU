n = 4;
a = 1;
b = 2;
v = zeros(n);
v1 = diag(a*ones(1, n));
v2 = diag(b*ones(1, n-1), 1);
v3 = diag(b*ones(1, n-1), -1);
v=v1+v2+v3;
disp(v);