import pandas as pd 
import matplotlib.pyplot as plt
import numpy as np

from wrapper import P1_Wrapper, P2_Wrapper
from plotting import plot_p1, plot_p2, plot_snapshots


# default ODE case 
test_ODE = P1_Wrapper()
test_ODE.run()

df_test_ODE = pd.read_csv(test_ODE.filename())
plot_p1(df_test_ODE, "visualisations/test_ODE.png")


#default Monte Carlo Case
test_MC = P2_Wrapper()
test_MC.run()

df_test_MC = pd.read_csv(test_MC.filename())
plot_p2(df_test_MC, "visualisations/test_MC.png")

df_test_snapshot = pd.read_csv("results/snapshots.txt")
plot_snapshots(df_test_snapshot)

