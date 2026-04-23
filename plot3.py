import pandas as pd 
import matplotlib.pyplot as plt

df = pd.read_csv("results/snapshots.txt")

for step in df["step"].unique():
    step_data = df[df["step"] == step]

    susceptible = step_data[step_data["state"] == 1]
    exposed = step_data[step_data["state"] == 2]
    infected = step_data[step_data["state"] == 3]
    recovered = step_data[step_data["state"] == 4]

    plt.figure(figsize=(8,8))
    plt.scatter(susceptible["x"], susceptible["y"], color= "blue", label= "Susceptible", s=20)
    plt.scatter(exposed["x"], exposed["y"], color= "orange", label= "Exposed", s=20)
    plt.scatter(infected["x"], infected["y"], color= "green", label= "Infected", s=20)
    plt.scatter(recovered["x"], recovered["y"], color= "red", label= "Recovered", s=20)

    plt.xlabel("x position")
    plt.ylabel("y position")

    plt.title(f"Monte Carlo SEIR Simulation (step {step})")
    plt.legend()
    plt.savefig(f"results/snapshot{step}.png", dpi=100)
    plt.close()
    