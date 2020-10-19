function task8 (Alpha=0.52, Beta=0.25, Gamma=0.6, Delta=0.15, k=2)
  
  ## стационарная точка системы, вокруг которой происходят колебания, 
  ## определяется следующим образом:
  xs = Gamma / Delta;
  ys = Alpha / Beta;
  
  x = 0:0.01:30;
  for K = 0:5
    y1 = lsode(@(xp_yp) df(xp_yp, Alpha, Beta, Gamma, Delta)...
              ,[xs, ys+K*k], x);
    plot(y1(:, 1), y1(:, 2), 'o')
    grid on
    hold on
  endfor
  
  title('Модель Лотки — Вольтерры');
	xlabel('Количество жертв');
	ylabel('Количество хищников');
  
endfunction

function y = df(xp_yp, Alpha, Beta, Gamma, Delta)
  y = [(Alpha - Beta * xp_yp(2)) * xp_yp(1), 
       (Delta * xp_yp(1) - Gamma) * xp_yp(2)]; #[x', y']
endfunction