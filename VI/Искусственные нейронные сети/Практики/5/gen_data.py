import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as mclr
from matplotlib import gridspec


def gen_data(x, e, n):
    validation_split = 0.2
    train_size, test_size = np.around(
        [n*(1-validation_split), n*validation_split]).astype(int)

    x = np.random.normal(x[0], x[1], n)
    e = np.random.normal(e[0], e[1], n)
    gen_x = np.array([(np.cos(x)*x + e), (-x+e), (np.sqrt(abs(x))+e),
                      (x**2+e), (-abs(x)+4), (x-((x**2)/5)+e)]).transpose()
    gen_y = (np.sin(x)*x + e).reshape((-1, 1))

    train_x = gen_x[:train_size]
    train_y = gen_y[:train_size]
    test_x = gen_x[-test_size:]
    test_y = gen_y[-test_size:]
    return (train_x, train_y), (test_x, test_y), x


def drawResults(data, label, p):
    plt.scatter(data, p[:, 0], s=9,
                c='red', label='sin(X)*X+e')
    plt.legend()
    plt.grid()
    plt.tight_layout()
    plt.show()

    fig = plt.figure(figsize=(13, 6))
    gs = gridspec.GridSpec(2, 3)

    cols = ['red', 'blue', 'green', 'orange', 'purple', 'yellow']
    labels = ['cos(X)+e', '-X+e', 'sqrt(|X|)+e',
              'X^2+e', '-|X|+4', 'X-X^2/5+e']

    for i in range(6):
        plt.subplot(gs[i])
        plt.scatter(data, label[:, i], s=8,
                    c=cols[i], label=labels[i])
        plt.legend()
        plt.grid()

    plt.tight_layout()
    plt.show()


def solution():
    x = np.array([0, 10])
    e = np.array([0, 0.3])
    n = 500

    (train_data, train_targets), (test_data, test_targets), all_x = gen_data(x, e, n)

    np.savetxt('train_data.csv', train_data, delimiter=';')
    np.savetxt('train_targets.csv', train_targets, delimiter=';')
    np.savetxt('test_data.csv', test_data, delimiter=';')
    np.savetxt('test_targets.csv', test_targets, delimiter=';')

    all_y = np.vstack((train_data, test_data))
    all_p = np.vstack((train_targets, test_targets))
    drawResults(all_x, all_y, all_p)