fig = figure ("numbertitle", "off", "name", "Gauss",
              "position", [150 150 1650 800]);                  
              
main = uicontrol (fig, "style", "pushbutton",
                       "string", "Solve",
                       "position", [280, 35, 150, 70],
                       "fontsize", 24, "fontname", "SF UI Display",
                       "backgroundcolor", [0.9 0.9 0.9], 
                       "foregroundcolor", "black", 
                       "callback", "gauss(fig, edit_a, edit_b, edit_main, textresult, get (popup, 'string'){get (popup, 'value')})");                 

main_button = uicontrol (fig, "style", "pushbutton",
                       "string", "Save As",
                       "position", [530, 35, 150, 70],
                       "fontsize", 24, "fontname", "SF UI Display",
                       "backgroundcolor", [0.9 0.9 0.9], 
                       "foregroundcolor", "black", 
                       "callback", "save(fig)");                        
                       
text_0 = uicontrol (fig, "style", "text",
                         "string", "Approximating",
                         "position", [200, 700, 150, 50],
                         "fontsize", 12, "fontname", "SF UI Display",
                         "fontangle", "italic", "fontweight", "bold",
                         "backgroundcolor", "white", "foregroundcolor", "red");
        
text_1 = uicontrol (fig, "style", "text",
                         "string", " f(x) ",
                         "position", [355, 700, 40, 50],
                         "fontsize", 12, "fontname", "SF UI Display",
                         "fontangle", "italic", "fontweight", "bold",
                         "backgroundcolor", "white", "foregroundcolor", "blue");  
                 
text_2 = uicontrol (fig, "style", "text",
                         "string", "with polynomials of order ",
                         "position", [400, 700, 280, 50],
                         "fontsize", 12, "fontname", "SF UI Display",
                         "fontangle", "italic", "fontweight", "bold",
                         "backgroundcolor", "white");
               
text_3 = uicontrol (fig, "style", "text",
                         "string", "Legendre polynomials,",
                         "position", [1000, 750, 220, 50],
                         "fontsize", 12, "fontname", "SF UI Display",
                         "fontangle", "italic", "fontweight", "bold",
                         "backgroundcolor", "white", "foregroundcolor", "blue");
        
text_4 = uicontrol (fig, "style", "text",
                         "string", " P[n](x[i]) = 0 ",
                         "position", [1225, 750, 130, 50],
                         "fontsize", 12, "fontname", "SF UI Display",
                         "fontangle", "italic", "fontweight", "bold",
                         "backgroundcolor", "white", "foregroundcolor", "red");  
                 
text_5 = uicontrol (fig, "style", "text",
                         "string", "& w(x[i])",
                         "position", [1360, 750, 100, 50],
                         "fontsize", 12, "fontname", "SF UI Display",
                         "fontangle", "italic", "fontweight", "bold",
                         "backgroundcolor", "white");    
             
text_6 = uicontrol (fig, "style", "text",
                         "string", "f(t[i])",
                         "position", [1200, 370, 70, 50],
                         "fontsize", 14, "fontname", "SF UI Display",
                         "fontangle", "italic", "fontweight", "bold",
                         "backgroundcolor", "white");              
                                              
text_a = uicontrol (fig, "style", "text",
                         "string", "Integral:",
                         "position", [65, 130, 130, 50],
                         "fontsize", 16, "fontname", "SF UI Display",
                         "backgroundcolor", "white"); 
                         
text_b = uicontrol (fig, "style", "text",
                         "string", "/",
                         "position", [180, 130, 60, 50],
                         "fontsize", 18, "fontname", "SF UI Display",
                         "backgroundcolor", "white"); 
                                                  
text_c = uicontrol (fig, "style", "text",
                         "string", "Amount of nodes:",
                         "position", [60, 200, 250, 50],
                         "fontsize", 16, "fontname", "SF UI Display",
                         "backgroundcolor", "white");    
      
popup = uicontrol ("style", "popupmenu",
                   "fontsize", 14, "fontname", "SF UI Display",
                   "string", {"2", "3", "4", "5", "6", "7", "8", "9", "10"},
                   "position", [300, 210, 50, 30]);      
                         
edit_a = uicontrol (fig, "style", "edit",
                         "string", "-1",
                         "fontsize", 12, "fontname", "SF UI Display",
                         "backgroundcolor", "white",
                         "position", [190, 100, 45, 30]); 
                         
edit_b = uicontrol (fig, "style", "edit",
                         "string", "1",
                         "fontsize", 12, "fontname", "SF UI Display",
                         "backgroundcolor", "white",
                         "position", [190, 170, 45, 30]); 
                         
edit_main = uicontrol (fig, "style", "edit",
                            "string", "exp(-x).*sin(4.*x).^2",
                            "fontsize", 14, "fontname", "SF UI Display",
                            "backgroundcolor", "white",
                            "position", [240, 140, 220, 30]);

textresult0 = uicontrol (fig, "style", "text",
                              "string", "=",
                              "fontsize", 14, "fontname", "SF UI Display",
                              "backgroundcolor", "white",
                              "position", [465, 143, 20, 30]); 
                            
textresult = uicontrol (fig, "style", "text",
                             "string", "",
                             "fontsize", 14, "fontname", "SF UI Display",
                             "backgroundcolor", [0.9 0.9 0.9],
                             "position", [488, 140, 120, 30]);                                 
                          
function save(fig)
  name = inputdlg("Enter file name", "Saving", [1, 20]);
  saveas(fig, strcat(name{:}, ".png"));
endfunction











    