import numpy as np
from scipy.fftpack import fft, ifft, fftshift, rfft
import matplotlib.pyplot as plt


def DFT(x):
    """Compute the discrete Fourier Transform of the 1D array x"""
    x = np.asarray(x, dtype=float)
    N = x.shape[0]
    n = np.arange(N)
    k = n.reshape((N, 1))
    M = np.exp(-2j * np.pi * k * n / N)
    return np.dot(M, x)


def get_foo(n):
    ws = np.arange(0, np.pi + 0.1 * np.pi, 0.1 * np.pi)
    us = np.random.random(size=11)/2.
    As = np.random.randint(1, 11, 11)
    x = np.linspace(0, 32, n)
    y = 0
    for w, u, A in zip(ws, us, As):
        y += A*np.cos(w*x + u)

    y = y / np.sum(As)

    return x, y


def task1_2():
    x, y = get_foo(200)
    plt.plot(x, y, 'r-')
    plt.ylabel(r'$x$(t)')
    plt.xlabel('t')
    plt.title('Analog')
    plt.show()

    x_disc, y_disc = get_foo(32)
    plt.stem(x_disc, y_disc, linefmt='b-')
    plt.ylabel(r'$x$(t)')
    plt.xlabel('t')
    plt.title('Discrete')
    plt.show()

    return x_disc, y_disc


def task3():
    x, y = get_foo(32)
    plt.stem(2*np.abs(fft(y))/32)
    plt.ylabel(r'level')
    plt.xlabel('freq')
    plt.title('DFP')
    plt.show()
    pass


def task4_5():
    task1_2()
    x, y = get_foo(32)
    av_y_5 = np.convolve(y, np.ones(5), 'same') / 5
    av_y_9 = np.convolve(y, np.ones(9), 'same') / 9
    plt.stem(av_y_5)
    plt.ylabel(r'$x$(t)')
    plt.xlabel('t')
    plt.title('Discrete average 5 dots')
    plt.show()
    plt.stem(av_y_9)
    plt.ylabel(r'$x$(t)')
    plt.xlabel('t')
    plt.title('Discrete average 9 dots')
    plt.show()
    pass


def task6():
    x, y = get_foo(32)
    av_y_5 = np.convolve(y, np.ones(5), 'same') / 5
    av_y_9 = np.convolve(y, np.ones(9), 'same') / 9

    f = fft(y)
    f = 2*np.abs(f) / len(f)
    f_5 = fft(av_y_5)
    f_5 = 2 * np.abs(f_5) / len(f_5)
    f_9 = fft(av_y_9)
    f_9 = 2 * np.abs(f_9) / len(f_9)

    plt.stem(f)
    plt.ylabel(r'level')
    plt.xlabel('freq')
    plt.title('DFP orig')
    plt.show()

    plt.stem(f_5)
    plt.ylabel(r'level')
    plt.xlabel('freq')
    plt.title('DFP 5 dots')
    plt.show()

    plt.stem(f_9)
    plt.ylabel(r'level')
    plt.xlabel('freq')
    plt.title('DFP 9 dots')
    plt.show()
    pass


def task7():
    pass


def task8_a():
    x, y = get_foo(32)
    av_y_5 = np.convolve(y, np.array([-3, 12, 17, 12, -3]), 'same') / 35
    av_y_9 = np.convolve(y, np.array([-21, 14, 39, 54, 59, 54, 39, 14, -21]), 'same') / 231

    plt.plot(y, label='orig')
    plt.plot(av_y_5, label='5 dots')
    plt.plot(av_y_9, label='9 dots')
    plt.xlabel('t')
    plt.ylabel(r'$y(t)$')
    plt.legend()
    plt.show()

    f = fft(y)
    f = 2*np.abs(f) / len(f)
    f_5 = fft(av_y_5)
    f_5 = 2 * np.abs(f_5) / len(f_5)
    f_9 = fft(av_y_9)
    f_9 = 2 * np.abs(f_9) / len(f_9)

    plt.stem(f)
    plt.ylabel(r'level')
    plt.xlabel('freq')
    plt.title('DFP orig')
    plt.show()

    plt.stem(f_5)
    plt.ylabel(r'level')
    plt.xlabel('freq')
    plt.title('DFP 5 dots')
    plt.show()

    plt.stem(f_9)
    plt.ylabel(r'level')
    plt.xlabel('freq')
    plt.title('DFP 9 dots')
    plt.show()
    pass


