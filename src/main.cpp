#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "p1_simulation.h"
#include "p2_simulation.h"

using namespace std;

int main(int argc, char* argv[]){
    if (argc <2){
        std::cerr << "Usage:" << argv[0] << "P1 or P2\n";
        return 1;
    }

    std::string mode = argv[1];

    if (mode == "P1"){
        if(argc < 6){
            std::cerr <<"Usage:" << argv[0]  
                << "P1 <beta> <sigma> <gamma> [n_steps] [s0] [e0] [i0] [r0]\n";
            return 1;  
        }

        double beta = std::stod(argv[2]);
        double sigma = std::stod(argv[3]);
        double gamma = std::stod(argv[4]);
        
        int n_steps = (argc >= 6) ? std::stoi(argv[5]) : 1000;
        double s0 = (argc >= 7) ? std::stod(argv[6]) : 0.99;
        double e0 = (argc >= 8) ? std::stod(argv[7]) : 0.01;
        double i0 = (argc >= 9) ? std::stod(argv[8]) : 0.0;
        double r0 = (argc >= 10) ? std::stod(argv[9]) : 0.0;

        double tmax = 100.0;
        double dt = tmax/ n_steps;

        P1_simulation model1(beta, sigma, gamma, s0, e0, i0, r0, dt);

        system("mkdir -p results");

        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2);
        stream << "results/p1_beta"<< beta << "_sigma" << sigma << "_gamma" <<gamma
        << ".txt";

        std::string filename = stream.str();

        std::ofstream outfile_p1(filename);
        if (!outfile_p1){
            std::cerr << "Error opening file" <<filename << "\n";
            return 1;
        }
        
        outfile_p1 << "t,susceptible,exposed,infected,recovered\n";
        model1.run(n_steps, outfile_p1);

        outfile_p1.close();
    }
    else if (mode=="P2"){
        if(argc < 5){
            std::cerr<<"Usage "<< argv[0] << "P2 <beta> <sigma> <gamma> <N> [seed]\n";
            return 1;
        }

        double beta = std::stod(argv[2]);
        double sigma = std::stod(argv[3]);
        double gamma = std::stod(argv[4]);
        int N = std::stoi(argv[5]);

        int seed = (argc >= 7) ? std::stoi(argv[6]) : 1234;

        int L = 100;
        int n_steps = 2000;

        P2_simulation model2(N, beta, sigma, gamma, L ,seed);

        system("mkdir -p results");

        std::ofstream snapshotfile("results/snapshots.txt");
        if (!snapshotfile){
            std::cerr << "Error opening file\n";
            return 1;
        }
        snapshotfile <<"step,x,y,state\n";

        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2);
        stream << "results/p2_beta"<< beta << "_sigma" << sigma << "_gamma" <<gamma <<"_N" << N
        << ".txt";

        std::string filename = stream.str();

        std::ofstream outfile_p2(filename);
        if (!outfile_p2){
            std::cerr << "Error opening file" <<filename << "\n";
            return 1;
        }
        
        outfile_p2 << "step,susceptible,exposed,infected,recovered\n";
        
        model2.run(n_steps, snapshotfile);
        model2.saveResults(n_steps, outfile_p2);

        snapshotfile.close();
        outfile_p2.close();
    }

    else {
        std::cerr << "Incorrect Mode" << mode << " use P1 or P2\n";
        return 1;
    }


    return 0;

}