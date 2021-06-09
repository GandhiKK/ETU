import numpy as np
import matplotlib.pyplot as plt
import random
from mpl_toolkits import mplot3d

# A = np.array([5, 6, 0])
# B = np.array([7, 0, 4])
# H = np.array([0, 6, 4])
# AA =np.array([10, 0, 0])
# BB =np.array([0, 7, 0])
# HH =np.array([0, 0, 5])

A = np.array([5, 7, 0])
B = np.array([4, 0, 6])
H = np.array([0, 6, 7])
AA =np.array([8, 0, 0])
BB =np.array([0, 8, 0])
HH =np.array([0, 0, 8])

x = np.array([A[0], B[0], H[0], AA[0], BB[0], HH[0]])
y = np.array([A[1], B[1], H[1], AA[1], BB[1], HH[1]])
z = np.array([A[2], B[2], H[2], AA[2], BB[2], HH[2]])

# закоментированная часть для отображение соединений начальных точек 

# fig = plt.figure()
# ax = plt.axes(projection='3d')
# ax.scatter(x, y, z, 'b')
# for k in range(1):
#     ax.plot([x[0 + 6*k], x[1 + 6*k]], [y[0 + 6*k], y[1 + 6*k]], [z[0 + 6*k], z[1 + 6*k]], color='b')
#     ax.plot([x[0 + 6*k], x[2 + 6*k]], [y[0 + 6*k], y[2 + 6*k]], [z[0 + 6*k], z[2 + 6*k]], color='b')
#     ax.plot([x[0 + 6*k], x[3 + 6*k]], [y[0 + 6*k], y[3 + 6*k]], [z[0 + 6*k], z[3 + 6*k]], color='b')
#     ax.plot([x[0 + 6*k], x[4 + 6*k]], [y[0 + 6*k], y[4 + 6*k]], [z[0 + 6*k], z[4 + 6*k]], color='b')
#     ax.plot([x[1 + 6*k], x[2 + 6*k]], [y[1 + 6*k], y[2 + 6*k]], [z[1 + 6*k], z[2 + 6*k]], color='b')
#     ax.plot([x[1 + 6*k], x[3 + 6*k]], [y[1 + 6*k], y[3 + 6*k]], [z[1 + 6*k], z[3 + 6*k]], color='b')
#     ax.plot([x[1 + 6*k], x[5 + 6*k]], [y[1 + 6*k], y[5 + 6*k]], [z[1 + 6*k], z[5 + 6*k]], color='b')
#     ax.plot([x[2 + 6*k], x[4 + 6*k]], [y[2 + 6*k], y[4 + 6*k]], [z[2 + 6*k], z[4 + 6*k]], color='b')
#     ax.plot([x[2 + 6*k], x[5 + 6*k]], [y[2 + 6*k], y[5 + 6*k]], [z[2 + 6*k], z[5 + 6*k]], color='b')

# ax.set_xlabel('x')
# ax.set_ylabel('y')
# ax.set_zlabel('z')

# plt.show()


# отражение октанта по иксу, ингеку и зету
x = np.append(x, x)
y = np.append(y, -y)
z = np.append(z, z)

x = np.append(x, -x)
y = np.append(y, y)
z = np.append(z, z)

x = np.append(x, x)
y = np.append(y, y)
z = np.append(z, -z)


