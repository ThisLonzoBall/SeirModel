import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("results/p1_beta1.00_sigma1.00_gamma0.10.txt")

plt.figure(figsize=(10,8))
plt.plot(data["t"],data["susceptible"] , label='Susceptible')
plt.plot(data["t"], data["exposed"], label='Exposed')
plt.plot(data["t"], data["infected"], label='Infected')
plt.plot(data["t"], data["recovered"], label='Recovered')

plt.xlabel('Time (days)')
plt.ylabel('Population fraction')
plt.title('SEIR Model')
plt.legend()
plt.grid()
plt.show()