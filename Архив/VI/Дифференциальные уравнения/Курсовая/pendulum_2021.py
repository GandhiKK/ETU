import numpy as np
import pandas as pd
from scipy.integrate import odeint
import matplotlib.pyplot as plt
plt.style.use('bmh')
figsize = (12, 5)
dpi = 600


g = 9.81
L = 50
theta0 = np.pi/12
t0 = 0
T0 = 200
X, T = [], []
f_counter = []

def approx(t, theta0):
    return theta0*np.cos(np.sqrt(g/L)*t)


t = np.arange(t0, T0, 0.001)
plt.figure(figsize=figsize, dpi=dpi)
plt.title("Аналитическое решение")
plt.plot(t, approx(t, theta0), "b-")
plt.xlabel(r"$t$, (сек)")
plt.ylabel(r"$\theta(t)$, (рад)")
plt.show()


def f(x):
    theta = x[0]
    w = x[1]
    dtheta = w
    dw = -(g/L)*(theta)
    f_counter.append(1)
    return np.array([dtheta, dw])


def callback(x, t):
    T.append(t)
    X.append(x.copy())

def out(x, t):
    return np.array(x)[:, 0], np.array(x)[:, 1], np.array(t)

def euler_method(f, X0, t0, T0, h, call):
    while t0 < T0-h:
        call(X0, t0)
        k1 = f(X0)
        X = X0 + h*k1    
        t0 += h
        X0 = X

h1 = 0.001
X, T, f_counter = [], [], []
euler_method(f, [theta0, 0], t0, T0, h1, callback)
theta1, w1, t1 = out(X, T)
print(len(f_counter))

h2 = 0.01
X, T, f_counter = [], [], []
euler_method(f, [theta0, 0], t0, T0, h2, callback)
theta2, w2, t2 = out(X, T)
print(len(f_counter))

plt.figure(figsize=figsize, dpi=dpi)
plt.title("Метод Эйлера и аналитическое решение")
plt.plot(t1, theta1, "r-", label=r"$h_1=%.3f$"%(h1))
plt.plot(t2, theta2, "b-", label=r"$h_2=%.3f$"%(h2))
plt.plot(t1, approx(t1, theta0), "m--", label=r"Аналитическое решение")
plt.xlabel(r"$t$, (сек)")
plt.ylabel(r"$\theta(t)$, (рад)")
plt.legend(loc='upper left')
plt.show()

he = 0.0001
X, T = [], []
euler_method(f, [theta0, 0], t0, T0, he, callback)
thetae, we, te = out(X, T)
error = np.abs(approx(te, theta0) - thetae)
plt.figure(figsize=figsize, dpi=dpi)
plt.plot(te, error, "b--")
plt.xlabel("Время, $t$(сек)")
plt.ylabel("Ошибка")
plt.title("Ошибка метода Эйлера") 
plt.show()
print("Максимальная ошибка равна ", np.max(error))


def midpoint_method(f, X0, t0, T0, h, call):
    while t0 < T0-h:
        call(X0, t0)
        k1 = f(X0)
        k2 = f(X0 + h/2*k1)
        X = X0 + h*k2
        t0 += h
        X0 = X

h1 = 0.01
X, T, f_counter = [], [], []
midpoint_method(f, [theta0, 0], t0, T0, h1, callback)
theta1, w1, t1 = out(X, T)
print(len(f_counter))
h2 = 0.001
X, T, f_counter = [], [], []
midpoint_method(f, [theta0, 0], t0, T0, h2, callback)
theta2, w2, t2 = out(X, T)
print(len(f_counter))

plt.figure(figsize=figsize, dpi=dpi)
plt.title("Метод средней точки и аналитическое решение")
plt.plot(t1, theta1, "r-", label=r"$h_1=%.3f$"%(h1))
plt.plot(t2, theta2, "b-", label=r"$h_2=%.3f$"%(h2))
plt.plot(t1, approx(t1, theta0), "m--", label=r"Аналитическое решение")
plt.xlabel(r"$t$, (сек)")
plt.ylabel(r"$\theta(t)$, (рад)")
plt.legend(loc='upper left')
plt.show()


