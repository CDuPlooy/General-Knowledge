# Macros
Generally with excel macros you want to just move offsets and change active cells.


Change the active cell
```vba
ActiveSheet.Cells(x,y).Select
```

Get the value of the active cell
```vba
ActiveSheet.Cells(x,y).Value
```

Work with the offsets
```vba
ActiveCell.Offset(x,y).Value
ActiveCell.Offset(x,y).Select
```

A tiny example of string manipulation
```vba
' This function returns the date as a string ; Error checking is omitted.
Function seperateDateAndTime(Buffer As String) As String
    pos = InStr(Buffer, " ")
    seperateDateAndTime = Left(Buffer, pos - 1)
End Function
```

A useful function for turning sheets into tables.
```vba
' This function finds the numerical value of a field in column x and row y
' Returns -1 on error ; The offset of the field relative to [row,column]
Function getFieldNum(workBookName As String, workSheetName As String, fieldName As String, row As Long, column As Long) As Integer
    getFieldNum = -1 ' Set the error condition
    
    Workbooks(workBookName).Activate ' Should raise an error if the workbook isn't found
    Worksheets(workSheetName).Select
    
    i = 0
    ActiveSheet.Cells(row, column).Select
    While (ActiveCell.Offset(0, i) <> "")
        If fieldName = ActiveCell.Offset(0, i).Value Then
            getFieldNum = i + 1
        End If
        i = i + 1
    Wend
End Function
```


Allows indexing of fields as tables
```vba

' This function returns the value of a field in column n ( Passing 0 will result in the field name being returned )
Function valueOfField(workBookName As String, workSheetName As String, fieldName As String, row As Long, column As Long, n As Long)
    field = getFieldNum(workBookName, workSheetName, fieldName, row, column)
    If field = -1 Then
    valueOfField = "(nill)"     ' This might conflict with some OOOOLD C applications.
    Else
    valueOfField = ActiveCell.Offset(n, field - 1).Value
    End If
End Function
```

ALl the above is kind of slow , range selections are very fast.

```vba
WorksheetFunction.Sum(Worksheets("OEE").Range("J:J"))
```
You can use wildcards in an Autofilter Criteria
```Wildcards
* and ?
```
