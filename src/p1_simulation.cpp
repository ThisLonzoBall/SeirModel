#include "p1_simulation.h"

// constructor for the ODE simulation
P1_simulation::P1_simulation(double beta, double sigma, double gamma,
                             double s0, double e0, double i0, double r0, double dt)
    : beta(beta), sigma(sigma), gamma(gamma), dt(dt),
      s(s0), e(e0), i(i0), r(r0), t(0.0) {}

// carries out 1 step of Euler's method and updates the compartment sizes 
void P1_simulation::euler_step() {
    double ds = -beta * i * s;
    double de = beta * i * s - sigma * e;
    double di = sigma * e - gamma * i;
    double dr = gamma * i;

    s += ds * dt;
    e += de * dt;
    i += di * dt;
    r += dr * dt;

    t += dt;
}

// Runs Euler's Method for a given number of files and writes the current compartment sizes to the file
void P1_simulation::run(int n_steps, std::ofstream& outfile){
    outfile << t << "," << s << "," << e << "," << i << "," << r << "\n";
    for (int step = 1; step <= n_steps; step++) {
        euler_step();
        outfile << t << ","<< s << ","<< e << ","<< i << ","<< r << "\n";
    }

}

// Getter functions

double P1_simulation::gets(){
    return s;
}

double P1_simulation::gete(){
    return e;
}

double P1_simulation::geti(){
    return i;
}

double P1_simulation::getr(){
    return r;
}