X = [[A,B,H], [A,BB,H], [A,B,AA], [HH,B,H], 
     [[A[0], -A[1], A[2]], B, [H[0], -H[1], H[2]]],
     [[A[0], -A[1], A[2]], [BB[0], -BB[1], BB[2]], [H[0], -H[1], H[2]]],
     [[A[0], -A[1], A[2]], B, AA],
     [HH, B, [H[0], -H[1], H[2]]],
     [[-A[0], A[1], A[2]], [-B[0], B[1], B[2]], [H[0], H[1], H[2]]],
     [[-A[0], A[1], A[2]], [BB[0], BB[1], BB[2]], [H[0], H[1], H[2]]],
     [[-A[0], A[1], A[2]], [-B[0], B[1], B[2]], [-AA[0], AA[1], AA[2]]],
     [HH, [-B[0], B[1], B[2]], [H[0], H[1], H[2]]],
     [[-A[0], -A[1], A[2]], [-B[0], B[1], B[2]], [H[0], -H[1], H[2]]],
     [[-A[0], -A[1], A[2]], [BB[0], -BB[1], BB[2]], [H[0], -H[1], H[2]]],
     [-A,[-B[0],B[1],B[2]],-AA],
     [HH,[-B[0],B[1],B[2]],[H[0],-H[1],H[2]]],
     [A,[B[0],B[1],-B[2]],[H[0],H[1],-H[2]]],
     [A,BB,[H[0],H[1],-H[2]]],
     [A,[B[0],B[1],-B[2]],AA],
     [-HH,[B[0],B[1],-B[2]],[H[0],H[1],-H[2]]],
     [[A[0],-A[1],A[2]],[B[0],B[1],-B[2]],-H],
     [[A[0],-A[1],A[2]],-BB,-H],
     [[A[0],-A[1],A[2]],[B[0],B[1],-B[2]],AA],
     [-HH,[B[0],B[1],-B[2]],-H],
     [[-A[0],A[1],A[2]],-B,[H[0],H[1],-H[2]]],
     [[-A[0],A[1],A[2]],BB,[H[0],H[1],-H[2]]],
     [[-A[0],A[1],A[2]],-B,-AA],
     [-HH,-B,[H[0],H[1],-H[2]]]
     ]


v1 = np.array([-4, 8, -7])
v2 = np.array([7, -8, -5])
v3 = np.array([v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]])
    
for i in range(len(X)):

    A_ = X[i][0]
    B_ = X[i][1]
    H_ = X[i][2]

    OA1 = np.cross(B_, H_) 
    OB1 = np.cross(A_, H_)
    OH1 = np.cross(A_, B_)

    OA_ = OA1 / np.dot(OA1, A_)
    OB_ = OB1 / np.dot(OB1, B_)
    OH_ = OH1 / np.dot(OH1, H_)

    P = np.array(v3)

    k1 = np.dot(P, OA_) // 0.001 / 1000
    k2 = np.dot(P, OB_) // 0.001 / 1000
    k3 = np.dot(P, OH_) // 0.001 / 1000
    n = k1+k2+k3 // 0.001 / 1000
    print(f'{A_} {B_} {H_}; {k1}; {k2}; {k3}; {"%.3f" % n}')


# # отображение базиса
# # трехгранного угла OABH (x < 0, y > 0, z < 0)
# # ax.plot([0, 2*A[0]], [0, -2*A[1]], [0, -2*A[2]], 'm--')
# # ax.plot([0, 2*B[0]], [0, -2*B[1]], [0, -2*B[2]], 'm--')
# # ax.plot([0, 2*H[0]], [0, -2*H[1]], [0, -2*H[2]], 'm--')

# # отображение вектора V2
# # ax.plot(v2[0], v2[1], v2[2], 'bo')
# # ax.plot([0, v2[0]], [0, v2[1]], [0, v2[2]])

# A_ = [A[0], -A[1], -A[2]]
# B_ = [B[0], -B[1], -B[2]]
# H_ = [H[0], -H[1], -H[2]]

# print(A_, B_, H_)

# OA1 = np.cross(B_, H_) # векторное произведение
# OB1 = np.cross(A_, H_)
# OH1 = np.cross(A_, B_)

# print(OA1, OB1, OH1)

# OA_ = OA1 / np.dot(OA1, A_) # получаем вектор OA'
# OB_ = OB1 / np.dot(OB1, B_) # получаем вектор OB'
# OH_ = OH1 / np.dot(OH1, H_) # получаем вектор OH'

# print(OA_, OB_, OH_)

# # проверяем что скалярное произведение (OA', OA) = 1 (OB', OB) = 1 (OH', OH) = 1
# print('(OA\', OA) = ', np.dot(OA_, A_)) 
# print('(OB\', OB) = ', np.dot(OB_, B_)) 
# print('(OH\', OH) = ', np.dot(OH_, H_)) 

