Attribute VB_Name = "Module5"
Sub Macros5()
sum = Cells(1, "X")
stocks = Cells(1, "Y")

lowerBound = 30
upperBound = 70
oldPos = 50

For row = 9 To 550 Step 1
    RSI = Cells(row, "P")
    price = Cells(row, "E")

    If (oldPos < lowerBound And RSI > lowerBound) Then
        modificationSum = sum * (RSI - oldPos) / 100
        Count = modificationSum / price
        stocks = stocks + Count
        sum = sum - modificationSum
    End If

    If (oldPos > upperBound And RSI < upperBound) Then
        modificationStocks = stocks * (oldPos - RSI) / 100
        sum = sum + modificationStocks * price
        stocks = stocks - modificationStocks
    End If

    Cells(row, "X") = sum
    Cells(row, "Y") = stocks
    Cells(row, "Z") = sum + price * stocks
    oldPos = RSI
Next row

Cells(1, "Z") = Cells(550, "Z")
End Sub

