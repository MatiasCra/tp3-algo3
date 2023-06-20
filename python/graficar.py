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


plt.plot(densidades, ralo, label="Priority queue (O((m + n) logn))")
plt.plot(densidades, denso, label="Sin heap (O(n^2))")
plt.plot(densidades, fib, label="Fibonacci heap (O(n logn + m))")
plt.plot(densidades, bel, label="Bellman-Ford (O(n * m))")
plt.xlabel("Densidad")
plt.ylabel("Tiempo (seg)")
plt.title("Tiempo por densidad")
plt.legend()
plt.show()
