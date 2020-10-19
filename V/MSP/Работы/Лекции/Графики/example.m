x = -1:0.01:1;
y = sin (x); z = cos (x);
u = asin (x); w = acos (x);

subplot (221)
plot (x, y, "b"), grid on
title (" Sine ")

subplot (222)
plot (x, z, "r"), grid on
title (" Cosine ")

subplot (223)
plot (x, u, "k"), grid on
title (" Arcsine ")

subplot (224)
plot (x, w, "m"), grid on
title (" Arccosine ")