function close_prog (hfig)
  btn = questdlg ("Are you sure you want to exit the program?",
                  "Close", "Yes", "No", "No");
                  
  if (strcmp (btn, "Yes"))
    close (hfig)
  endif
endfunction