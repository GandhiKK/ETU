import pandas as pd
import numpy as np
from lab2_y import inter_df as inter_df_y, means as means_y, df as df_y, up_range as up_range_y, \
    low_range as low_Range_y, h as h_y, s as s_y, moments as m_y, k, start_moment_1_emp as mean_y, nums as nums_y
from lab2 import inter_df as inter_df_x, means as means_x, df as df_x, up_range as up_range_x, \
    low_range as low_Range_x, h as h_x, s as s_x, moments as m_x, start_moment_1_emp as mean_x, nums as nums_x

df = pd.read_csv('sample.csv', header=None)

rows = []

for u_x, l_x in zip(up_range_x, low_Range_x):
    cols = []
    cond_x = (l_x <= df.iloc[:, 0]) & \
             (df.iloc[:, 0] < u_x) \
        if u_x < max(df.iloc[:, 0]) \
        else (l_x <= df.iloc[:, 0]) & (df.iloc[:, 0] <= u_x)

    rng = df.iloc[:, 1][cond_x]
    for u_y, l_y in zip(up_range_y, low_Range_y):
        cond_y = (l_y <= rng) & \
                 (rng < u_y) \
            if u_y < max(rng) \
            else (l_y <= rng) & (rng <= u_y)

        cols.append(sum(cond_y))

    rows.append(cols)

rows = np.array(rows)
cor_table = pd.DataFrame(data=rows, index=means_x, columns=means_y)
cor_table.to_csv('Двумерный интервальный ряд.csv')
C_x = means_x[int(len(means_x) / 2)]
C_y = means_y[int(len(means_y) / 2)]

v_x = (np.array(means_x) - C_x) / h_x
v_y = (np.array(means_y) - C_y) / h_y
cor_table.columns = v_x
cor_table = cor_table.set_index(v_y)

cor_table.to_csv('Корялиционная таблица.csv')
rows = []
for i in range(len(cor_table)):
    cols = []
    for j in range(len(cor_table.columns)):
        cols.append(cor_table.to_numpy()[i][j] * v_y[j] * v_x[i])
    rows.append(cols)

help_table = pd.DataFrame(data=rows, index=v_x, columns=v_y)
help_table.to_csv('Вспомогательная таблица.csv')
sums = help_table.to_numpy().sum(axis=0)
s = sums.sum()


cor = (s - len(df)*m_x[0]*m_y[0]) / (len(df) * (s_x/h_x)*(s_y/h_y))


zb = np.log((1+cor)/(1 - cor)) / 2
o_b = 1 / np.sqrt(len(df) - 3)
z_r = zb + 1.96 *o_b
z_l = zb - 1.96 *o_b

T_n = cor * np.sqrt(len(df) - 2) / np.sqrt(1 - cor**2)

if __name__=='__main__':
    print('Суммы столбцов:', sums)
    print('Сумма: ', s)
    print("Коэф корреляции: ", cor)
    print("S_v: ", (s_x/h_x))
    print("S_u: ", (s_y/h_y))
    print("v_b: ", m_x[0])
    print("u_b: ", m_y[0])
    print(
        '({}:{})'.format((np.exp(2 * z_l) - 1) / (np.exp(2 * z_l) + 1), (np.exp(2 * z_r) - 1) / (np.exp(2 * z_r) + 1)))
    print('k: ', k - 2)
    print('T_krit: ', 1.943)
    print('T_n: ', T_n)

    print('Отвергаем' if T_n > 1.943 else 'Принимаем')
