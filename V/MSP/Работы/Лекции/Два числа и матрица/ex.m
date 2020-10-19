f = fopen("matr.txt", "at");

p = dlmread("matr.txt");

mat = p(1:2,1:2);
t = p(3:end, :);

[n, m] = size(mat);
mat = mat';
mat = reshape(mat, 1, n*m);

try
  t = t(mat(1):mat(2), mat(3):mat(4));
  dlmwrite("answet.txt", t);
catch
  warning("Error\n");
  fprintf(f, "\nError\n");
end


fclose("all");