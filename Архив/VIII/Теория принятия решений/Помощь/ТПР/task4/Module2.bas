Attribute VB_Name = "Module2"
Sub Macros2()
Dim oldSum, newSum, stocks, efficiency As Single
oldSum = 129
newSum = oldSum
stocks = 0

For row = 9 To 550 Step 1
    price = Cells(row, "E")
    indicator = Cells(row, "K")
    If (indicator > price) Then
        Count = newSum / price
        newSum = 0
        stocks = stocks + Count
    Else
        newSum = newSum + stocks * price
        stocks = 0
    End If
    Cells(row, "M") = newSum
    Cells(row, "L") = stocks
Next row

efficiency = (newSum - oldSum) / oldSum

Cells(1, "L") = oldSum
Cells(2, "L") = newSum
Cells(3, "L") = efficiency
End Sub

