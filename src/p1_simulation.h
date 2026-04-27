#ifndef P1_SIMULATION_H
#define P1_SIMULATION_H

#include <fstream>

class P1_simulation {

private:

    double beta, sigma, gamma;
    double dt;
    double s,e, i, r;
    double t;

public:
    P1_simulation(double beta, double sigma, double gamma, 
                double s0, double e0, double i0, double r0, double dt);
    
    void euler_step();
    void run(int n_steps, std::ofstream& outfile);

    double gets();
    double gete();
    double geti();
    double getr();
};

#endif // P1_SIMULATION_H