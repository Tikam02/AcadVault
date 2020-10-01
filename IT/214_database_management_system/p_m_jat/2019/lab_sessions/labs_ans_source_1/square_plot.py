import matplotlib.pyplot as plt
import math

fp = open("parallel_square.txt", "r")
f = open("serial_square.txt", "r")

s = []
p = []
ser = []

for i, j in zip(f, fp):
	t = i.split()
	tp = j.split()
	#print(t[0])
	s.append(math.log(long(t[0]), 2))
	if(tp[1] == "inf"):
		tmp = 0
		sup.append(tmp)
	elif(t[1] == "inf"):
		tmp = float("inf")
		sup.append(tmp)
	else:
		tmp = float(t[1])
		ser.append(tmp)
		tmp = float(tp[1])
		p.append(tmp)

plt.plot(s, ser, marker='^', label="serial")
#plt.ylabel('Speedup')
#plt.xlabel('Size (Bytes)')
'''
fp = open("parallel_square.txt", "r")
f = open("serial_square.txt", "r")

s = []
sup = []

for i, j in zip(f, fp):
        t = i.split()
        tp = j.split()
        #print(t[0])
        s.append(math.log(long(t[0]), 2))
	#print(s)
        if(tp[1] == "inf"):
                tmp = 0
                sup.append(tmp)
        elif(t[1] == "inf"):
                tmp = float("inf")
                sup.append(tmp)
        else:
                tmp = float(t[1])/float(tp[1])
                sup.append(tmp)
'''
plt.plot(s, p, marker='o', label="parallel")
plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=3, ncol=2, mode="expand", borderaxespad=0.)
plt.ylabel('throughput')
plt.xlabel('Size (Bytes)')
plt.savefig('plot_square.png')
plt.show()
