function gauss(fig, edit_a, edit_b, edit_main, textresult, value)
  try  
    text_22 = uicontrol (fig, "style", "text",
                              "string", num2str(str2num(value)*2-1),
                              "position", [665, 695, 40, 50],
                              "fontsize", 14, "fontname", "SF UI Display",
                              "fontangle", "italic", "fontweight", "bold",
                              "backgroundcolor", "white"); 
  
    accuracy = str2num (value);
    x1 = str2num (get (edit_a).string);
    x2 = str2num (get (edit_b).string);
  
    if(x1 < x2 & abs(x1) < 100 & abs(x2) < 100)
      int = (get (edit_main).string);  
      axis([x1 x2]);  
      x = x1:0.01:x2;
  
      try
        y = eval(int);
      catch lasterror
        set (textresult, "string", "Invalid func");
        return;
      end_try_catch    
  
      subplot(221, "position", [0.035 0.35 0.5 0.5]);
      grid on;
      plot (x, y, "-b");
      area(x, y, "Facecolor", [0.9 0.9 0.9], "Edgecolor", "blue");
      hold on;
  
      subplot(224);
      grid on;
      plot (x, y, "b");
      hold on;
  
      format short;
      result = gs(accuracy, x1, x2, int);  
      set (textresult, "string", sprintf ("%.6f", result));
      return;
    endif
    
    set (textresult, "string", "Invalid span");
    return; 
  
  catch lasterror
    set (textresult, "string", "Invalid smth");
    return;
  end_try_catch    
endfunction


function r = gs(n, a, b, func)
  result = 0.0; f = 0.0;
  Tj = 0.0; Wj = 0.0;
  xx = []; yy = [];
  
  for j=1:n
    hold on;
    h = 1e-15;
    Tj = ((a+b)/2+((b-a)/2*xj_for_next_k(n, xj_0(n, j), h)));
    
    subplot(222); 
    grid on;
    r = xj_for_next_k(n, xj_0(n, j), h);  
    plot (r, 0, "r*")
    hold on;
    
    Wj = wj(n, xj_for_next_k(n, xj_0(n, j), h));
    
    subplot(222); 
    plot (r, Wj, "k*")
    hold on;    
    
    g1 = repmat(r, 1, 2);
    g2 = [0 Wj];
    subplot(222); 
    plot(g1, g2, "k");
    hold on;
  
    x = Tj;
    f = eval(func);
    
    subplot(224); 
    grid on;
    plot (x, f, "r*");
    hold off;
    
    result += Wj*f;
    
    x = r;
    xx = [xx x];    
    y = eval(func);
    yy = [yy y];    
  endfor
  
  r = ((b-a)/2)*result;  
  subplot(222);
  grid on;
  x = -1:0.01:1;
  x2 = x*0;  
  plot(x, x2, "k");
  hold on;
  
  subplot(222);
  grid on;
  plot(x, P(n, x), "b");
  hold off;
    
  subplot(221, "position", [0.035 0.35 0.5 0.5]);
  grid on;
  hold on;
  
  A = polyfit(xx, yy, length(xx)-1);
  xx1 = a:0.01:b;
  yy1 = polyval(A, xx1);
  plot (xx1, yy1, "-r");  
  hold off;  
endfunction


function r = wj(n, x)
  r = 2/((1-x^2)*(P1(n, x)^2));
endfunction


function r = xj_for_next_k(n, x0, e)
  Y = 0.0; Y1 = 0.0; DX = 0.0;
  do
    Y = P(n, x0);    
    if (Y == 0.0)
      break;
    endif
    Y1 = P1(n, x0);
    DX = Y/Y1;
    x0 -= DX;
  until (abs(DX) > e);
  r = x0; 
endfunction


function r = xj_0(n, j)
  r = cos(pi*(4*j-1)/(4*n+2));
endfunction


function r = P(n, x)
  if (n == 0)
    r = 1;
  elseif (n == 1)
    r = x;
  else
    r = (((2*(n-1)+1)/((n-1)+1)).*x.*P(n-1, x)-((n-1)/((n-1)+1)).*P(n-2, x));
  endif
endfunction


function r = P1(n, x)
  r = (n/(1-x*x))*(P(n-1, x)-x*P(n, x));
endfunction