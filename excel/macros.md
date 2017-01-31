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
