# -*- coding: utf-8 -*-
"""
Created on Sun Jan 26 17:55:19 2020

@author: Нодари Бартая
"""
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# НУ
def U0(N):
    U = np.ones(N, dtype=float)
    for i in range(N):
        if i < N*0.4 or i >= N*0.6:
            U[i] = 0.4
        elif i >= N*0.4 and i < N*0.6:
            U[i] = 0.8
    return U

# Аналитическое решение
def Un(N, t):
    U = np.ones(N, dtype=float)
    for i in range(N):
        if i < (N*0.4 + t-1) or i >= (N*0.6 + t -1):
            U[i] = 0.4
        elif i >= (N*0.4 + t-1) and i < (N*0.6 + t - 1):
            U[i] = 0.8
    return U

# подгрузка из выходных данных кода
def getData(fileName, N, n):
    if n == 1:
        skip = 0
    else:
        skip = (N+1)*n
    arr = np.zeros(shape = (3))
    arr = np.loadtxt(fileName, 
                     skiprows = 1 + skip, 
                     usecols = (0, 1, 3),
                     max_rows = N + 1)
    return arr

#----------------------------------------------------------------------------#
#--------------------------------> используется для N1000C99
# загрузка параметров расчёта из файла
initial = np.loadtxt('file1.txt',
                     usecols = 1)
print(initial)
print('parameters: (TO DO)')
print('N = ', initial[0])

N = 10000               # размер сетки
h = 60                  # номер блока на вывод
time = 2999.4           # время из расчёта

x = np.linspace(0, 1, N)

rho0 = U0(100)
print(rho0)
len(rho0)

# получение массива релузльтатов
fileName = '.\outputs\output_10000.txt'
numeric = getData(fileName, N, 1)
#----------------------------------------------------------------------------#
# начальное распределение
anal = U0(N)

plt.plot(x, numeric[0:N:1, 1], 'v', color = 'brown',
                     label = 'numeric  (N=1000)',
                     markersize = 7)
plt.plot(np.linspace(0, 1, 100), 
                     getData('.\outputs\output_100.txt', 100, 1)[0:100:1, 1], 
                     'o',
                     color = 'limegreen',
                     markersize = 5,
                     label = 'numeric (N=100)')
plt.plot(np.linspace(0, 1, 30), 
                     getData('.\outputs\output_30.txt', 30, 1)[0:30:1, 1], 
                     'D',
                     color = 'darkslategrey',
                     markersize = 5,
                     label = 'numeric (N=30)')
plt.plot(x, anal, 'k',label = 'analytic', 
                     linewidth = 1)
plt.legend()
# plt.show()
plt.savefig('initial-transfer.pdf')
print('numeric(0) = \n', numeric[0:N:1, :])

#----------------------------------------------------------------------------#
# профиль в момент времени T
plt.figure(2, figsize=(6.4, 9.6))

#---------------------> Courant = 0.2
# plt.subplot(321)
plt.subplot2grid((3, 3), (0, 0), colspan = 2)
plt.xlim(0.4, 1)
# plt.text(0.4, 1.1, 'Уравнение переноса\nчисло Куранта = 0.2, 0.6, 0.99 ', 
#          fontsize=10)

nNum1000C02 = getData('.\outputs\output_1000_C02.txt', 1000, 75)
nNum100C02 = getData('.\outputs\output_100_C02.txt', 100, 75)
nNum30C02 = getData('.\outputs\output_30_C02.txt', 30, 45)

plt.plot(np.linspace(0, 1, 1000), nNum1000C02[0:1000:1, 1], 'v', 
                      label = 'numeric (N = 1000)',
                      markersize = 5,
                      color = 'brown')
plt.plot(np.linspace(0, 1, 100), nNum100C02[0:100:1, 1], 'o', 
                     label = 'numeric (N = 100)',
                     markersize = 7,
                     color = 'limegreen')
plt.plot(np.linspace(0, 1, 30), nNum30C02[0:30:1, 1], 'D', 
                     label = 'numeric (N = 30)',
                     markersize = 7,
                     color = 'darkslategrey')
plt.plot(np.linspace(0, 1, 10000), Un(10000, 3000), 'k')

#---------------------> Courant = 0.6
# plt.subplot(323)
plt.subplot2grid((3, 3), (1, 0), colspan = 2)
plt.xlim(0.5, 1)

nNum1000C06 = getData('.\outputs\output_1000_C06.txt', 1000, 50)
nNum100C06 = getData('.\outputs\output_100_C06.txt', 100, 50)
nNum30C06 = getData('.\outputs\output_30_C06.txt', 30, 15)

plt.plot(np.linspace(0, 1, 1000), nNum1000C06[0:1000:1, 1], 'v', 
                      label = 'numeric (N = 1000)',
                      markersize = 5,
                      color = 'brown')
plt.plot(np.linspace(0, 1, 100), nNum100C06[0:100:1, 1], 'o', 
                     label = 'numeric (N = 100)',
                     markersize = 7,
                     color = 'limegreen')
