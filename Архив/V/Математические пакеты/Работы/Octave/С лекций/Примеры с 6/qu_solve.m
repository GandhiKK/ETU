function qu_solve (edit_a, edit_b, edit_c, radio_biqu, textresult)
  a = str2num (get (edit_a).string);
  b = str2num (get (edit_b).string);
  c = str2num (get (edit_c).string);
  
  D = b^2 - 4*a*c;
  
  if (get (radio_biqu).value == 0)  # if-else 1
    if (D < 0)  # if-else 5
      beep
      set (textresult, "string", "No solution to the quadratic equation!")
    else  # if-else 5
      x1 = (-b + sqrt (D)) / (2*a);
      x2 = (-b - sqrt (D)) / (2*a);
      set (textresult, "string",
           sprintf ("2 roots of the quadratic equation \t x1=%1.2f\tx2=%1.2f",
                    x1, x2));
    endif  # if-else 5
  else  # if-else 1
    if (D < 0)  # if-else 2
      beep
      set (textresult, "string", "No solution to the quadratic equation!");
    else  # if-else 2
      y1 = (-b + sqrt (D)) / (2*a);
      y2 = (-b - sqrt (D)) / (2*a);
      
      if (y1 < 0 && y2 < 0)  # if-else 3
        beep
        set(textresult, "string", "No solution to the biquadratic equation!");
      elseif (y1 >= 0 && y2 >= 0)  # if-else 3
        x1 = sqrt (y1);
        x2 = -x1;
        x3 = sqrt (y2);
        x4 = -x3;
        set (textresult, "string",
             sprintf ("4 roots of the biquadratic equation\
\t x1=%1.2f\tx2=%1.2f\tx3=%1.2f\tx4=%1.2f", x1, x2, x3, x4))
      else  # if-else 3
        if (y1 >= 0)  # if-else 4
          x1 = sqrt (y1);
          x2 = -x1;
        else  # if-else 4
          x1 = sqrt (y2);
          x2 = -x1;
        endif # end if-else 4
        set (textresult, "string",
             sprintf ("2 roots of the biquadratic equation\
\t x1=%1.2f\tx2=%1.2f", x1, x2));
                    
      endif  # end if-else 3
    endif  # end if-else 2
  endif  # end if-else 1
endfunction