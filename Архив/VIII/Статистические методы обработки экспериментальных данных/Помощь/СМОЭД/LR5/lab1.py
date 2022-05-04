import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('sample.csv', header=None).iloc[:, 0]

ranked_series = df.sort_values()

variation_series = ranked_series.apply(lambda x: sum(ranked_series == x))
relative_var_series = variation_series.apply(lambda x: x / len(df))

variation_df = pd.DataFrame({'Значение': ranked_series, 'Частота': variation_series,
                             'Относительная частота': relative_var_series}).drop_duplicates()


k = 1.33 + 3.31 * np.log10(len(df))
k = int(np.round(k, 0))
h = (max(ranked_series) - min(ranked_series)) / k
h = int(np.round(h, 0))

means = []
nums = []
relative_nums = []
distrib_nums = []
low_range = []
up_range = []
for i in np.arange(np.min(ranked_series), np.max(ranked_series), h):
    cond = (i <= variation_df['Значение']) & \
           (variation_df['Значение'] < i + h) \
        if i + h < max(ranked_series) \
        else (i <= variation_df['Значение']) & (variation_df['Значение'] <= i + h)

    means.append((i * 2 + h) / 2)
    nums.append(variation_df['Частота'][cond].sum())
    relative_nums.append(variation_df['Относительная частота'][cond].sum())
    distrib_nums.append(variation_df['Относительная частота'][variation_df['Значение'] < i + h].sum())
    low_range.append(i)
    up_range.append(i+h)

if __name__ == '__main__':
    ranked_series.to_csv('Ранжированный_ряд.csv', index=0, header=None)
    variation_df.to_csv('Вариационный_ряд.csv', index=0, header=None)
    inter_df = pd.DataFrame({'Средние значения': means, 'Частота': nums}, dtype=np.int64)
    inter_df.to_csv('Интервальный_Ряд.csv', index=0, header=None)
    inter_df['Частота'] = inter_df['Частота'] / h

    relative_inter_df = pd.DataFrame({'Средние значения': means, 'Относительная частота': relative_nums},
                                     dtype=np.int64)
    relative_inter_df.to_csv('Интервальный_ряд_относительные_частоты.csv', index=0, header=None)

    distrib_df = pd.DataFrame({'Средние значения': means, 'Относительная частота': distrib_nums}, dtype=np.int64)
    distrib_df.to_csv('Функция_распределения.csv', index=0, header=None)

    fig = inter_df.plot(x='Средние значения', y='Частота', title='Полигон для абсолютной частоты')
    plt.show()

    fig = inter_df.plot(x='Средние значения', y='Частота', kind='bar', title='Гистограмма для абсолютной частоты')
    plt.show()

    fig = relative_inter_df.plot(x='Средние значения', y='Относительная частота',
                                 title='Полигон для относительной частоты')
    plt.show()

    fig = relative_inter_df.plot(x='Средние значения', y='Относительная частота', kind='bar',
                                 title='Гистограмма для относительной частоты')
    plt.show()

    fig = distrib_df.plot(x='Средние значения', y='Относительная частота', title='Эмпирическая функция распределения')
    plt.show()