he = 0.0001
X, T = [], []
midpoint_method(f, [theta0, 0], t0, T0, he, callback)
thetae, we, te = out(X, T)
error = np.abs(approx(te, theta0) - thetae)
plt.figure(figsize=figsize, dpi=dpi)
plt.plot(te, error, "b--")
plt.xlabel("Время, $t$(сек)")
plt.ylabel("Ошибка")
plt.title("Ошибка метода средней точки") 
plt.show()
print("Максимальная ошибка равна ", np.max(error))


def RK4_method(f, X0, t0, T0, h, call):
    while t0 < T0-h:
        call(X0, t0)
        k1 = f(X0)
        k2 = f(X0 + h/2*k1)
        k3 = f(X0 + h/2*k2)
        k4 =  f(X0 + h*k3)
        X= X0 + h/6*(k1 + 2*k2 + 2*k3 + k4)
        t0 += h
        X0 = X

h1 = 0.01
X, T, f_counter = [], [], []
RK4_method(f, [theta0, 0], t0, T0, h1, callback)
theta1, w1, t1 = out(X, T)
print(len(f_counter))

plt.figure(figsize=figsize, dpi=dpi)
plt.title("Метод Рунге-Кутты 4 и аналитическое решение")
plt.plot(t1, theta1, "m", label=r"$h_1=%.3f$"%(h1))
plt.plot(t1, approx(t1, theta0), "b--", label=r"Аналитическое решение")
plt.xlabel(r"$t$, (сек)")
plt.ylabel(r"$\theta(t)$, (рад)")
plt.legend(loc='upper left')
plt.show()

he = 0.01
X, T = [], []
RK4_method(f, [theta0, 0], t0, T0, he, callback)
thetae, we, te = out(X, T)
error = np.abs(approx(te, theta0) - thetae)
plt.figure(figsize=figsize, dpi=dpi)
plt.plot(te, error, "b--")
plt.xlabel("Время, $t$(сек)")
plt.ylabel("Ошибка")
plt.title("Ошибка метода Рунге-Кутты 4") 
plt.show()
print("Максимальная ошибка равна ", np.max(error))


def true_sol(t, x0, w0):
    return x0 * np.cos(np.sqrt(g/L) * t) + (w0/np.sqrt(g/L)) * np.sin(np.sqrt(g/L) * t)

def error_handler(x, x_hat):
    err = 0
    x = np.array(x)
    x_hat = np.array(x_hat)
    tol = np.zeros(len(x))
    for i in range(len(x)):
        tol[i] = atol + max(abs(x[i]), abs(x_hat[i])) * rtol
        err += ((x_hat[i] - x[i]) / tol[i]) ** 2
    err = np.sqrt(err/(len(x)))
    return err

def BS_method(f, X0, t0, T0, h, call):
    errors, true_errors = [], []
    k1 = f(X0)
    while t0 < T0-h:
        call(X0, t0)
        k2 = f(X0 + h/2*k1)
        k3 = f(X0 + (3*h)/4*k2)
        X_new = X0 + (2*h)/9*k1 + (1*h)/3*k2 + (4*h)/9*k3 
        k4 =  f(X_new)
        X_hat = X0 + h*(7*k1 + 6*k2 + 8*k3 + 3*k4)/24
        err = error_handler(X_new, X_hat)
        h = h * ((1/err)**(1/3))
        t0 += h
        eps = np.abs(X_new[0] - X_hat[0]) # оценка локальной ошибки
        true_eps = np.abs(true_sol(h, X0[0], X0[1]) - X_new[0]) # истинное значение локальной ошибки        
        X0 = X_new
        k1 = k4
        errors.append(eps)
        true_errors.append(true_eps)
    return np.array(errors), np.array(true_errors)

atol, rtol = 2e-10, 2e-10
h1 = 0.01
T0 = 20
X, T, f_counter = [], [], []
e1, te1 = BS_method(f, [theta0, 0], t0, T0, h1, callback)
theta1, w1, t1 = out(X, T)
print(len(f_counter))

