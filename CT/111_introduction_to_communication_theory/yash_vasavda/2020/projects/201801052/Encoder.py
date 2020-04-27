import GenM
import numpy as np

def Encoder(Message):
	K = len(Message)

	Generator = GenM.GeneratorMatrix(K)
	CodedMessage = (np.dot(Generator, Message))%2

	return CodedMessage

a=[1,0,1,0]
z=Encoder(a)
print(z)
