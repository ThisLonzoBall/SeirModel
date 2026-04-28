#include "P2_simulation.h"
#include <iostream>
#include <random>
#include <algorithm>

// Constructor
// intializes and places agents on the lattice amd stores initial compartment count
P2_simulation::P2_simulation(int N, double beta, double sigma, double gamma, double reinfect, int L, int seed)
    : N(N), beta(beta), sigma(sigma), gamma(gamma),reinfect(reinfect), lattice(L), rng(seed), uniform_dist(0.0, 1.0),
    S(0), E(0), I(0), R(0)
    {
    initAgents(); 
    
    S_arr.push_back(S);
    E_arr.push_back(E);
    I_arr.push_back(I);
    R_arr.push_back(R);
}

// returns double in [0,1]
double P2_simulation::uniform() {
    return uniform_dist(rng);
}

// returns random integer in [min, max]
int P2_simulation::randint(int min, int max){
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

// moves agent from current position to new position on lattice
// updates both the lattice grid and the agent object with the new position
void P2_simulation::tryMove(Agent& agent, int new_x, int new_y){
    lattice.moveAgent(agent.getX(), agent.getY(), new_x, new_y, agent.getState());
    agent.updatePosition(new_x, new_y);
}

// updates agent compartment and corresponding lattice site
 void P2_simulation::changeState(Agent& agent, int newstate){
    lattice.updateAgent(agent.getX(), agent.getY(), newstate);
    agent.updateState(newstate);
 }

 // places N agents randomly at empty position on lattice with probability 0.95 in S and 0.05 in E
 void P2_simulation::initAgents(){
    agents.resize(N);

    for(int k=0; k < N; k++){
        int x,y;
        
        // finds empty lattice site
        do {
            x = randint(0, lattice.getL()-1);
            y = randint(0, lattice.getL()-1);
        } while(!lattice.isEmpty(x,y));

        int state = Susceptible;
        
        if (uniform() < 0.05) {
            state = Exposed;
        }

        if (state == Susceptible){
            S+=1;
        }
        else{
            E+=1;
        }

        agents[k] = Agent(x,y, state); // stores agent in vector
        lattice.updateAgent(x,y, state); // updates site on lattice grid with the compartment 
    }
}

// carries out one full MCS
// each agent attempts to randomly move and transitions state based on sigma, gamma and neighbours
void P2_simulation::step() {

    int directions[4][2] = {{1,0}, {-1,0}, {0,1}, {0, -1}}; // 4 possible directions agent can move

    // shuffle agents initially so agents move order isn't same each time
    std:: shuffle(agents.begin(), agents.end(), rng);

    
    for(Agent& agent : agents){ 
        int dir = randint(0,3); // picks random direction to move in

        int dx = directions[dir][0]; 
        int dy = directions[dir][1];

        int updated_x = (agent.getX() + dx + lattice.getL()) % lattice.getL(); // new X position
        int updated_y = (agent.getY() + dy + lattice.getL()) % lattice.getL(); // new Y position

        // move is only accepted if lattice site is empty
        if (lattice.isEmpty(updated_x, updated_y)) {
            tryMove(agent,updated_x ,updated_y);
        }

        // exposed agents transition to infected with probability sigma
        if (agent.getState() == Exposed){
            if (uniform() < sigma){
                changeState(agent, Infected); //updates state
                I += 1; 
                E -= 1;
            }
        }

        // infected agents transition to recovered with probability gamma
        else if (agent.getState() == Infected){
            if (uniform() < gamma){
                changeState(agent, Recovered); //updates state
                I -= 1;
                R += 1;
            }
        }

        // susceptible agents check infected neighbours and become exposed with probability beta for each infected neighbour
        else if (agent.getState()== Susceptible) {
            int infected_neighbours = lattice.countInfectedNeighbours(agent.getX() , agent.getY());

            for(int k=0; k < infected_neighbours; k++){
                if (uniform() < beta){
                    changeState(agent, Exposed);
                    S-=1;
                    E+=1;

                    break;
                }
            }

        }

        // COVID example where recovered agents transition to infected with small probability
         else if (agent.getState()== Recovered) {
            if (uniform() < reinfect){
            int infected_neighbours = lattice.countInfectedNeighbours(agent.getX() , agent.getY());
            for(int k=0; k < infected_neighbours; k++){
                if (uniform() < beta){
                    changeState(agent, Exposed); // updates state
                    R-= 1;
                    E+= 1;

                    break;
                }
            }

        }
    }

    }
}

// writes position and state of each agent to snashpot file
void P2_simulation::saveSnapshot(std::ofstream& snapshotfile, int step){
        for (Agent& agent : agents){
            snapshotfile << step << "," << agent.getX() << ","<< agent.getY() << "," << agent.getState() <<"\n";
        }
}

// runs Monte Carlo simulation for a given number of steps storing the compartment counts
void P2_simulation::run(int n_steps, std::ofstream& snapshotfile){
        for(int k=1; k <= n_steps; k++){
            step();
            S_arr.push_back(S);
            E_arr.push_back(E);
            I_arr.push_back(I);
            R_arr.push_back(R);
            // saves snapshots at fixed steps 100, 500, 1000, 2000
            if (k == 100 || k == 500 || k == 1000 || k== n_steps){
                saveSnapshot(snapshotfile,k);
            }
        }
}

// writes stored compartment counts for each MCS to output file at end of sim
void P2_simulation::saveResults(int n_steps, std::ofstream& outfile){
    for(int step=0; step <= n_steps; step++){
        outfile << step << ","
        << S_arr[step] << ","
        << E_arr[step] << ","
        << I_arr[step] << ","
        << R_arr[step] << "\n";
    }
}

// Getter functions

int P2_simulation::getS(){
    return S;
}
int P2_simulation::getE(){
    return E;
}
int P2_simulation::getI(){
    return I;
}
int P2_simulation::getR(){
    return R;
}

int P2_simulation::getN(){
    return N;
}


