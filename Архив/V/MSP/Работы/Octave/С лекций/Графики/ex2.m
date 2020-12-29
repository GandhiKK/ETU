phi = -pi /4:0.001: pi /4;
rho = 3 * sqrt (2 * cos (2 * phi));
polar (phi , rho , "b"), hold on
polar (phi , -rho , "b"), grid on
#title (’Lemniscate : \rho = 3 * sqrt (2 * cos (\ phi))’)