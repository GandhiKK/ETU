function sine_wave (a, b, c, d)
  if (b * c != 0)
    f = figure ("numbertitle", "off",
                "name", "Sine Wave");
    x = -2*pi:0.01:2*pi;
    y = a + b * sin (c * x + d);
    plot (x, y, "r"), grid on
    xlim ([-2*pi, 2*pi])
  else
    beep
    errordlg ("Error !\n'b' or 'c' is not equale zero!");
  endif
endfunction