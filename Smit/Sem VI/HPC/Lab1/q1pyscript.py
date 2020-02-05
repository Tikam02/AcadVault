import matplotlib.pyplot as plt
import numpy as np
with open('bar.txt') as f:
	values = f.readlines()

throughput = []
size = []
for i in values:
	i = i.split()
	try:
		throughput.append(float(i[0]))
		size.append(int(i[1]))
	except:
		print(i[1])

throughput1 = throughput[:int(len(throughput)/2)]
throughput2 = throughput[int(len(throughput)/2):]

size = size[:int(len(size)/2)]

plt.plot(np.log(size)/np.log(2), throughput1)
plt.plot(np.log(size)/np.log(2), throughput2)
#plt.stem(np.log(size)/np.log(2), throughput)
plt.grid(True)
plt.title('Throughput vs Size')
plt.ylabel('Throughput')
plt.xlabel('Size')
plt.legend(['Addition', 'Division'])
plt.savefig('q1b_2.png')
plt.show()
