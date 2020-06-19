import matplotlib.pyplot as plt
import numpy as np

c, phi = np.loadtxt('phi_measurements.txt', delimiter=' ', unpack=True)

plt.plot(c, phi)
plt.rc('text', usetex=True)
plt.xlabel(r'$N_c$')
plt.ylabel(r'$\bar{\phi}$')

plt.show()


c, s = np.loadtxt('action_measurements.txt', delimiter=' ', unpack=True)
plt.plot(c, s)
plt.rc('text', usetex=True)
plt.xlabel(r'$N_c$')
plt.ylabel(r'$S_T$')
plt.show()
