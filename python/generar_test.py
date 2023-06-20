import sys
import numpy as np

esquinas = int(sys.argv[1])
densidad = float(sys.argv[2])

cantidad_posible = (esquinas * (esquinas - 1)) / 2

calles = {}
for i in range(esquinas - 1):
    calles[i, i + 1] = 1000


while (len(calles) + 1) / cantidad_posible < densidad:
    desde = np.random.randint(0, esquinas)
    hasta = np.random.randint(0, esquinas)

    if (desde, hasta) in calles or (hasta, desde) in calles:
        continue

    calles[desde, hasta] = np.random.randint(1, 1000)

import os
os.system(f"notify-send {len(calles) / cantidad_posible}")

print(1)
print(esquinas, len(calles), 0, 1, esquinas)
for (desde, hasta), coste in calles.items():
    print(desde + 1, hasta + 1, coste)
