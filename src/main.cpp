#include <iostream>
#include <fstream>
#include "p1_simulation.h"
#include "p2_simulation.h"

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

    system("mkdir -p results");
    std::string filename = "results/p1_output.txt";
    std::ofstream outfile(filename);
    if (!outfile){
        std::cerr << "Error opening file" <<filename << "\n";
        return 1;
    }
    outfile << "t,susceptible,exposed,infected,recovered\n";
    
    outfile << model.t << "," << model.s << "," << model.e << ","
             << model.i << "," << model.r << "\n";

    for (int step = 1; step <= n_steps; step++) {

        model.euler_step();
        outfile << model.t << ","
             << model.s << ","
             << model.e << ","
             << model.i << ","
             << model.r << "\n";
    }

    beta = 1.0;
    sigma = 0.1;
    gamma = 0.005;
    n_steps = 2000;

    int N = 250;
    int L = 100;
    int seed = 1234;

    P2_simulation model2(N , beta, sigma, gamma, L , seed);

    system("mkdir -p results");
    std::string filename2 = "results/p2_output.txt";
    std::ofstream outfile2(filename2);
    if (!outfile2){
        std::cerr << "Error opening file" <<filename2 << "\n";
        return 1;
    }
    outfile2 << "step,susceptible,exposed,infected,recovered\n";
    
    outfile2 << 0 << "," << model2.S << "," << model2.E << ","
             << model2.I << "," << model2.R << "\n";

    for (int step = 1; step <= n_steps; step++) {

        model2.step();
        outfile2 << step << ","
             << model2.S << ","
             << model2.E << ","
             << model2.I << ","
             << model2.R<< "\n";
    }

    return 0;

}