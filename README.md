# Mini Project

## Overview

This project simulates the SEIR transition model using both ODEs and a Monte Carlo Simulation.


## Project Structure


```
SEIRMODEL/
├── src/
|    ├── main.cpp - Runs simulation and saves results in output file
|    ├── P1_simulation.cpp - Implementation of P1_simulation class
|    ├── P1_simulation.h- Header file for the class used to run the ODE simulation
|    ├── agent.cpp - Implementation of agent class
|    ├── agent.h - Header file for the agent class representing each individual agent
|    ├── lattice.cpp - Implementation of lattice class
|    ├── lattice.h - Header file for the class used to represent the 2D lattice in simulation
|    ├── P2_simulation.cpp - Implementation of P2_simulation class
|    └── P2_simulation.h - Header file for the class used to run and save the results from the Monte Carlo simulation
├── wrapper.py - wrapping ODE and Monte Carlo simulation in Python using subprocess module and contains a class for P1 and P2
├── plotting.py - provides plotting functions to plot output files from running simulation.
├── test_cases.py - runs the simulation for default parameter cases in the brief
├── analysis.ipynb - notebook used for analysis in the results section
├── README.md - This file (outlines of project)
├── Makefile -  Automated script for compilations
└── .gitignore -  Files we want to ignore in our git repository
```
---
## Compilation

The project is compiled using provided Makefile

To compile run in terminal:

```
make            # compiles all source files and produces seir_sim
make clean      # removes executable, object files, results/ and visualisations/
make test       # compiles and runs all test in testing.cpp
```


## Running Simulation


### ODE (part 1) 
```
./seir_sim  P1 <beta> <sigma> <gamma> <n_steps> [s0] [e0] [i0] [r0]
```
- `beta`, `sigma` , `gamma` - required SEIR rates
- `n_steps` - number of Euler steps 
- `s0`, `e0`, `i0` , `r0` - optional parameters that represent the initial compartments proportions (default: 0.99, 0.01, 0.0, 0.0)

### Monte Carlo Simulation (part 2) 

```
./seir_sim  P2 <beta> <sigma> <gamma> <N> [reinfect] [seed]
```
- `beta`, `sigma` , `gamma` - required SEIR rates
- `N` - number of agents on lattice
- `reinfect` - optional reinfection probability for recovered (default : 0.0)
- `seed` - optional random seed (default: 1234)

## Output 

### Part 1
```
results/p1_beta{beta}_sigma{sigma}_gamma{gamma}.txt
```
Contains time against s,e,i,r fractions for the ODE simulation

### Part 2

```
results/p2_beta{beta}_sigma{sigma}_gamma{gamma}_N{N}.txt
```
Contains MCS against S,E,I,R for the Monte Carlo simulation


```
results/snapshots.txt
```
Contains the x,y coordinates and state of each agent, recorded at MCS 100, 500, 1000, 2000.

## Visualisation

Plotting.py can be used to visualise outputs.

This can be run easily in the terminal using:

### Part 1
```
python3 plotting.py P1 results/p1_beta{beta}_sigma{sigma}_gamma{gamma}.txt
```

### Part 2 
```
python3 plotting.py P2 results/p2_beta{beta}_sigma{sigma}_gamma{gamma}_N{N}.txt
```

### Snapshots
```
python3 plotting.py snapshots results/snapshots.txt
```
all plots are saved to `visualisations/`

## Git navigation:

Download and clone bundle using:
```
git clone 2373720.bundle
```

Then you will be able to see all the branches and commits of the bundle.

Branches:
- `master`: main branch, all feature branches merged here
- `P1`: ODE simulation implementation
- `P2`: Monte Carlo simulation implementation
- `encapsulation`: adding private and public to all classes
- `CLI arguments`: command line argument parsing and input validation
- `testing`: unit tests in testing.cpp


```
git checkout <branch>       # switch to a branch
git checkout master          # return to main branch
```
