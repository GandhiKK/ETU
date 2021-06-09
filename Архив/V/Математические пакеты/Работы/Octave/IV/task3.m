function task3 (A)  
  grid on;
  hold on;
  xlabel("X"); ylabel("Y");
  
  x = A(1, :);
  y = A(2, :);
  
  subplot(221)
  plot (x, y, "bo;A;")
  hold on;
  plot (mean(x), mean(y), "r*;rc;")
  text(3, 3, "центр масс")
  title ("A")
  
  subplot(222)
  plot (x-mean(x), y-mean(y), "g^;B;")
  title ("B")
  
  subplot(223)
  p = deg2rad(15);
  plot (x*cos(p) - y*sin(p), x*sin(p) + y*cos(p), "mh;C;")
  title ("C")
  
  subplot(224)
  p = deg2rad(25);
  plot ((x*cos(p) - y*sin(p))+mean(x), (x*sin(p) + y*cos(p))+mean(y), "yp;D;")
  title ("D") 
 
  saveas(gcf, "task3.png");   
endfunction
