import numpy as np
import matplotlib.pyplot as plt

east, time, west = [], [], []
with open('traffic_time.dat', 'r') as datafile:
    for line in datafile:
        data = line.split()
        east.append(float(data[0]))
        time.append(float(data[1]))
        west.append(float(data[2]))

def N(t, A, mu, beta, lamda):
    return A*(mu+t*t)*np.e**(-(lamda*t - beta)**2)

x = np.arange(-12, 12, 0.01)
Awest, muWest, betaWest, lamdaWest = 44.0, 8.53, -0.09, 0.19
Nwest = N(x, Awest, muWest, betaWest, lamdaWest)

plt.figure()
plt.plot(time, west)
plt.plot(x, Nwest, 'r--', lw=1)


y = np.arange(-12, 12, 0.01)
Aeast, muEast, betaEast, lamdaEast = 44.1, 10.5, 0.24, 0.22
Neast = N(y, Aeast, muEast, betaEast, lamdaEast)

plt.figure()
plt.plot(time, east)
plt.plot(y, Neast, 'r--', lw=1)

plt.show()