plt.plot(np.linspace(0, 1, 30), nNum30C06[0:30:1, 1], 'D', 
                     label = 'numeric (N = 30)',
                     markersize = 7,
                     color = 'darkslategrey')
plt.plot(np.linspace(0, 1, 10000), Un(10000, 3000), 'k')

#---------------------> Courant = 0.99
# plt.subplot(325)
plt.subplot2grid((3, 3), (2, 0), colspan = 2)
analytic = Un(N, time)
plt.plot(x, analytic)
plt.xlim(0.6, 1)

nNumeric = getData(fileName, N, h)
nNum100 = getData('.\outputs\output_100.txt', 100, 30)
nNum30 = getData('.\outputs\output_30.txt', 30, 9)

plt.plot(x, nNumeric[0:N:1, 1], 'v', 
                     label = 'numeric (N = 1000)',
                     color = 'brown',
                     markersize = 6)
plt.plot(np.linspace(0, 1, 100), nNum100[0:100:1, 1], 'o', 
                     label = 'numeric (N = 100)',
                     markersize = 7,
                     color = 'limegreen')
plt.plot(np.linspace(0, 1, 30), nNum30[0:30:1, 1], 'D', 
                     label = 'numeric (N = 30)',
                     markersize = 7,
                     color = 'darkslategrey')
plt.plot(x, analytic, label = 'analytic',
                         color = 'k',
                         linewidth = 1)
plt.legend()
# plt.legend(bbox_to_anchor=(0.95, 3.9), loc='upper left', borderaxespad=0.)
# plt.savefig('transfer-on-time.pdf')
# plt.show()
print('numeric(t) = \n', nNumeric[0:N:1, :])
print('TIME IS EQUAL TO ', nNum100[0, 2])

#----------------------------------------------------------------------------#
# график погрешности
#---------------------> Courant = 0.2
# plt.subplot(322)
plt.subplot2grid((3, 3), (0, 2))
plt.xlim(0.2, 1)
plt.plot(np.linspace(0, 1, 1000), 
          abs(nNum1000C02[0:1000:1, 1] - Un(1000, 300)) / nNum1000C02[0:1000:1, 1],
                      'v-',
                      color = 'brown',
                      linewidth = 1)
plt.plot(np.linspace(0, 1, 100), 
          abs(nNum100C02[0:100:1, 1] - Un(100, 30)) / nNum100C02[0:100:1, 1],
                      'o-',
                      color = 'limegreen',
                      linewidth = 1)
plt.plot(np.linspace(0, 1, 30), 
          abs(nNum30C02[0:30:1, 1] - Un(30, 9)) / nNum30C02[0:30:1, 1],
                      'D-',
                      color = 'darkslategrey',
                      linewidth = 1)
#---------------------> Courant = 0.6
# plt.subplot(324)
plt.subplot2grid((3, 3), (1, 2))
plt.ticklabel_format(axis='y', style='sci', scilimits=(1, 0))


plt.xlim(0.4, 1)
plt.plot(np.linspace(0, 1, 1000), 
          abs(nNum1000C06[0:1000:1, 1] - Un(1000, 300)) / nNum1000C06[0:1000:1, 1],
                      'v-',
                      color = 'brown',
                      linewidth = 1)
plt.plot(np.linspace(0, 1, 100), 
          abs(nNum100C06[0:100:1, 1] - Un(100, 30)) / nNum100C06[0:100:1, 1],
                      'o-',
                      color = 'limegreen',
                      linewidth = 1)
plt.plot(np.linspace(0, 1, 30), 
          abs(nNum30C06[0:30:1, 1] - Un(30, 9)) / nNum30C06[0:30:1, 1],
                      'D-',
                      color = 'darkslategrey',
                      linewidth = 1)
#---------------------> Courant = 0.99
# plt.subplot(326)
plt.subplot2grid((3, 3), (2, 2))
plt.xlim(0.6, 1)

plt.plot(np.linspace(0, 1, N), 
          abs(nNumeric[0:N:1, 1] - analytic) / numeric[0:N:1, 1],
                      'v-',
                      color = 'brown',
                      linewidth = 1)
plt.plot(np.linspace(0, 1, 100), 
          abs(nNum100[0:100:1, 1] - Un(100, 29.7)) / nNum100[0:100:1, 1],
                      'o-',
                      color = 'limegreen',
                      markersize = 5,
                      linewidth = 1)
plt.plot(np.linspace(0, 1, 30), 
          abs(nNum30[0:30:1, 1] - Un(30, 9.01)) / nNum30[0:30:1, 1],
                      'D-',
                      color = 'darkslategrey',
                      linewidth = 1)
plt.tight_layout(h_pad=0.1, w_pad=0.1)
# plt.savefig('transfer.pdf')
#----------------------------------------------------------------------------#
#----------------------------------------------------------------------------#