plt.figure(figsize=figsize, dpi=dpi)
plt.xlabel("Время, $t$(сек)")
plt.ylabel("Ошибка")
plt.title("Ошибка метода Богацкого-Шампина") 
plt.plot(t1, e1, "m-", label=r'Оценка локальной ошибки')
plt.plot(t1, te1, "b--", label=r'Истинное значение локальной ошибки')
plt.legend(loc='upper left')
plt.show()


def AB_method(f, X0, t0, T0, h, call):
    RK4_method(f, X0, t0, t0+5*h, h, call)
    t0 = t0 + 3*h
    i = 3
    while t0 < T0-h:
        Y = X[i] + h/24. * (55*f(X[i]) - 59*f(X[i-1]) + 37*f(X[i-2]) - 9*f(X[i-3]))      
        t0 = t0 + h
        i += 1
        call(Y, t0)

h1 = 0.01
X, T, f_counter = [], [], []
AB_method(f, [theta0, 0], t0, T0, h1, callback)
theta1, w1, t1 = out(X, T)
print(len(f_counter))

plt.figure(figsize=figsize, dpi=dpi)
plt.plot(t1, np.abs(theta1-approx(t1, theta0)), "m--")
plt.xlabel("Время, $t$(сек)")
plt.ylabel("Ошибка")
plt.title("Ошибка метода Адамса-Башфорта") 
plt.show()
print("Максимальная ошибка равна ", np.max(np.abs(theta1-approx(t1, theta0))))


def AM_method(f, X0, t0, T0, h, call):
    RK4_method(f, X0, t0, t0+5*h, h, call)    
    k0, k1, k2, k3 = f(X[3]), f(X[2]), f(X[1]), f(X[0])
    t0 = t0 + 3*h
    i = 3
    while t0 < T0-h:
        k4, k3, k2, k1 = k3, k2, k1, k0 
        # Предиктор (Адамс-Башфорт)
        Y = X[i] + h/24. * (55*k1 - 59*k2 + 37*k3 - 9*k4)
        k0 = f(Y)
        # Корректор (Адамс-Мултон)
        Y = X[i] + h/24. * (9*k0 + 19*k1 - 5*k2 + 1*k3)
        k0 = f(Y)
        t0 += h
        i += 1
        call(Y, t0)

h1 = 0.01
X, T, f_counter = [], [], []
AM_method(f, [theta0, 0], t0, T0, h1, callback)
theta1, w1, t1 = out(X, T)
print(len(f_counter))

plt.figure(figsize=figsize, dpi=dpi)
plt.plot(t1, np.abs(theta1-approx(t1, theta0)), "m--")
plt.xlabel("Время, $t$(сек)")
plt.ylabel("Ошибка")
plt.title("Ошибка метода Адамса-Мултона") 
plt.show()
print("Максимальная ошибка равна ", np.max(np.abs(theta1-approx(t1, theta0))))


def fsp(X, t):
    f_counter.append(1)
    return np.array([X[1], -(g/L)*(X[0])])
t = np.arange(t0, T0, 0.1)
f_counter = []
tol = 2e-10
Y = odeint(fsp, [theta0, 0], t, atol=tol, rtol=tol)
plt.figure(figsize=figsize, dpi=dpi)
plt.plot(t, np.abs(Y[:, 0] - approx(t, theta0)), "m--")
plt.xlabel("Время, $t$(сек)")
plt.ylabel("Ошибка")
plt.title("Ошибка scipy.odeint") 
plt.show()
print(len(f_counter))
print(np.max(np.abs(Y[:, 0] - approx(t, theta0))))


methods = [midpoint_method, RK4_method, AB_method, AM_method]

