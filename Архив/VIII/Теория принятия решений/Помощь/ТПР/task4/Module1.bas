Attribute VB_Name = "Module1"
Sub Makros1()
Dim del, start As Integer
Dim tav As Integer
Dim Vmaxavr, sum, price, finish As Single
    
del = 1 '5 * 60 / 4     ���
    
tav = Cells(1, "M") - 1
sum = 0
start = 2 '905
finish = start + tav  '24005
    
Fin = 550 'Cells(1, "A") - 1
    
For row = start To finish Step del
    Vmax = Vmax + Cells(row, "E")
   
    Next row
      
Cells(finish, "L") = Vmax
        
start = finish + del
finish = Fin 'ish + n * del
tav = tav + 1
                                                
For row = start To finish Step del
    Vmax = Vmax + Cells(row, "E") - Cells(row - tav, "E")

    Vmaxavr = Vmax / tav
    Cells(row, "K") = Vmaxavr
                                   
    Next row  '45      'Next Row
    
End Sub

Sub sd()

End Sub



