import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.colors as colors
import random
from itertools import combinations

np.random.seed(4)
random.seed(4)
df = pd.read_csv('sample.csv', header=None)
df.columns = ['x', 'y']

ax = df.plot.scatter(x=0, y=1)
ax.set_title('Выборка')
plt.show()

df = (df - df.min(axis=0)) / (df.max(axis=0) - df.min(axis=0))
# df = (df - df.mean(axis=0)) / df.std(axis=0)

ax = df.plot.scatter(x=0, y=1)
ax.set_title('Нормализованная выборка')
plt.show()

up_limit = np.sqrt(len(df) / 2).astype(np.int64)
print('Верхняя граница: {}'.format(up_limit))


def f1():
    distances = df.apply(lambda x: np.min(dists_to_centroids(x, centroids)) ** 2, axis=1)
    return distances.sum()


def get_metrics():
    f2 = []
    f3 = []
    for i, centroid in enumerate(centroids.to_numpy()):
        cluster_dists = []
        f3.append(df[cl_centroids == i].var().mean())
        for comb in combinations(df[cl_centroids == i].to_numpy(), 2):
            cluster_dists.append(np.linalg.norm(comb[0] - comb[1]) ** 2)
        f2.append(sum(cluster_dists))
    f2 = sum(f2)
    f3 = sum(f3)

    print('----\nF1 = {}\nF2 = {}\nF3 = {}\n----'.format(f1(), f2, f3))


def dists_to_centroids(point, cur_centroids):
    return cur_centroids.apply(lambda x: np.linalg.norm(x - point), axis=1)


def get_closest_centroids(points, cur_centroids):
    return points.apply(lambda x: np.argmin(dists_to_centroids(x, cur_centroids)), axis=1)


def move_centroids(points, closest_centroids, num_of_centroids):
    return np.array([points[closest_centroids == c].mean(axis=0) for c in range(num_of_centroids)])


for N in range(2, up_limit+1):
    print(N)
    dict_colors = {i: name for i, (name, col) in enumerate(random.choices(list(colors.CSS4_COLORS.items()), k=N))}
    list_colors = [name for name, col in random.choices(list(colors.CSS4_COLORS.items()), k=N)]
    centroids = df.sample(N)

    i = 1
    while True:
        prev_centroids = centroids.copy()
        cl_centroids = get_closest_centroids(df, centroids)
        centroids[:] = move_centroids(df, cl_centroids, N)

        ax = df.plot.scatter(x=0, y=1, c=cl_centroids.apply(lambda x: dict_colors[x]))
        ax.scatter(centroids.x, centroids.y, c='red')
        ax.set_title('K means {}, шаг - {}'.format(N, i))
        plt.show()
        # print('step {}'.format(i))
        i += 1

        if ((prev_centroids - centroids).mean(axis=0).abs() < [0.0001, 0.0001]).all():
            break

    cl_centroids = get_closest_centroids(df, centroids)
    get_metrics()
    rows = []
    for i, centroid in enumerate(centroids.to_numpy()):
        rows.append([i + 1, '({} : {})'.format(*centroid), sum(cl_centroids == i)])

    res = pd.DataFrame(rows, columns=['Номер кластера', 'Центр кластера', 'Количество элементов в кластере'])
    res.to_csv('Таблица{}.csv'.format(N), index=False)
