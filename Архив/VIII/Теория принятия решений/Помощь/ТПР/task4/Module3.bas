Attribute VB_Name = "Module3"
Sub Macros3()
For Block = 2 To 550 - 7 Step 1
    incr = 0
    decr = 0
    For row = 1 To 7 Step 1
        oldPrice = Cells(Block + row - 1, "E")
        newPrice = Cells(Block + row, "E")
        deltaPrice = newPrice - oldPrice
        
        If (deltaPrice > 0) Then
            incr = incr + deltaPrice
        Else
            decr = decr - deltaPrice
        End If
    Next row
    If (decr <> 0) Then
        RS = incr / decr
        RSI = 100 - 100 / (1 + RS)

        Cells(Block + 7, "O") = RS
        Cells(Block + 7, "P") = RSI
    End If
    Next Block
End Sub

