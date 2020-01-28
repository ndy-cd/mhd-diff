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
def U(x, t):
    return 

# загрузка параметров расчёта из файла
initial = np.loadtxt('file1.txt',
                     usecols = 1)
print(initial)
print('parameters: (TO DO)')
print('N = ', initial[0])

N = 10000               # размер сетки
h = 60                  # номер шага на вывод

x = np.linspace(0, 1, 100)

rho0 = U0(100)
print(rho0)
len(rho0)
input('STOP')

arr = np.zeros(shape = (3))
for i in range (h+2):
    arr = np.loadtxt('output.txt', 
                     skiprows = 1, 
                     usecols = (0, 1),
                     max_rows = i*N + N)



plt.plot(x, arr[0:N:1, 1])
plt.plot(x, arr[h*N:(h*N + N):1, 1])


    

# plt.plot(x, arr[, 1])

#np.savetxt('arr.txt', arr)
# for i in range (3):
    # print(arr[i*100:100+i*100:1,0:3])
    
    
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
    
