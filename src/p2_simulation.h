#ifndef P2_SIMULATION_H
#define P2_SIMULATION_H

#include <vector>
#include <random>
#include <fstream>

#include "agent.h"
#include "lattice.h"

class P2_simulation {
private:
    int N;
    double beta;
    double sigma;
    double gamma;
    double reinfect;

    Lattice lattice;
    std::vector<Agent> agents;

    std::mt19937 rng;
    std::uniform_real_distribution<double> uniform_dist;

    int S,E,I,R;

    std::vector<int> S_arr, E_arr, I_arr, R_arr;
    
    void initAgents();
    double uniform();
    int randint(int min, int max);
    void tryMove(Agent& agent, int new_x, int new_y);
    void changeState(Agent& agent, int new_state);

public: 

    P2_simulation(int N, double beta, double sigma, double gamma, double reinfect, int L, int seed);

    void saveSnapshot(std::ofstream& snapshotfile, int step);
    void saveResults(int n_steps, std::ofstream& outfile);
    void step();
    void run(int n_steps, std::ofstream& snapshotfile);

    int getS();
    int getE();
    int getI();
    int getR();
    int getN();

};

#endif // P2_SIMULATION_H