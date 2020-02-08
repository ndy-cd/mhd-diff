# -*- coding: utf-8 -*-
"""
Created on Sun Jan 26 17:55:19 2020

@author: Папа Нодар
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
fileName = 'output_10000.txt'
numeric = getData(fileName, N, 1)


#----------------------------------------------------------------------------#
# начальное распределение
anal = U0(N)
plt.plot(x, anal, label = 'analytic', 
                     linewidth = 3)
plt.plot(x, numeric[0:N:1, 1], 'v', 
                     label = 'numeric  (N=10000)')
plt.plot(np.linspace(0, 1, 100), getData('output_100.txt', 100, 1)[0:100:1, 1], 
                     'o',
                     color = 'brown',
                     markersize = 3,
                     label = 'numeric (N=100)')
plt.legend()
# plt.savefig('initial-transfer.pdf')
plt.show()
print('numeric(0) = \n', numeric[0:N:1, :])

#----------------------------------------------------------------------------#
# профиль в момент времени T
analytic = Un(N, time)
plt.plot(x, analytic)

nNumeric = getData(fileName, N, h)
nNum100 = getData('output_100.txt', 100, 30)

plt.plot(x, nNumeric[0:N:1, 1], 'v', 
                     label = 'numeric (N = 10000)',
                     markersize = 7)
plt.plot(np.linspace(0, 1, 100), nNum100[0:100:1, 1], 'o', 
                     label = 'numeric (N = 100)',
                     markersize = 7,
                     color = 'brown')
plt.plot(x, analytic, label = 'analytic',
                         color = 'magenta',
                         linewidth = 2)
plt.legend()
# plt.savefig('transfer-on-time.pdf')
plt.show()
print('numeric(t) = \n', nNumeric[0:N:1, :])
print('TIME IS EQUAL TO ', nNum100[0, 2])

#----------------------------------------------------------------------------#
# график погрешности
plt.clf()
# plt.ylim(0, 0.51)
plt.xlim(0.6, 1)
plt.ticklabel_format(style='sci', axis='y', scilimits=(1,1))
# plt.yscale("log")
plt.plot(x, abs(nNumeric[0:N:1, 1] - analytic) / numeric[0:N:1, 1],
                     'v-',
                     label = 'N = 10000',
                     linewidth = 2,)
plt.plot(np.linspace(0, 1, 100), 
         abs(nNum100[0:100:1, 1] - Un(100, 29.7)) / nNum100[0:100:1, 1],
                     'o-',
                     label = 'N = 100',
                     linewidth = 2)
plt.legend()
plt.savefig('transfer-mistake.pdf')
#----------------------------------------------------------------------------#
#----------------------------------------------------------------------------#


    
# fig = plt.figure()
# # ims is a list of lists, each row is a list of artists to draw in the
# # current frame; here we are just animating one artist, the image, in
# # each frame
# ims = []
# for i in range(3):
#     im = plt.imshow(arr[i*100:100+i*100:1,0:2], animated=True)
#     ims.append([im])

# ani = animation.ArtistAnimation(fig, ims, interval=50, blit=True,
#                                 repeat_delay=1000)

# ani.save('plot.gif')

# plt.plot()

# plt.show()
