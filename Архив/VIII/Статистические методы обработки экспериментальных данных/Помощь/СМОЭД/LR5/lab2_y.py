from lab1_y import means, nums, h, df, low_range, up_range, variation_df, ranked_series, k
import pandas as pd
import numpy as np

inter_df = pd.DataFrame({'Средние значения': means, 'Частота': nums}, dtype=np.int64)
C = inter_df.iloc[4, 0]
inter_df['Условные варианты'] = inter_df['Средние значения'].apply(lambda x: (x - C) / h)

moments = []
for num_of_moment in range(1, 5):
    col = 'Условный момент {}'.format(num_of_moment)
    inter_df[col] = inter_df.iloc[:, 1:3].apply(lambda x: x[0]*(x[1]**num_of_moment), axis=1)
    moments.append(inter_df[col].sum() / len(df))
    if __name__ == '__main__':
        print(col, ': ', moments[-1])

inter_df['Проверка'] = inter_df.iloc[:, 1:3].apply(lambda x: x[0]*((x[1]+1)**4), axis=1)

inter_df.to_csv('Таблица.csv', index=0)

start_moment_1_usl = moments[0]*h + C
central_moment_2_usl = (moments[1] - moments[0]**2)*(h**2)
central_moment_3_usl = (moments[2] - 3*moments[1]*moments[0] + 2*(moments[0]**3))*(h**3)
central_moment_4_usl = (moments[3] - 4*moments[2]*moments[0] + 6*moments[1]*(moments[0]**2) - 3*(moments[0]**4))*(h**4)

start_moment_1_emp = inter_df.iloc[:, :2].apply(lambda x: x[0]*x[1], axis=1).sum() / len(df)
central_moment_2_emp = inter_df.iloc[:, :2].apply(lambda x: ((x[0] - start_moment_1_emp)**2)*x[1], axis=1).sum() / len(df)

s = np.sqrt((len(df)/(len(df)-1)) * central_moment_2_emp)
asim = central_moment_3_usl / (s**3)
ecs = central_moment_4_usl / (s**4) - 3

max_low_val = 0
max_num = 0
max_low_val_prev = 0
max_low_val_next = 0

sum_median_prev_nums = 0
for i, (n, l, u) in enumerate(list(zip(nums, low_range, up_range))):
    if n > max_num:
        max_num = n
        max_low_val = l

        try:
            max_low_val_prev = nums[i-1]
            max_low_val_next = nums[i+1]
        except Exception:
            max_low_val_prev = 0
            max_low_val_next = 0

    if i < int(len(nums)/2):
        sum_median_prev_nums += n

moda = max_low_val + h * ((max_num - max_low_val_prev)/(2*max_num - max_low_val_prev - max_low_val_next))
median_int = int(len(nums)/2)
median_num = nums[median_int]
x_0_median = low_range[median_int]

median = x_0_median + h*((0.5 * sum(nums) - sum_median_prev_nums) / median_num)


if __name__ == '__main__':
    print('Начальный условный момент 1го порядка: ', start_moment_1_usl)
    print('Центральный условный момент 2го порядка: ', central_moment_2_usl)
    print('Центральный условный момент 3го порядка: ', central_moment_3_usl)
    print('Центральный условный момент 3го порядка: ', central_moment_4_usl)
    print('Начальный эмпирический момент 1го порядка: ', start_moment_1_emp)
    print('Центральный эмпирический момент 2го порядка: ', central_moment_2_emp)
    print('Асимметрия: ', asim)
    print('Эксцесса: ', ecs)

    print('Мода: ', moda)
    print('Медиана: ', median)
