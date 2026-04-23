#include "P2_simulation.h"
#include <iostream>
#include <random>
#include <algorithm>


P2_simulation::P2_simulation(int N, double beta, double sigma, double gamma, int L, int seed)
    : N(N), beta(beta), sigma(sigma), gamma(gamma), lattice(L),  rng(seed), uniform_dist(0.0, 1.0),
    S(0), E(0), I(0), R(0)
    {
    initAgents(); 

    S_arr.push_back(S);
    E_arr.push_back(E);
    I_arr.push_back(I);
    R_arr.push_back(R);
}

double P2_simulation::uniform() {
    return uniform_dist(rng);
}

int P2_simulation::randint(int min, int max){
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

void P2_simulation::tryMove(Agent& agent, int new_x, int new_y){
    lattice.moveAgent(agent.getX(), agent.getY(), new_x, new_y, agent.getState());
    agent.updatePosition(new_x, new_y);
}

 void P2_simulation::changeState(Agent& agent, int newstate){
    lattice.updateAgent(agent.getX(), agent.getY(), newstate);
    agent.updateState(newstate);
 }

 void P2_simulation::initAgents(){
    agents.resize(N);

    for(int k=0; k < N; k++){
        int x,y;
        
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

        agents[k] = Agent(x,y, state);
        lattice.updateAgent(x,y, state);
    }
}

void P2_simulation::step() {
    int directions[4][2] = {{1,0}, {-1,0}, {0,1}, {0, -1}};

    std:: shuffle(agents.begin(), agents.end(), rng);


    for(Agent& agent : agents){
        int dir = randint(0,3);

        int dx = directions[dir][0];
        int dy = directions[dir][1];

        int updated_x = (agent.getX() + dx + lattice.getL()) % lattice.getL();
        int updated_y = (agent.getY() + dy + lattice.getL()) % lattice.getL();

        if (lattice.isEmpty(updated_x, updated_y)) {
            tryMove(agent,updated_x ,updated_y);
        }

        if (agent.getState() == Exposed){
            if (uniform() < sigma){
                changeState(agent, Infected);
                I += 1; 
                E -= 1;
            }
        }
        else if (agent.getState() == Infected){
            if (uniform() < gamma){
                changeState(agent, Recovered);
                I -= 1;
                R += 1;
            }
        }
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

    }
}
void P2_simulation::saveSnapshot(std::ofstream& snapshotfile, int step){
        for (Agent& agent : agents){
            snapshotfile << step << "," << agent.getX() << ","<< agent.getY() << "," << agent.getState() <<"\n";
        }
}

void P2_simulation::run(int n_steps, std::ofstream& snapshotfile){
        for(int k=1; k <= n_steps; k++){
            step();
            S_arr.push_back(S);
            E_arr.push_back(E);
            I_arr.push_back(I);
            R_arr.push_back(R);
            if (k == 100 || k == 500 || k == 1000 || k== n_steps){
                saveSnapshot(snapshotfile,k);
            }
        }
}

void P2_simulation::saveResults(int n_steps, std::ofstream& outfile){
    for(int step=0; step <= n_steps; step++){
        outfile << step << ","
        << S_arr[step] << ","
        << E_arr[step] << ","
        << I_arr[step] << ","
        << R_arr[step] << "\n";
    }
}





