import os 
import sys
import matplotlib.pyplot as plt
import pandas as pd

output_dir = "visualisations"
os.makedirs(output_dir, exist_ok=True)

def load(path):
    return pd.read_csv(path)

def plot_p1(df, output_file):
    fig, ax = plt.subplots(figsize=(10,8))
    ax.plot(df["t"],df["susceptible"] , label='Susceptible')
    ax.plot(df["t"], df["exposed"], label='Exposed')
    ax.plot(df["t"], df["infected"], label='Infected')
    ax.plot(df["t"], df["recovered"], label='Recovered')


    ax.set_xlabel('Time (days)')
    ax.set_ylabel('Population Fraction')
    ax.set_title('ODE SEIR Simulation')
    ax.legend(loc="upper right")
    ax.grid()
    
    fig.savefig(output_file)
    plt.close()
    return fig 

def plot_p2(df, output_file):
    fig, ax = plt.subplots(figsize=(10,8))
    ax.plot(df["step"], df["susceptible"], label="Susceptible")
    ax.plot(df["step"], df["exposed"], label="Exposed")
    ax.plot(df["step"], df["infected"], label="Infected")
    ax.plot(df["step"], df["recovered"], label="Recovered")

    ax.set_xlabel("Monte Carlo Step")
    ax.set_ylabel("Population")
    ax.set_title(f"Monte Carlo SEIR Simulation")
    ax.legend(loc="upper right")
    ax.grid()

    fig.savefig(output_file)
    plt.close()
    return fig 

def plot_snapshots(df):
    for step in df["step"].unique():
        step_df= df[df["step"] == step]

        susceptible = step_df[step_df["state"] == 1]
        exposed = step_df[step_df["state"] == 2]
        infected = step_df[step_df["state"] == 3]
        recovered = step_df[step_df["state"] == 4]

        fig, ax = plt.subplots(figsize=(10,8))
        ax.scatter(susceptible["x"], susceptible["y"], color= "blue", label= "Susceptible", s=20)
        ax.scatter(exposed["x"], exposed["y"], color= "orange", label= "Exposed", s=20)
        ax.scatter(infected["x"], infected["y"], color= "green", label= "Infected", s=20)
        ax.scatter(recovered["x"], recovered["y"], color= "red", label= "Recovered", s=20)

        ax.set_xlabel("x position")
        ax.set_ylabel("y position")

        ax.set_title(f"Monte Carlo SEIR Simulation (step {int(step)})")
        ax.legend(loc = "upper right")
    
        fig.savefig(os.path.join(output_dir,f"snapshot_{int(step)}.png"))
        plt.close()

    
if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: python3 plot.py <mode> <filepath>")
        sys.exit(1)
    
    mode = sys.argv[1]
    filepath = sys.argv[2]

    if mode == "P1":
        plot_p1(load(filepath), os.path.join(output_dir, os.path.basename(filepath).replace(".txt", ".png")))
    elif mode == "P2":
        plot_p2(load(filepath), os.path.join(output_dir, os.path.basename(filepath).replace(".txt", ".png")))
    elif mode == "snapshots":
        plot_snapshots(load(filepath))
    else:
        print("Incorrect Input")
        sys.exit(1)


