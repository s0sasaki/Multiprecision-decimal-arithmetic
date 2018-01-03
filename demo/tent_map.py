def tent(x):
	if 2*x < 1:
		return 2*x
	else:
		return 2-2*x
v = 0.1
data = []
for i in range(100):
	data.append(v)
	v = tent(v)
import matplotlib.pyplot as plt
plt.plot(data)
plt.show()
