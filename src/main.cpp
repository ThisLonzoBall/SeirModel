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
    std::string filename1 = "results/p1_output.txt";
    std::ofstream outfile1(filename1);
    if (!outfile1){
        std::cerr << "Error opening file" <<filename1 << "\n";
        return 1;
    }
    outfile1 << "t,susceptible,exposed,infected,recovered\n";
    model.run(n_steps, outfile1);
    
    beta = 1.0;
    sigma = 0.1;
    gamma = 0.005;
    n_steps = 2000;

    int N = 250;
    int L = 100;
    int seed = 1234;

    P2_simulation model2(N , beta, sigma, gamma, L , seed);

    std::ofstream snapshotfile("results/snapshots.txt");
    if (!snapshotfile){
        std::cerr << "Error opening file\n";
        return 1;
    }
    snapshotfile <<"step,x,y,state\n";

    std::string filename2 = "results/p2_output.txt";
    std::ofstream outfile2(filename2);
    if (!outfile2){
        std::cerr << "Error opening file" <<filename2 << "\n";
        return 1;
    }
    
    outfile2 << "step,susceptible,exposed,infected,recovered\n";
    
    model2.run(n_steps, snapshotfile);
    model2.saveResults(n_steps, outfile2);

    return 0;

}