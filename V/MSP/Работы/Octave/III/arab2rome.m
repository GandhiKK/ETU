#{
## a = [1, 6, 14, 1, 2, 3, 5, 8, 13, 14, 15];
## r = arab2rome(a)
#}

function r = arab2rome (a)
  x = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "$"};
  a(a > 10) = 11;
  r = x(a);
endfunction