def task8_b():
    x, y = get_foo(32)
    av_y_7 = np.convolve(y, np.array([5, -30, 75, 131, 75, -30, 5]), 'same') / 231
    av_y_11 = np.convolve(y, np.array([13, -45, -10, 60, 120, 143, 120, 60, -10, -45, 13]), 'same') / 429

    plt.plot(y, label='orig')
    plt.plot(av_y_7, label='7 dots')
    plt.plot(av_y_11, label='11 dots')
    plt.xlabel('t')
    plt.ylabel(r'$y(t)$')
    plt.legend()
    plt.show()

    f = fft(y)
    f = 2*np.abs(f) / len(f)
    f_7 = fft(av_y_7)
    f_7 = 2 * np.abs(f_7) / len(f_7)
    f_11 = fft(av_y_11)
    f_11 = 2 * np.abs(f_11) / len(f_11)

    plt.stem(f)
    plt.ylabel(r'level')
    plt.xlabel('freq')
    plt.title('DFP orig')
    plt.show()

    plt.stem(f_7)
    plt.ylabel(r'level')
    plt.xlabel('freq')
    plt.title('DFP 7 dots')
    plt.show()

    plt.stem(f_11)
    plt.ylabel(r'level')
    plt.xlabel('freq')
    plt.title('DFP 11 dots')
    plt.show()
    pass


def task8_c():
    x, y = get_foo(32)
    av_y_diff_1 = np.convolve(y, np.array([-1, 0, 1]), 'same') / 2

    plt.plot(y, label='orig')
    plt.plot(av_y_diff_1, label='diff')
    plt.xlabel('t')
    plt.ylabel(r'$y(t)$')
    plt.legend()
    plt.show()

    f = fft(y)
    f = 2*np.abs(f) / len(f)
    f_5 = fft(av_y_diff_1)
    f_5 = 2 * np.abs(f_5) / len(f_5)

    plt.stem(f)
    plt.ylabel(r'level')
    plt.xlabel('freq')
    plt.title('DFP orig')
    plt.show()

    plt.stem(f_5)
    plt.ylabel(r'level')
    plt.xlabel('freq')
    plt.title('DFP diff')
    plt.show()
    pass


def rect(orig):
    integr = np.empty(len(orig))
    integr[0] = orig[0]
    for i in range(1, len(orig)):
        integr[i] = integr[i-1] + orig[i]
    return integr


def simpson(orig):
    integr = np.empty(len(orig))
    integr[0] = (0 + 4*orig[0] + orig[1]) / 3
    for i in range(1, len(orig)-1):
        integr[i] = integr[i-1] + (orig[i-1] + orig[i] + 4*orig[i+1]) / 3
    return integr


def trap(orig):
    integr = np.empty(len(orig))
    integr[0] = (orig[0] + orig[1]) / 2
    for i in range(1, len(orig)-1):
        integr[i] = integr[i - 1] + (orig[i] + orig[i+1]) / 2
    return integr


def task8_d():
    x, y = get_foo(32)
    y_rect = rect(y)
    y_trap = trap(y)
    y_simps = simpson(y)

    plt.plot(y, label='orig')
    plt.plot(y_rect, label='rect')
    plt.plot(y_trap, label='trap')
    plt.plot(y_simps, label='simpson')
    plt.xlabel('t')
    plt.ylabel(r'$y(t)$')
    plt.legend()
    plt.show()

    f = fft(y)
    f = 2*np.abs(f) / len(f)
    f_rect = fft(y_rect)
    f_rect = 2 * np.abs(f_rect) / len(f_rect)
    f_trap = fft(y_trap)
    f_trap = 2 * np.abs(f_trap) / len(f_trap)
    f_simps = fft(y_simps)
    f_simps = 2 * np.abs(f_simps) / len(f_simps)

    plt.stem(f)
    plt.ylabel(r'level')
    plt.xlabel('freq')
    plt.title('DFP orig')
    plt.show()

    plt.stem(f_rect)
    plt.ylabel(r'level')
    plt.xlabel('freq')
    plt.title('DFP rect')
    plt.show()

    plt.stem(f_trap)
    plt.ylabel(r'level')
    plt.xlabel('freq')
    plt.title('DFP trap')
    plt.show()

    plt.stem(f_simps)
    plt.ylabel(r'level')
    plt.xlabel('freq')
    plt.title('DFP simps')
    plt.show()
    pass


task8_d()
