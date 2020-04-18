import matplotlib
import numpy as np

def decoderBEC(RecievedM,ParityCheckMatrix):
    alpha=RecievedM
    n=len(RecievedM)
    syndrome=np.dot(ParityCheckMatrix,RecievedM)

    for z in range(50):
        tempalpha=alpha
        for i in range(0,n):
            if alpha[i]==-1:
                beta=np.zeros(n)
                SyndromeCount=0
                for j in range(0,np.size(ParityCheckMatrix,0)):
                    beta[0]=alpha[i]

                    if ParityCheckMatrix[j][i]==1:
                        SyndromeCount=SyndromeCount+1
                        sum=0
                        for k in range(0,n):
                            if ParityCheckMatrix[j][k]==1 and k!=i:
                                sum+=alpha[k]                           
                        sum=sum%2                    
                        beta[SyndromeCount]=sum

                Bincount=np.zeros(2)  
                for  t in range(0,SyndromeCount+1):
                    if beta[t]==0:
                        Bincount[0]+=1
                    else:
                        Bincount[1]+=1

                if (Bincount[0]==Bincount[1]):
                    if (beta[0]==1):
                        tempalpha[i]=0
                    else:
                        tempalpha[i]=0

                elif Bincount[0]>Bincount[1]:
                   tempalpha[i]=0

                elif Bincount[0]<Bincount[1]:
                    tempalpha[i]=1

        alpha=tempalpha
        syndrome=(np.dot(ParityCheckMatrix,alpha))%2
        IsSyndromZero=np.count_nonzero(syndrome)
        
        if IsSyndromZero==0:
            break                        

    return alpha          
