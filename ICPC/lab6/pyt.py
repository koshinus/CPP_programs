#from Methods5 import *
from pylab import *
import numpy as np

startX = 0
endX = 1
n = 2000 # 10, 20
step = 1.0 / (n-1) # 1) 0.1; 2) 0.05
startMu = 10 # mu = 0 is optimal

def f(x,y):
return y + 2.14*x*(1-x) + 6.28

def preciseSolution(x):
return 2.14*x*x - 2.14*x + np.exp(x) + np.exp(-x) - 2

def cauchyMethod(x_j, y_j, z_j, h): # y(x_j)
return z_j + h * f(x_j+h/2, y_j + h/2*f(x_j, y_j))

# 0. Precise solution
preciseSolutionX = np.linspace(startX, endX, (endX-startX) / step) 
preciseSolutionY = preciseSolution(preciseSolutionX) #[preciseSolution(x) for x in preciseSolutionX] 
plot(preciseSolutionX, preciseSolutionY, "g--", label="precise")

# 1. Shooting method
	mu = 0
	newMu = startMu
	shootingX, shootingY = [], []
	while np.abs(newMu - mu) > 0.00000001:
		mu = newMu
		startY = mu
		startZ = mu - 2.14
		shootingX, shootingY, shootingZ = [startX], [startY], [startZ]
		while True:
			shootingX.append(shootingX[-1] + step)
			shootingY.append(shootingY[-1] + step * shootingZ[-1])
			shootingZ.append(cauchyMethod(shootingX[-1], shootingY[-1], shootingZ[-1], step))
			if shootingX[-1]+step-0.00001 >= endX:
				shootingX[-1] = 1
				break
		newMu = mu - (shootingZ[-1]-np.e+1.0/np.e-2.14)/np.e
	plot(shootingX, shootingY, label="mu = " + str(mu))
# print newMu

# 2. Finite difference method
def finiteDifferenceMethod(n):
h = 1.0/n
a = []
b = []
a.append([-1-h-0.5*h*h, 1] + [0 for x in range(2, n)]) # * h^2
b.append([3.14*h*h - 2.14*h]) # * h^2
for j in range(0,n-2):
a.append([0 for x in range(0, j)] + [1, -2-h*h, 1] + [0 for x in range(j+3, n)]) # * h^2
b.append([6.28*h*h+2.14*j*h*(1-j*h)*h*h]) # * h^2
a.append([0 for x in range(0, n-2)] + [1, -1-0.5*h*h]) # * h^2
b.append([-np.e*h+h/np.e-2.14*h+3.14*h*h]) # * h^2
a = np.array(a)
b = np.array(b)
return np.linalg.solve(a,b)
finiteDifferenceX = np.linspace(startX, endX, n)
finiteDifferenceY = finiteDifferenceMethod(n)
plot(finiteDifferenceX, finiteDifferenceY,"r-.", label = "finiteDifference: n = " + str(n))

legend(loc='upper left')
show()