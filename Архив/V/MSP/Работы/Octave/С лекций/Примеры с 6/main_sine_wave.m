fig = figure ("numbertitle", "off",
              "name", "My Window",
              "position", [800, 700, 220, 100]);          

fig_bt = uicontrol (fig, "style", "pushbutton",
                         "string", "Show sine wave",
                         "position", [50, 50, 130, 30],
                         "callback", "sine_wave(2, 1, 2, -1);");                         