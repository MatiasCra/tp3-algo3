import sys
import matplotlib.pyplot as plt

with open(sys.argv[1]) as f:
    lines = f.readlines()

ralo = []
denso = []
fib = []
bel = []

densidades = [i * 0.1 for i in range(1, 10)]

for i, line in enumerate(lines):
    match i % 4:
        case 0:
            ralo.append(float(line))
        case 1:
            denso.append(float(line))
        case 2:
            fib.append(float(line))
        case 3:
            bel.append(float(line))


plt.plot(densidades, ralo, label="Ralo")
plt.plot(densidades, denso, label="Denso")
plt.plot(densidades, fib, label="Fibonacci Heap")
plt.plot(densidades, bel, label="Bellmand-Ford")
plt.xlabel("Densidad")
plt.ylabel("Tiempo (seg)")
plt.title("Tiempo por densidad")
plt.legend()
plt.show()
