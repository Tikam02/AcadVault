import matplotlib.pyplot as plt
import numpy as np


def bec(encodedM,probability):
    ErrorM=np.zeros((len(encodedM),), dtype=int)
    
    for i in range(0,len(ErrorM)):
        P=np.around(np.random.rand(1),decimals=3)
       
        if P[0]<probability:
            ErrorM[i]=1
    for i in range(0,len(encodedM)):
        if ErrorM[i]==1:
            encodedM[i]=-1
    return encodedM            
            
a=[0,0,0,0,0,0,0,0,0]
P=np.zeros(100)
S=np.zeros(100)
Eb=np.zeros(100)
for x in range(0,100):
    p=x/100

    P[x]=p
    success=0
    for _ in range(10000):
        b=np.zeros(100)
        z=bec(b,p)
        Eb[x]=np.count_nonzero(z)
    print(x)

print(P)
print(S)

plt.plot(P,Eb)
plt.ylabel("Percentage of bits in Error ")
plt.xlabel("Probability of Error")
plt.title("Randomness of Random function ")
plt.show()


                    


        
            


