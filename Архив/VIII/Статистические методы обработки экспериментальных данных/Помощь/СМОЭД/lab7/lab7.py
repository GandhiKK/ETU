import numpy as np
import sys
import math
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.colors as colors
import random
from itertools import combinations
from scipy.spatial import distance


random.seed(5)
np.random.seed(5)
df = pd.read_csv('sample.csv', header=None)
df.columns = ['x', 'y']

ax = df.plot.scatter(x=0, y=1)
ax.set_title('Выборка')
plt.show()

df = (df - df.mean(axis=0)) / df.std(axis=0)
noise = np.random.normal(0, 0.1, [len(df), 2])

df = df + noise

ax = df.plot.scatter(x=0, y=1)
ax.set_title('Нормализованная выборка')
xlim = ax.get_xlim()
ylim = ax.get_ylim()
plt.show()

distances = distance.cdist(df, df)
distances = set(distances.flatten().tolist()) - {0}
R_min = min(distances)
R_max = max(distances)


def plot_step(step_points, circle, title):
    ax = step_points.plot.scatter(x=0, y=1)
    ax.set_title(title)
    ax.set_xlim(xlim)
    ax.set_ylim(ylim)
    c = plt.Circle(circle, R, alpha=0.1)
    ax.add_patch(c)
    plt.show()


points = df.copy()
R = np.float32(1.2) # 0.8
i = 0
df['Clusters'] = 0
while len(points):
    circle = points.iloc[:, :2].sample(1)
    j = 0
    while True:
        prev_circle = circle

        points_in_circle = points.apply(lambda x: np.linalg.norm(x - circle) <= R, axis=1)
        circle = points[points_in_circle].mean(axis=0)
        plot_step(points, circle, 'R = {}, Шаг {}.{}'.format(R.round(1), i + 1, j + 1))
        j += 1
        if ((circle - prev_circle).abs() < 0.0001).all().all():
            break

    points_in_circle = points.apply(lambda x: np.linalg.norm(x - circle) <= R, axis=1)
    df.loc[points_in_circle.index, 'Clusters'] = points_in_circle * i
    points = points[~ points_in_circle]
    i += 1

list_colors = np.array([name for name, col in colors.CSS4_COLORS.items()])
np.random.shuffle(list_colors)
ax = df.plot.scatter(x=0, y=1, c=list_colors[df['Clusters']], s=50)
for c in range(i):
    circle = df[df['Clusters'] == c].iloc[:, :2].mean(axis=0)
    ax.scatter(circle[0], circle[1], c='red')
ax.set_title('Результат кластеризации, R = {}'.format(R.round(1)))
plt.show()

f1 = []
f2 = []
f3 = []
for c in range(i):
    if np.isnan(df[df['Clusters'] == c].iloc[:, :2].var().mean()):
        continue
    circle = df[df['Clusters'] == c].iloc[:, :2].mean(axis=0)
    cluster_dists = []
    f3.append(df[df['Clusters'] == c].iloc[:, :2].var().mean())
    for comb in combinations(df[df['Clusters'] == c].iloc[:, :2].to_numpy(), 2):
        cluster_dists.append(np.linalg.norm(comb[0] - comb[1]) ** 2)
    f2.append(sum(cluster_dists))
    f1.append(sum(np.linalg.norm(df[df['Clusters'] == c].iloc[:, :2] - circle, axis=1) ** 2))
f2 = sum(f2)
f3 = sum(f3)
f1 = sum(f1)

print('R = {}:\nF1 = {}\nF2 = {}\nF3 = {}'.format(R, f1, f2, f3))

rows = []
for centroid_id in range(i):
    centroid = df[df['Clusters'] == centroid_id].iloc[:, :2]
    rows.append([centroid_id + 1, '({} : {})'.format(*(centroid.mean(axis=0))), len(centroid)])

res = pd.DataFrame(rows, columns=['Номер кластера', 'Центр кластера', 'Количество элементов в кластере'])
res.to_csv('Таблица.csv', index=False)

print('R_min = {}\nR_max = {}'.format(R_min, R_max))
