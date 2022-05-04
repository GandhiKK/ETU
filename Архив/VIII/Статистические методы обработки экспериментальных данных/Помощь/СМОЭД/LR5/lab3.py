from lab2 import means, nums, h, df, low_range, up_range, start_moment_1_emp, central_moment_2_emp, s
import pandas as pd
import numpy as np
import math

print('Мат ожидание: ', start_moment_1_emp)
print('Дисперсия: ', central_moment_2_emp)

print('Среднекв отклонение: ', np.sqrt(central_moment_2_emp))

print('Исправленная выб. дисперсия: ', s)

print('n=', len(df))
t = 1.98
print('t=', t)

sl = s * t / np.sqrt(len(df))
i1 = start_moment_1_emp - sl
i2 = start_moment_1_emp + sl

print('Доверительный интервал для мат. ож. - ({}, {})'.format(i1, i2))

q = 0.14

print('Доверительный интервал для среднекв. отклонения - ({}, {})'.format(s * (1 - q), s * (1 + q)))

low_range.append(up_range[-1])
table = pd.DataFrame({'x': low_range})
table['x-x_mean'] = table['x'].apply(lambda x: x - start_moment_1_emp)
table['v'] = table['x-x_mean'].apply(lambda x: x / s)


def gauss_integral(z):
    return np.sqrt(np.pi) * math.erf(z / np.sqrt(2)) / np.sqrt(2)


def gauss(x):
    return np.exp(-np.power(x, 2.) / 2) / np.sqrt(2 * np.pi)


table['f(v)'] = table['v'].apply(lambda x: gauss_integral(x) / np.sqrt(2 * np.pi))
table.to_csv('Таблица1.csv', index=0)

v_means = []
deltas = []
for i in range(0, len(table['v']) - 1):
    v_means.append((table['v'][i] + table['v'][i + 1]) / 2)
    deltas.append(table['f(v)'][i + 1] - table['f(v)'][i])

table2 = pd.DataFrame({'v_means': v_means, 'p_2': deltas})
table2['f(v_mean)'] = table2['v_means'].apply(gauss)
table2['p_1'] = table2['f(v_mean)'].apply(lambda x: x * h / s)
table2['n_1'] = table2['p_1'].apply(lambda x: x * len(df))
table2['n_2'] = table2['p_2'].apply(lambda x: x * len(df))
table2.to_csv('Таблица2.csv', index=0)


sol1 = pd.DataFrame({'nums': nums, 'n': table2['n_1']})
sol1['nums-n'] = sol1.apply(lambda x: x[0]-x[1], axis=1)
sol1['(nums-n)^2'] = sol1['nums-n'].apply(lambda x: x**2)
sol1['(nums-n)^2/n']=sol1.apply(lambda x: x[3]/x[1], axis=1)
print('Solution 1 summ: ', sol1['(nums-n)^2/n'].sum())
sol1.to_csv('solution1.csv', index=0)

sol2 = pd.DataFrame({'nums': nums, 'n': table2['n_2']})
sol2['nums-n'] = sol2.apply(lambda x: x[0]-x[1], axis=1)
sol2['(nums-n)^2'] = sol2['nums-n'].apply(lambda x: x**2)
sol2['(nums-n)^2/n']=sol2.apply(lambda x: x[3]/x[1], axis=1)
print('Solution 2 summ: ', sol2['(nums-n)^2/n'].sum())
sol2.to_csv('solution1.csv', index=0)