# P = np.array(v2)

# k1 = np.dot(P, OA_) // 0.001 / 1000
# k2 = np.dot(P, OB_) // 0.001 / 1000
# k3 = np.dot(P, OH_) // 0.001 / 1000
# n = k1+k2+k3 // 0.001 / 1000
# # P_ = [k1*A + k2*B + k3*H]
# # print(P_)
# print(k1, k2, k3)
# print('||P||w = ', n)


# # отображение базиса
# # трехгранного угла OABH (x > 0, y = 0, z < 0)
# # ax.plot([0, 2*H[0]], [0, 2*H[1]], [0, -2*H[2]], 'r--')
# # ax.plot([0, 2*B[0]], [0, 2*B[1]], [0, -2*B[2]], 'r--')
# # ax.plot([0, 2*HH[0]], [0, 2*HH[1]], [0, -2*HH[2]], 'r--')

# # отображение вектора V3
# # ax.plot(v3[0], v3[1], v3[2], 'bo')
# # ax.plot([0, v3[0]], [0, v3[1]], [0, v3[2]])

# H_ = [H[0], H[1], -H[2]]
# B_ = [B[0], B[1], -B[2]]
# HH_ = [HH[0], HH[1], -HH[2]]

# # print(H_, B_, HH_)

# OH1 = np.cross(B_, HH_) # векторное произведение
# OB1 = np.cross(H_, HH_)
# OHH1 = np.cross(H_, B_)

# print(OH1, OB1, OHH1)

# OH_ = OH1 / np.dot(OH1, H_) # получаем вектор OA'
# OB_ = OB1 / np.dot(OB1, B_) # получаем вектор OB'
# OHH_ = OHH1 / np.dot(OHH1, HH_) # получаем вектор OH'

# print(OH_, OB_, OHH_)

# # проверяем что скалярное произведение (OA', OA) = 1 (OB', OB) = 1 (OH', OH) = 1
# print('(OH\', OH) = ', np.dot(OH_, H_)) 
# print('(OB\', OB) = ', np.dot(OB_, B_)) 
# print('(OHH\', OHH) = ', np.dot(OHH_, HH_)) 

# P = np.array(v3)

# k1 = np.dot(P, OH_) // 0.001 / 1000
# k2 = np.dot(P, OB_) // 0.001 / 1000
# k3 = np.dot(P, OHH_) // 0.001 / 1000
# n = k1+k2+k3 // 0.001 / 1000
# # P_ = [k1*A + k2*B + k3*H]
# # print(P_)
# print(k1, k2, k3)
# print('||P||w = ', n)


# M = max(
#     (A[0]**2 + A[1]**2 + A[2]**2)**(1/2),
#     (B[0]**2 + B[1]**2 + B[2]**2)**(1/2),
#     (H[0]**2 + H[1]**2 + H[2]**2)**(1/2),
#     (AA[0]**2 + AA[1]**2 + AA[2]**2)**(1/2),
#     (BB[0]**2 + BB[1]**2 + BB[2]**2)**(1/2),
#     (HH[0]**2 + HH[1]**2 + HH[2]**2)**(1/2)
# )

# print('M = ', M)

# m = 4

# u = np.linspace(0, 2 * np.pi, 100)
# v = np.linspace(0, np.pi, 100)

# x = M * np.outer(np.cos(u), np.sin(v))
# y = M * np.outer(np.sin(u), np.sin(v))
# z = M * np.outer(np.ones(np.size(u)), np.cos(v))

# # ax.plot_surface(x, y, z, color='r', alpha=0.5, linewidth=0)

# u = np.linspace(0, 2 * np.pi, 100)
# v = np.linspace(0, np.pi, 100)

# x = m * np.outer(np.cos(u), np.sin(v))
# y = m * np.outer(np.sin(u), np.sin(v))
# z = m * np.outer(np.ones(np.size(u)), np.cos(v))

# ax.plot_surface(x, y, z, color='g', alpha=0.5, linewidth=0)

# ax.set_xlabel('x')
# ax.set_ylabel('y')
# ax.set_zlabel('z')

# plt.show()