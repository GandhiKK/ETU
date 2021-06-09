import numpy as np

def solve(mat, final, cen, nm):
    offsetStartx = cen[0]-nm[0]//2
    offsetStarty = cen[1]-nm[1]//2
    offsetEndx = cen[0]+nm[0]//2
    offsetEndy = cen[1]+nm[1]//2

    matSliceStartX = offsetStartx if offsetStartx > 0 else 0
    matSliceStartY = offsetStarty if offsetStarty > 0 else 0
    matSliceEndX = offsetEndx+1 if offsetEndx+1 < mat.shape[0] else mat.shape[0]
    matSliceEndY = offsetEndy+1 if offsetEndy+1 < mat.shape[1] else mat.shape[1]
    if (nm[0] % 2) == 0:
        matSliceEndX = offsetEndx if offsetEndx < mat.shape[0] else mat.shape[0]
    if (nm[1] % 2) == 0:
        matSliceEndY = offsetEndy if offsetEndy < mat.shape[1] else mat.shape[1]

    slice_for_mat = tuple([slice(matSliceStartX, matSliceEndX), 
                           slice(matSliceStartY, matSliceEndY)])
    slice_for_final = tuple([slice(matSliceStartX-offsetStartx, matSliceEndX-offsetStartx), 
                             slice(matSliceStartY-offsetStarty, matSliceEndY-offsetStarty)])
    final[slice_for_final] = mat[slice_for_mat]
    return final

mat = np.genfromtxt('data1.csv', dtype='int', delimiter=';')
print('mat: \n', mat)
print('fill:')
fill = int(input())
print('center:')
dot = [int(i) for i in input().split()]
print('mat shape:')
sh = [int(i) for i in input().split()]

final = np.ones(sh, dtype='int') * fill
final = solve(mat, final, dot, sh)
print('final: \n', final)
np.savetxt('out.csv', np.asarray(final), fmt="%s;")