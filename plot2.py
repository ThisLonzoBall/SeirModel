import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results/p2_beta1.00_sigma0.10_gamma0.01_N250.txt")

plt.figure(figsize=(10,8))
plt.plot(df["step"], df["susceptible"], label="Susceptible")
plt.plot(df["step"], df["exposed"], label="Exposed")
plt.plot(df["step"], df["infected"], label="Infected")
plt.plot(df["step"], df["recovered"], label="Recovered")

plt.xlabel("Monte Carlo Step")
plt.ylabel("Population")
plt.title(f"Monte Carlo SEIR simulation")
plt.legend()
plt.tight_layout()
plt.grid()
plt.show()
