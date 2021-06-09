# Практика 3, вариант 8

## Задача

Написать функцию, выделяющую часть матрицы фиксированного размера с центром в данном элементе (дополненное значением fill если необходимо)

## Решение

Функция `solve` принимает исходную матрицу; конечную матрицу заданного размера, заполненную значением fill; центр; размерность конечной матрицы.

Высчитываются значения начала и конца слайсов для исходной матрицы, то есть какая часть копируется из матрицы.

```py
offsetStartx = cen[0]-nm[0]//2
offsetStarty = cen[1]-nm[1]//2
offsetEndx = cen[0]+nm[0]//2
offsetEndy = cen[1]+nm[1]//2
```

Далее значения меняются в завсисмости от того, вышли они за границу или нет. Также меняется значение конца слайса для конечной матрицы с четной размерностью.

```py
matSliceStartX = offsetStartx if offsetStartx > 0 else 0
matSliceStartY = offsetStarty if offsetStarty > 0 else 0
matSliceEndX = offsetEndx+1 if offsetEndx+1 < mat.shape[0] 
                            else mat.shape[0]
matSliceEndY = offsetEndy+1 if offsetEndy+1 < mat.shape[1] 
                            else mat.shape[1]

if (nm[0] % 2) == 0:
    matSliceEndX = offsetEndx if offsetEndx < mat.shape[0]
                              else mat.shape[0]
if (nm[1] % 2) == 0:
    matSliceEndY = offsetEndy if offsetEndy < mat.shape[1] 
                              else mat.shape[1]
```

Также высчитывается слайс для конечной матрицы. И далее часть исходной матрицы копируется в новую.

```py
slice_for_mat = tuple([slice(matSliceStartX, matSliceEndX), 
                       slice(matSliceStartY, matSliceEndY)])
slice_for_final = tuple([slice(matSliceStartX-offsetStartx, matSliceEndX-offsetStartx), 
                         slice(matSliceStartY-offsetStarty, matSliceEndY-offsetStarty)])
final[slice_for_final] = mat[slice_for_mat]
```

Матрица считывается из файла. Результаты записываются в файл.

## Пример

Дано:

```py
mat:
    [[ 1  2  3  2  1]
     [ 4  5  6  5  4]
     [ 7  8  9  8  7]
     [10 11 12 11 10]
     [13 14 15 14 13]]

fill: 0
center: 4 1
mat shape: 3 3
```

Вывод:

```py
    [[10 11 12]
     [13 14 15]
     [ 0  0  0]]
```