T0 = 20
h = 0.1
X, T, f_counter = [], [], []
for method in methods:
    cur_h = h
    print(f'Для метода "{method.__name__}"')
    method(f, [theta0, 0], t0, T0, cur_h, callback)
    theta1, w1, t1 = out(X, T)
    print(f'h = {cur_h} | err = {np.max(np.abs(approx(t1, theta0) - theta1))}')
    while np.max(np.abs(approx(t1, theta0) - theta1)) > 2e-10:
        cur_h *= 0.9
        X, T, f_counter = [], [], []
        method(f, [theta0, 0], t0, T0, cur_h, callback)
        theta1, w1, t1 = out(X, T)
        print(f'h = {cur_h} | err = {np.max(np.abs(approx(t1, theta0) - theta1))} | f_call = {len(f_counter)}')
T0 = 200


T0 = 20
h1 = 0.01
X, T, f_counter = [], [], []
AB_method(f, [theta0, 0], t0, T0, h1, callback)
theta1, w1, t1 = out(X, T)
print(f"Вызовы функции f: {len(f_counter)}")
error = np.abs(approx(t1, theta0) - theta1)
print(f"Максимальная ошибка равна {np.max(error)}\n")
h1 = 0.001
X, T, f_counter = [], [], []
AB_method(f, [theta0, 0], t0, T0, h1, callback)
theta1, w1, t1 = out(X, T)
print(f"Вызовы функции f: {len(f_counter)}")
error = np.abs(approx(t1, theta0) - theta1)
print(f"Максимальная ошибка равна {np.max(error)}\n")
h3 = 0.0001 # численное насыщение
X, T, f_counter = [], [], []
AB_method(f, [theta0, 0], t0, T0, h3, callback)
theta3, w3, t3 = out(X, T)
print(f"Вызовы функции f: {len(f_counter)}")
error = np.abs(approx(t3, theta0) - theta3)
print(f"Максимальная ошибка равна {np.max(error)}\n")


h1 = 0.1
X, T, f_counter = [], [], []
AM_method(f, [theta0, 0], t0, T0, h1, callback)
theta1, w1, t1 = out(X, T)
print(f"Вызовы функции f: {len(f_counter)}")
error = np.abs(approx(t1, theta0) - theta1)
print(f"Максимальная ошибка равна {np.max(error)}\n")
h2 = 0.01
X, T, f_counter = [], [], []
AM_method(f, [theta0, 0], t0, T0, h2, callback)
theta2, w2, t2 = out(X, T)
print(f"Вызовы функции f: {len(f_counter)}")
error = np.abs(approx(t2, theta0) - theta2)
print(f"Максимальная ошибка равна {np.max(error)}\n")
h3 = 0.001
X, T, f_counter = [], [], []
AM_method(f, [theta0, 0], t0, T0, h3, callback)
theta3, w3, t3 = out(X, T)
print(f"Вызовы функции f: {len(f_counter)}")
error = np.abs(approx(t3, theta0) - theta3)
print(f"Максимальная ошибка равна {np.max(error)}\n")
h4 = 0.0001
X, T, f_counter = [], [], []
AM_method(f, [theta0, 0], t0, T0, h4, callback)
theta4, w4, t4 = out(X, T)
print(f"Вызовы функции f: {len(f_counter)}")
error = np.abs(approx(t4, theta0) - theta4)
print(f"Максимальная ошибка равна {np.max(error)}\n")

methods = [AM_method]
T0 = 20
h = 0.1
f_err = 1
X, T, f_counter = [], [], []
for method in methods:
    cur_h = h
    cur_err = f_err
    print(f'Для метода "{method.__name__}"')
    method(f, [theta0, 0], t0, T0, cur_h, callback)
    theta1, w1, t1 = out(X, T)
    print(f'h = {cur_h} | err = {np.max(np.abs(approx(t1, theta0) - theta1))}')
    while np.max(np.abs(approx(t1, theta0) - theta1)) > 2e-10:
        cur_err = np.max(np.abs(approx(t1, theta0) - theta1))
        cur_h *= 0.9
        X, T, f_counter = [], [], []
        method(f, [theta0, 0], t0, T0, cur_h, callback)
        theta1, w1, t1 = out(X, T)
        print(f'h = {cur_h} | err = {np.max(np.abs(approx(t1, theta0) - theta1))} | f_call = {len(f_counter)}')