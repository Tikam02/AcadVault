import matplotlib.pyplot as plt
import numpy as np
import ParityCheckMatrix
import GenM
import BEC
import BSC
import Encoder





def decoder(RecievedM,ParityCheckMatrix):
    alpha=RecievedM
    n=len(RecievedM)
    syndrome=np.dot(ParityCheckMatrix,RecievedM)
    
    for z in range(50):
        tempalpha=alpha
        for i in range(0,n):
            beta=np.empty(n)
        for j in range(0,np.size(ParityCheckMatrix,0)):
            beta[0]=alpha[i]
            if ParityCheckMatrix[j][i]==1:
                SyndromeCount=0
                for k in range(0,n):
                    sum=0
                    if ParityCheckMatrix[j][k]==1 and k!=i:
                        sum+=alpha[i]
                sum=sum%2
                beta[SyndromeCount+1]=sum
                SyndromeCount+=1
        Bincount=np.zeros(2,dtype='int')    
        for  t in range(0,SyndromeCount):
            if beta[t]==0:
                Bincount[0]+=1
            else:
                Bincount[1]+=1   

        
        if Bincount[0]>Bincount[1]:
            tempalpha[i]=0
        elif Bincount[0]<Bincount[1]:
            tempalpha[i]=1
        alpha=tempalpha  
        print(tempalpha)
        if np.count_nonzero(np.dot(ParityCheckMatrix,alpha))==0:
            return alpha
      
    return alpha        




                        
a=[0,1,0,0,0,1,1,1,1]
p=ParityCheckMatrix.ParityCheckMatrix(4)
d=decoder(a,p)
print(d)
                        