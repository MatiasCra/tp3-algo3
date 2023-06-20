import sys
import numpy as np

esquinas = int(sys.argv[1])

calles = {}
for i in range(esquinas):
    for j in range(i + 1, esquinas):
        calles[i, j] = np.random.randint(1, 1000)

print(1)
print(esquinas, len(calles), 0, 1, esquinas)
for (desde, hasta), coste in calles.items():
    print(desde + 1, hasta + 1, coste)
