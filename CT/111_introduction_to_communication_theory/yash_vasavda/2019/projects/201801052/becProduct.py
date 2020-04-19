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



def Encoder(Message):
	K = len(Message)

	Generator = GeneratorMatrix(K)
	CodedMessage = (np.dot(Generator, Message))%2

	return CodedMessage


def bec(encodedM,probability):
    ErrorM=np.zeros((len(encodedM),), dtype=int)
    NoiseM=encodedM
    
    for i in range(0,len(ErrorM)):
        P=np.around(np.random.rand(1),decimals=3)
       
        if P[0]<probability:
            ErrorM[i]=1
    for i in range(0,len(encodedM)):
        if ErrorM[i]==1:
            NoiseM[i]=-1
    return NoiseM   

def bsc(encodedM,probability):
    ErrorM=np.zeros((len(encodedM),), dtype=int)
    NoiseM=encodedM
    P=np.around(np.random.rand(1),decimals=4)
    for i in range(0,len(encodedM)):
        P=np.around(np.random.rand(1),decimals=4)
        
        if P[0]<probability:
            ErrorM[i]=1
    for i in range(0,len(encodedM)):
        if ErrorM[i]==1:
            if NoiseM[i]==1:
                NoiseM[i]=0
            else:
                  NoiseM[i]=1
    return NoiseM         

def  ParityCheckMatrix(k) :
	sqrtk = int(np.sqrt(k))
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


def decoder(RecievedM,ParityCheckMatrix):
    alpha=RecievedM
    n=len(RecievedM)
    syndrome=np.dot(ParityCheckMatrix,RecievedM)

    for z in range(50):
        tempalpha=alpha
        for i in range(0,n):
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
                    tempalpha[i]=1

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

def DecoderBEC(RecievedMessage,RelationMatrix):
    n=len(RecievedMessage)
    k=int((np.sqrt(n)-1)*(np.sqrt(n)-1))
    alpha=np.array(RecievedMessage)

    check=0
    for i in range(n):
        if (alpha[i]==-1):
            check+=1   
    if check==0:
        return alpha

    for Cycle in range(30):
        tempalpha=np.array(alpha)

        for i in range(n-k):
            indexMatrix=np.zeros(n)
            z=0
            for j in range(0,n):
                if (RelationMatrix[i][j]==1):
                    if (tempalpha[j]==-1):
                        indexMatrix[z]=j
                        z+=1
            if (z!=1):
                continue
            sum=0
            for j in range(0,n):
                if RelationMatrix[i][j]==1 and j!=indexMatrix[0]:
                    sum+=tempalpha[j]                    
            tempalpha[int(indexMatrix[0])]=sum%2

        CheckEqual=tempalpha-alpha
        if (np.count_nonzero(CheckEqual)==0):
            break

        alpha=tempalpha

        check=0
        for i in range(n):
            if (alpha[i]==-1):
                check+=1   
        if check==0:
            break 

    return alpha



def ProductCodeBec(EncodedM,p):
        


    
    
    a=EncodedM
    
    prob=p
    
    NoiseMBec=bec(a,prob)

    
    
    
    DecodedBEC=DecoderBEC(NoiseMBec,ParityCheckMatrix(4))
    
    
    return DecodedBEC



a=[0,0,0,0,0,0,0,0,0]
P=np.zeros(100)
S=np.zeros(100)
for x in range(0,100):
    p=x/100

    P[x]=p
    success=0
    for _ in range(1000):
        b=np.zeros(9)
        z=ProductCodeBec(b,p)
        if np.count_nonzero(z)==0:
            success+=1
    S[x]=success/10
    print(x)

print(P)
print(S)

plt.plot(P,S)
plt.ylabel("%age of Succesful decoding")
plt.xlabel("Probability of Error")
plt.title("Performance of BEC Product Code Decoder for (9,4)Product code ")
plt.show()

            
    
    




















