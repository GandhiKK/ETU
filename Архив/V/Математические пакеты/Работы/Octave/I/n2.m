n = 5;
a = zeros(n);
x = 1:2:n;
y = 2:2:n;
a(x,x) = 1;
a(y,y) = 1;
disp(a);