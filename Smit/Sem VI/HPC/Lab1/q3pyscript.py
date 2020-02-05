import matplotlib.pyplot as plt
import numpy as np
with open('chad.txt') as f:
	values = f.readline().split(',')

throughput1 = []
throughput2 = []

for i in range(0, len(values)-1, 2):
	print(i+1)
	throughput1.append(values[i])
	throughput2.append(values[i+1])
#print(size, throughput)


#throughput1 = throughput[:int(len(throughput)/2)]
#throughput2 = throughput[int(len(throughput)/2):]

#size = size[:int(len(size)/2)]

plt.plot(throughput1)
plt.plot(throughput2)
#plt.stem(np.log(size)/np.log(2), throughput)
plt.grid(True)
plt.legend(["Normal", "Optimized"])
plt.title('Endtime vs Size')
plt.ylabel('Endtime')
plt.savefig('q1e.png')
plt.show()
