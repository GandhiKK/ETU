clear all
hfig = figure ("numbertitle", "off",
               "name", "QU_EQUATION",
               "position", [300, 300, 660, 290]);

lab_a = uicontrol (hfig, "style", "text",
                         "string", "A = ",
                         "position", [50, 250, 100, 20]);

lab_b = uicontrol (hfig, "style", "text",
                         "string", "B = ",
                         "position", [150, 250, 100, 20]);

lab_c = uicontrol (hfig, "style", "text",
                         "string", "C = ",
                         "position", [250, 250, 100, 20]);

edit_a = uicontrol (hfig, "style", "edit",
                          "string", "1",
                          "position", [50, 230, 100, 20]);

edit_b = uicontrol (hfig, "style", "edit",
                          "string", "2",
                          "position", [150, 230, 100, 20]);

edit_c = uicontrol (hfig, "style", "edit",
                          "string", "1",
                          "position", [250, 230, 100, 20]);

textresult = uicontrol (hfig, "style", "text",
                              "string", "",
                              "position", [5, 80, 650, 20]);

radio_biqu = uicontrol ("style", "radiobutton",
                        "string", "Is Biquadratic equation?",
                        "value", 1, 
                        "position", [100, 100, 300, 20]);
                        
BtSolve = uicontrol ("style", "pushbutton",
                     "string", "Solve",
                     "callback",
                     "qu_solve(edit_a, edit_b, edit_c, radio_biqu, textresult)",
                     "position", [50, 50, 120, 20]);
BtClose = uicontrol ("style", "pushbutton",
                     "string", "Close",
                     "callback", "close_prog (hfig)",
                     "position", [300, 50, 120, 20]);