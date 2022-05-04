from lab4 import df, cor, s_x, s_y, mean_x, mean_y, means_x, means_y, k, cor_table, nums_x, nums_y
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


def mean_sq_regression(s1, s2, mean1, mean2, cor, pref='y(x)='):
    def inner_foo(x, pr=False):
        if pr:
            print(pref + '{} * x'.format(cor * s1 / s2), '{0:+}'.format(mean1 - cor * s1 / s2 * mean2))
        a1 = cor * s1 / s2
        a2 = mean1 - cor * s1 / s2 * mean2
        return a2 + a1 * x

    return inner_foo


msr_x = mean_sq_regression(s_x, s_y, mean_x, mean_y, cor, 'x(y)=')
msr_y = mean_sq_regression(s_y, s_x, mean_y, mean_x, cor)

ax = df.plot.scatter(x=0, y=1)
y1 = np.array([60, 200])
x2 = np.array([300, 600])

ax.plot(x2, msr_y(x2, pr=True), label='y(x)')
ax.plot(msr_x(y1, pr=True), y1, label='x(y)')

line1 = np.array([[x2[0], msr_y(x2)[0]], [x2[1], msr_y(x2)[1]]])
line2 = np.array([[msr_x(y1)[0], y1[0]], [msr_x(y1)[1], y1[1]]])

t, s = np.linalg.solve(np.array([line1[1] - line1[0], line2[0] - line2[1]]).T, line2[0] - line1[0])

ax.plot(*((1 - t) * line1[0] + t * line1[1]), 'o', color='red')
ax.set_title('Regression')
ax.set_xlabel('x')
ax.set_ylabel('y')
plt.legend()
plt.show()

print('Остаточная дисперсия y: ', (np.array(means_y) - msr_y(np.array(means_x))).sum() / k)
print('Остаточная дисперсия x: ', (np.array(means_x) - msr_x(np.array(means_y))).sum() / k)

cors = cor_table.to_numpy()
rows_y = []
vars_y = []
for row in range(len(cor_table)):
    cols = []
    var = []
    for col in range(len(cor_table.columns)):
        cols.append(cors[row][col] * means_y[col])
    rows_y.append(sum(cols) / nums_x[row])
    for col in range(len(cor_table.columns)):
        var.append(((means_y[col] - rows_y[-1]) ** 2) * cors[row][col])
    vars_y.append(sum(var) / nums_x[row])

cols_x = []
vars_x = []
for col in range(len(cor_table.columns)):
    rows = []
    var = []
    for row in range(len(cor_table)):
        rows.append(cors[row][col] * means_x[row])
    cols_x.append(sum(rows) / nums_y[col])
    for row in range(len(cor_table)):
        var.append(((means_x[col] - cols_x[-1]) ** 2) * cors[row][col])
    vars_x.append(sum(var) / nums_y[col])

cor_table['n_y'] = nums_x
cor_table['mean_y_gr'] = rows_y
cor_table['D_y_gr'] = vars_y
cor_table.to_csv('Table1.csv')
pd.DataFrame({'n_x': nums_y, 'x_mean_gr': cols_x, 'D_x_gr': vars_x}).T.to_csv('Table1_last_rows.csv')

x_t = pd.DataFrame({'n_x': nums_y, 'x_mean_gr': cols_x, 'D_x_gr': vars_x})

D_ingr_yx = (cor_table['D_y_gr'].to_numpy() * x_t['n_x'].to_numpy()).sum() / len(df)
D_ingr_xy = (x_t['D_x_gr'].to_numpy() * cor_table['n_y'].to_numpy()).sum() / len(df)
print('D внутригр xy = {}'.format(D_ingr_xy))
print('D внутригр yx = {}'.format(D_ingr_yx))

D_betwgr_yx = (((cor_table['mean_y_gr'] - mean_y) ** 2).to_numpy() * x_t['n_x'].to_numpy()).sum() / len(df)
D_betwgr_xy = (((x_t['x_mean_gr'] - mean_x) ** 2).to_numpy() * cor_table['n_y'].to_numpy()).sum() / len(df)

print('D межгр xy = {}'.format(D_betwgr_xy))
print('D межгр yx = {}'.format(D_betwgr_yx))

D_gen_xy = D_ingr_xy + D_betwgr_xy
D_gen_yx = D_ingr_yx + D_betwgr_yx

print('D общая xy = {}'.format(D_gen_xy))
print('D общая yx = {}'.format(D_gen_yx))

n_xy = np.sqrt(D_betwgr_xy / D_gen_xy)
n_yx = np.sqrt(D_betwgr_yx / D_gen_yx)

print('n xy = {}'.format(n_xy))
print('n yx = {}'.format(n_yx))

x = df.iloc[:, 0]
y = df.iloc[:, 1]

system = []
b = []
for i in range(3):
    line = []
    for j in range(3):
        line.append((x ** (4 - i - j)).sum())
    system.append(line)
    b.append((y * (x ** (2 - i))).sum())

res = np.linalg.solve(np.array(system), np.array(b))

print('a={}, b={}, c={}'.format(*res))


def sq_regr(x):
    return res[0] * x ** 2 + res[1] * x + res[2]


ax = df.plot.scatter(x=0, y=1)
y1 = np.array([60, 200])
x2 = np.array([300, 600])

ax.plot(x2, msr_y(x2), label='y(x)')
ax.plot(msr_x(y1), y1, label='x(y)')

x3 = np.linspace(300, 600)
ax.plot(x3, sq_regr(x3), label='y(x)^2')

ax.plot(*((1 - t) * line1[0] + t * line1[1]), 'o', color='red')
ax.set_title('Regression')
ax.set_xlabel('x')
ax.set_ylabel('y')


y = df.iloc[:, 1]
x = df.iloc[:, 0]
z = np.log(y)
a1 = (len(df) * (x*z).sum() - x.sum() * z.sum())/(len(df)*(x*x).sum()-x.sum()**2)
a0 = z.mean() - a1 * x.mean()

b = a1
a = np.exp(a0)

#ax.plot(x3, a * np.exp(b*x3), label='y(x) = b1*exp(b2*x)')
plt.legend()
plt.show()
print('b0={}, b1={}'.format(a, b))
