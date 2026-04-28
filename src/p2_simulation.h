#ifndef P2_SIMULATION_H
#define P2_SIMULATION_H

#include <vector>
#include <random>
#include <fstream>

#include "agent.h"
#include "lattice.h"

// class to carry out Monte Carlo simulation 
class P2_simulation {
private:
    int N; // number of agents 
    double beta;
    double sigma;
    double gamma;
    double reinfect; // reinfection probability

    Lattice lattice; // 2D lattice storing agent states
    std::vector<Agent> agents; // vector of all agent objects

    std::mt19937 rng; // randon number generator
    std::uniform_real_distribution<double> uniform_dist; //uniform distribution

    int S,E,I,R; // compartment counts

    std::vector<int> S_arr, E_arr, I_arr, R_arr; // stores compartment counts at each MCS
    
    void initAgents(); // intialises and places agents on lattices
    double uniform(); // returns double in [0,1]
    int randint(int min, int max); // returns random integer in [min, max]
    void tryMove(Agent& agent, int new_x, int new_y); // moves agent to a new lattice position: updating both agent and lattice
    void changeState(Agent& agent, int new_state); // updates agent compartment and lattice with new compartment

public: 
    // constructor
    P2_simulation(int N, double beta, double sigma, double gamma, double reinfect, int L, int seed);

    void saveSnapshot(std::ofstream& snapshotfile, int step); // writes agent positions and states to file at specific MCS
    void saveResults(int n_steps, std::ofstream& outfile); // writes compartment count to file
    void step(); // carries out one MCS
    void run(int n_steps, std::ofstream& snapshotfile); // runs Monte Carlo for n_steps

    // getter functions
    int getS();
    int getE();
    int getI();
    int getR();
    int getN();

};

#endif // P2_SIMULATION_H