#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "p1_simulation.h"
#include "p2_simulation.h"

using namespace std;

int main(int argc, char* argv[]){
    // first argument mode that needs to be run ODE (P1) or Monte Carlo (P2)
    if (argc <2){
        std::cerr << "Usage:" << argv[0] << "P1 or P2\n";
        return 1;
    }

    // mode input
    std::string mode = argv[1];

    // ODE simulation
    if (mode == "P1"){
        // checks usage is correct
        if(argc < 5){
            std::cerr <<"Usage:" << argv[0]  
                << "P1 <beta> <sigma> <gamma> [n_steps] [s0] [e0] [i0] [r0]\n";
            return 1;  
        }

        // CLI arguments for beta, sigma , gamma
        double beta = std::stod(argv[2]);
        double sigma = std::stod(argv[3]);
        double gamma = std::stod(argv[4]);
        
        // optional parameters are n_steps and s0, e0, i0, r0
        int n_steps = (argc >= 6) ? std::stoi(argv[5]) : 1000; // n_steps defults to 100
        double s0 = (argc >= 7) ? std::stod(argv[6]) : 0.99; // s0 defults to 0.99
        double e0 = (argc >= 8) ? std::stod(argv[7]) : 0.01; // e0 defaults to 0.01
        double i0 = (argc >= 9) ? std::stod(argv[8]) : 0.0; // i0 defaults to 0.0
        double r0 = (argc >= 10) ? std::stod(argv[9]) : 0.0; // r0 defaults to 0.0

        // checks whethter inputs are valid
        if (beta < 0.0){
            std::cerr << "Beta must be >=0\n";
            return 1;
        }
        if (sigma < 0.0){
            std::cerr << "Sigma must be >=0\n";
            return 1;
        }
        if (gamma < 0.0){
            std::cerr << "Gamma must be >=0\n";
            return 1;
        }
        if (n_steps < 1 || n_steps > 1e7){
            std::cerr << "n_steps must be between 1 and 1e7\n";
            return 1;
        }
        if (s0 < 0){
            std::cerr << "s0 must be >=0 \n";
            return 1;
        }
        if (e0 < 0){
            std::cerr << "e0 must be >=0 \n";
            return 1;
        }
        if (i0 < 0){
            std::cerr << "i0 must be >=0 \n";
            return 1;
        }
        if (r0 < 0){
            std::cerr << "r0 must be >=0 \n";
            return 1;
        }
        if (s0 + e0 + i0 + r0 > 1.0 + 1e-8){
            std::cerr << "Initial proportions must sum to 1 \n";
            return 1;
        }

        double tmax = 100.0; // time step to 100 days
        double dt = tmax/ n_steps; // determines dt based on number of steps

        // creates results directory
        system("mkdir -p results");

        // construct output file name from parameters
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

        P1_simulation model1(beta, sigma, gamma, s0, e0, i0, r0, dt); // instantiates simulation object for given parameters

        
        // runs simulation
        model1.run(n_steps, outfile_p1);

        outfile_p1.close();

        std::cout << "ODE simulation complete. Results written to "<<filename<< "\n";
    }

    // Monte Carlo simulation
    else if (mode=="P2"){
        // checks usage is correct
        if(argc < 5){
            std::cerr<<"Usage "<< argv[0] << "P2 <beta> <sigma> <gamma> <N> [seed]\n";
            return 1;
        }

        // required CLI arguments
        double beta = std::stod(argv[2]);
        double sigma = std::stod(argv[3]);
        double gamma = std::stod(argv[4]);
        int N = std::stoi(argv[5]);

        // optional parameters reinfection probability and seed
        double reinfect = (argc >= 7) ? std::stod(argv[6]) : 0.0; // defaults to 0
        int seed = (argc >= 8) ? std::stoi(argv[7]) : 1234; // defaults to 1234

        int L = 100; // fixed lattice size 
        int n_steps = 2000; // fixed number of MCS

        // input validation
        if (beta < 0.0 || beta > 1.0){
            std::cerr << "Beta must be between 0 and 1\n";
            return 1;
        }
        if (sigma < 0.0 || sigma > 1.0){
            std::cerr << "Sigma must be between 0 and 1\n";
            return 1;
        }
        if (gamma < 0.0 || gamma > 1.0){
            std::cerr << "Gamma must be between 0 and 1\n";
            return 1;
        }
        if (N < 1){
            std::cerr << "N must be >=1\n";
            return 1;
        }
        if (N > L*L){
            std::cerr << "N must be <= L squared\n";
            return 1;
        }



        // creates results directory
        system("mkdir -p results");

        // opens snapshot files
        std::ofstream snapshotfile("results/snapshots.txt");
        if (!snapshotfile){
            std::cerr << "Error opening file\n";
            return 1;
        }
        snapshotfile <<"step,x,y,state\n";

        // construct output file name from parameters
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(3);
        stream << "results/p2_beta"<< beta << "_sigma" << sigma << "_gamma" <<gamma <<"_N" << N
        << ".txt";
        std::string filename = stream.str();

        std::ofstream outfile_p2(filename);
        if (!outfile_p2){
            std::cerr << "Error opening file" <<filename << "\n";
            return 1;
        }
        
        outfile_p2 << "step,susceptible,exposed,infected,recovered\n";

        P2_simulation model2(N, beta, sigma, gamma, reinfect, L ,seed); // instantiate Monte Carlo simulation object

        // run simulation and write the results
        model2.run(n_steps, snapshotfile);
        model2.saveResults(n_steps, outfile_p2);

        snapshotfile.close();
        outfile_p2.close();

        std::cout << "Monte Carlo simulation complete. Results written to "<<filename<< ".Snapshots written to results/snapshots.txt\n";
    }

    else {
        std::cerr << "Incorrect Mode" << mode << " use P1 or P2\n";
        return 1;
    }


    return 0;

}