data = [60,70,60,60,70,70,80,80,80,80,80,80,80,90,90,90,90,90,100,100,100,100,100,100,100,100,110,110,110,110];
a = sort(data);
n = length(a);

#x = unique(a);
x = [0 1 2 3];
j = 0;
#for i = x, j++;
  #m(j) = sum(a==i);
#endfor
n = 50;
m = [32 12 5 1];
p = m./n;

xv = sum(x .* p);
xv2 = sum(x.^2 .* p);
dv = xv2 - xv^2;
sko = sqrt(dv);
mo = mode(a);
me = median(a);
v = sko / xv * 100;

M = [xv]; N = [0];
for i = 2:4
  M(i) = sum(x.^i .* p);
  N(i) = sum((x - xv).^i .* p);
endfor

as = N(3)/sko^3;
ex = N(4)/sko^4 - 3;

answer = {x, m, p, xv, dv, sko, mo, me, v, M, N, as, ex};
answerNames = {"x:", "m:", "p:", "xv:", "dv:", "sko:", "mo:", "me:", "v:", "M:", "N:", "as:", "ex:"};
#plot(x, m)

for i = 1:13 disp(answerNames{i}); disp(answer{i}); endfor