#include <iostream>
#include "p1_simulation.h"
using namespace std;

int main(){
    double beta = 1.0;
    double sigma = 1.0;
    double gamma = 0.1;
    
    int n_steps = 1000;
    
    double dt = 0.1;
    double s0 = 0.99;
    double e0 = 0.01;
    double i0 = 0.0;
    double r0 = 0.0;

    P1_simulation model(beta, sigma, gamma, s0, e0, i0, r0, dt);
    for (int step = 1; step <= n_steps; step++) {

        model.euler_step();
        cout << model.t << ","
             << model.s << ","
             << model.e << ","
             << model.i << ","
             << model.r << "\n";
    }
    
    return 0;

}