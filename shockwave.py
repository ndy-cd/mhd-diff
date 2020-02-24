# -*- coding: utf-8 -*-
"""
Created on Mon Feb 24 13:55:50 2020

@author: Нодари Бартая
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import fsolve
from analyze import getData

def system(variable, params):
    rhoL, rhoR, pL, pR = variable
    rho1, D, v2, p2, rho2 = params
    gamma = 5.0/3.0
    sys = [rho1 - D / (D - v2)]
    sys.append(D - (p2-pR)/rhoR/v2)
    sys.append(pL/rhoL**gamma - p2/rho2**gamma)
    sys.append(p2 - pR * ((gamma+1)*rho1 - (gamma-1)*rhoR) /
                         ((gamma+1)*rhoR - (gamma-1)*rho1))
    sys.append(v2 - 2/(gamma-1)*(np.sqrt(gamma*pL/rhoL) - np.sqrt(gamma*p2/rho2)))
    return sys

# def system2(variable):
#     rhoL, rhoR, pL, pR = variable
#     gamma = 5.0/3.0
#     return (D - (p2-pR)/rhoR/v2),
#             (D - (p2-pR)/rhoR/v2),
#             (pL/rhoL**gamma - p2/rho2**gamma),
#             (p2 - pR * ((gamma+1)*rho1 - (gamma-1)*rhoR) /
#                          ((gamma+1)*rhoR - (gamma-1)*rho1)),
#             (v2 - 2/(gamma-1)*(np.sqrt(gamma*pL/rhoL) - np.sqrt(gamma*p2/rho2)))


ans = fsolve(system, [1, 1, 3, 1], args=[1, 1, 0.1, 3, 1])        

plt.plot(np.linspace(0, 1, 10000), 
            getData('./output.txt', 10000, 20) )
