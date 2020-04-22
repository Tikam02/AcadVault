import numpy as np
import matplotlib.pyplot as plt

inlinks, inpackages = [], []
with open('in_squeeze.dat') as inData:
    for line in inData:
        data = line.split()
        print(data)
        inlinks.append(float(data[0]))
        inpackages.append(float(data[1]))

print(inlinks, inpackages)
outlinks, outpackages = [], []
with open('out_squeeze.dat') as inData:
    for line in inData:
        data = line.split()
        outlinks.append(float(data[0]))
        outpackages.append(float(data[1]))


def N(t, nu, c, lamda):
    return nu+(c*c)*((t+lamda)**(-2))


X1 = np.linspace(start=1, stop=47, num=1000)
X2 = np.linspace(start=1, stop=47, num=1000)
nuinlinks, cinlinks, lamdainlinks = -28.0, 265.0, 2.2
Ninlinks = N(X1, nuinlinks, cinlinks, lamdainlinks)
nuoutlinks, coutlinks, lamdaoutlinks = 1.0, 110.0, 0.45
Noutlinks = N(X2, nuoutlinks, coutlinks, lamdaoutlinks)

plt.figure()
plt.plot(inlinks, inpackages, '+')
plt.xscale('log')
plt.yscale('log')
plt.plot(X1, Ninlinks, 'r--', lw=1)

plt.figure()
plt.plot(outlinks, outpackages, '+')
plt.xscale('log')
plt.yscale('log')
plt.plot(X2, Noutlinks, 'r--', lw=1)

plt.show()
