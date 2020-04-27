import matplotlib.pyplot as plt
import numpy as np
import math

def  ParityCheckMatrix(k) :
	sqrtk = int(math.sqrt(k))
	sqrtn = int(sqrtk + 1)
	n = int(k + 2 * sqrtk + 1)
	OfSet = 0

	ParityCheckMatrix = np.zeros((n - k, n))

	for i in range(0,sqrtk):
		for j in range(OfSet,sqrtk + OfSet + 1):
			ParityCheckMatrix[i][j] = 1

		OfSet = OfSet + sqrtk + 1

	for i in range(sqrtk,2 * sqrtk):
		for j in range(i - sqrtk,n,sqrtn): 
			ParityCheckMatrix[i][j] = 1

	for i in range(0,n):
		ParityCheckMatrix[n-k-1][i] = 1

	return ParityCheckMatrix

z=ParityCheckMatrix(4)
print(z)
