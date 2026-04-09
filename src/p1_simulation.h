#ifndef P1_SIMULATION_H
#define P1_SIMULATION_H

class P1_simulation {
public:
    
    double beta, sigma, gamma;
    double dt;
    double s,e, i, r;
    double t;

    P1_simulation(double beta, double sigma, double gamma, 
                double s0, double e0, double i0, double r0, double dt);
    
    void euler_step();
};

#endif // P1_SIMULATION_H