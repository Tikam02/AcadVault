import matplotlib.pyplot as plt
import numpy as np

def CopySubMatrix(Matrix,SubMatrix,i,j,rows,columns):
	n=rows*rows
	k=columns*columns
	for x in range(0,rows):
		for y in range(0,columns):
			Matrix[((i + x) , (j + y))] = SubMatrix[(x , y)]




def GeneratorMatrix(k):
	n=int(k + (2 * np.sqrt(k)) + 1)
	rootn = int(np.sqrt(n))
	rootk = int(np.sqrt(k))
	Generator=np.zeros((int (n),int(k)))
	Matrix =np.zeros((int(rootn),int(rootk)))
	for i in range(0,rootk):
		Matrix [i,i]=1
		Matrix [(rootn-1) , i]=1
	for i in range(0,rootk):
		CopySubMatrix   (Generator, Matrix, i*rootn, i*rootk, rootn, rootk)
		CopySubMatrix (Generator, Matrix, n - rootn, i*rootk, rootn, rootk)  
	return Generator 


z=GeneratorMatrix(16)
print(z)










