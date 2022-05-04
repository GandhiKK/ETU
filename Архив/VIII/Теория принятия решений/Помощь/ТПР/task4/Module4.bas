Attribute VB_Name = "Module4"
Sub Macros4()
sum = Cells(1, "T")
stocks = Cells(1, "U")
lowerBound = 30
upperBound = 70
oldPos = 50

For row = 9 To 550 Step 1
    RSI = Cells(row, "P")
    price = Cells(row, "E")
    
    If (oldPos < lowerBound And RSI > lowerBound) Then
        Count = sum / price
        stocks = stocks + Count
        sum = 0
    End If
    
    If (oldPos > upperBound And RSI < upperBound) Then
        sum = sum + stocks * price
        stocks = 0
    End If
    
    Cells(row, "T") = sum
    Cells(row, "U") = stocks
    Cells(row, "V") = sum + price * stocks
    oldPos = RSI
Next row

Cells(1, "V") = Cells(550, "V")

End Sub
