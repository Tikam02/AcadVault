import matplotlib.pyplot as plt
import numpy as np


def bsc(encodedM,probability):
    ErrorM=np.zeros((len(encodedM),), dtype=int)
    P=np.around(np.random.rand(1),decimals=4)
    for i in range(0,len(encodedM)):
        P=np.around(np.random.rand(1),decimals=4)
        print(P)
        if P[0]<probability:
            ErrorM[i]=1
    for i in range(0,len(encodedM)):
        if ErrorM[i]==1:
            if encodedM[i]==1:
                encodedM[i]=0
            else:
                  encodedM[i]=1
    return encodedM             







        
            


