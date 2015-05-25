import random
import matplotlib.pyplot as plt

random.seed()
rs = [random.random() for x in range(10000)]
plt.hist(rs, 30)
plt.show()
