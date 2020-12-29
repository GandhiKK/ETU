##jabberwocky("the", "abcdef", "and");

function jabberwocky (varargin)
  f = fopen("Jabberwocky.txt", "r");
  ff = fopen("jabberwocky-analysis.txt", "w");   
  A = textscan(f, '%s', 'HeaderLines', 4, 'Delimiter', "\n");
  x = [A{[1]}];
  n = size(x);
  fwrite(ff, "Word / Num. of entries / No. str. with first occurrence\n\n");
  
  for i = 1:nargin
    y = [varargin{i}];
    text = [x{[1:n]}];
    t = int2str(length(findstr(text, y))); # количество вхождений y в текст([x{[1:n]}])   
    if t == "0" 
      fwrite(ff, strcat(y, ":\t0\tNaN\n"));
      continue
    endif
    az = strcat(x, "$");
    textMod = [az{[1:n]}];
    f = findstr(textMod, y);    
    u = int2str(length(findstr(textMod(1:f(1)), "$"))+1); # количество $ в течение поиска первого символа аргумента    
    fwrite(ff, strcat(y, ":\t", t, "\t", u, "\n"));
  endfor 
  
  fclose("all");
endfunction
