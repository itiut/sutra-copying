import random
import matplotlib.pyplot as plt

random.seed()
rs = [random.normalvariate(0.5, 0.2) for x in range(10000)]
plt.hist(rs, 30)
plt.show()
