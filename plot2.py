import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results/p2_output.txt")

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
plt.show()
