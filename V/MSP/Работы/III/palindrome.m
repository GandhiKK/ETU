#{
## str = '"Not New York", - Roy went on';
## palindrome(str);
#}

function palindrome (str)
  str = lower(str);
  strA = str(isletter(str));
  strB = fliplr(strA);
  x = merge(strcmp(strA, strB) ...
            , "This string is a palindrome!" ...
            , "This string is not a palindrome!");
  disp(x);
endfunction
