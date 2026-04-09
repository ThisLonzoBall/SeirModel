import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("results/p1_output.txt")

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