function XY = task5 (C1 = [5, 8, 5], C2 = [-5, -4, 11])
  
  f1 = @(x1, y1, r1, x) sqrt(r1.^2-(x-x1).^2)+y1;
  f2 = @(x1, y1, r1, x) -sqrt(r1.^2-(x-x1).^2)+y1;
  
  x1 = C1(1); x2=C2(1);
  y1 = C1(2); y2=C2(2);
  r1 = C1(3); r2=C2(3);
  
  p1 = x1-r1:0.01:x1+r1;
  p2 = x2-r2:0.01:x2+r2;
  
  A = 2*(x2 - x1);
	B = 2*(y2 - y1);
  C = x1^2-x2^2+y1^2-y2^2-r1^2+r2^2;
  x0 = -(A*C)/(A^2+B^2);
  y0 = -(B*C)/(A^2+B^2);  
  D = sqrt(r1^2-(C^2/(A^2+B^2)));
  mult = sqrt(D^2/(A^2+B^2));  
  ax = x0+B*mult;
  ay = y0-A*mult;
  bx = x0-B*mult;
  by = y0+A*mult;
  
  if abs(C) <= r1 * sqrt(A^2+B^2)
    plot(p1, f1(x1,y1,r1,p1), 'r',
         p1, f2(x1,y1,r1,p1), 'r',
         p2, f1(x2,y2,r2,p2), 'b',
         p2, f2(x2,y2,r2,p2), 'b'), grid on

    x1_y1 = fsolve (@(x) g(x, C1, C2), [ax, ay]);
    x2_y2 = fsolve (@(x) g(x, C1, C2), [bx, by] );
    XY = [x1_y1; x2_y2]';  
    hold on
    plot (x1_y1(1), x1_y1(2), "mo", x2_y2(1), x2_y2(2), "mo")  
  endif
  
endfunction

function y = g (x, C1, C2)
  y(1) = (x(1)-C1(1))^2+(x(2)-C1(2))^2-C1(3)^2;
  y(2) = (x(1)-C2(1))^2+(x(2)-C2(2))^2-C2(3)^2;
endfunction