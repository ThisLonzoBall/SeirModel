#ifndef P1_SIMULATION_H
#define P1_SIMULATION_H

#include <fstream>


class P1_simulation {

private:

    double beta, sigma, gamma; // rates 
    double dt; // time step 
    double s,e, i, r; // compartment proportions
    double t; // total time passed

public:
    // constructor
    P1_simulation(double beta, double sigma, double gamma, 
                double s0, double e0, double i0, double r0, double dt);
    
    void euler_step(); // carries out 1 step Euler Method
    void run(int n_steps, std::ofstream& outfile); // runs Euler Method and writes values to file
    
    // getter functions
    double gets();
    double gete();
    double geti();
    double getr();
};

#endif // P1_SIMULATION_H