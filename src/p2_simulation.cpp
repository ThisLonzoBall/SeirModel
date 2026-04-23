#include "P2_simulation.h"
#include <iostream>
#include <random>
#include <algorithm>


P2_simulation::P2_simulation(int N, double beta, double sigma, double gamma, int L, int seed)
    : N(N), beta(beta), sigma(sigma), gamma(gamma), lattice(L),  rng(seed), uniform_dist(0.0, 1.0),
    S(0), E(0), I(0), R(0)
    {
    initAgents(); 
}

double P2_simulation::uniform() {
    return uniform_dist(rng);
}

int P2_simulation::randint(int min, int max){
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

void P2_simulation::tryMove(Agent& agent, int new_x, int new_y){
    lattice.moveAgent(agent.x, agent.y, new_x, new_y, agent.state);
    agent.updatePosition(new_x, new_y);
}

 void P2_simulation::changeState(Agent& agent, int newstate){
    lattice.updateAgent(agent.x, agent.y, newstate);
    agent.updateState(newstate);
 }

 void P2_simulation::initAgents(){
    agents.resize(N);

    for(int k=0; k < N; k++){
        int x,y;
        
        do {
            x = randint(0, lattice.L-1);
            y = randint(0, lattice.L-1);
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

        int updated_x = (agent.x + dx + lattice.L) % lattice.L ;
        int updated_y = (agent.y + dy + lattice.L) % lattice.L ;

        if (lattice.isEmpty(updated_x, updated_y)) {
            tryMove(agent,updated_x ,updated_y);
        }

        if (agent.state == Exposed){
            if (uniform() < sigma){
                changeState(agent, Infected);
                I += 1; 
                E -= 1;
            }
        }
        else if (agent.state == Infected){
            if (uniform() < gamma){
                changeState(agent, Recovered);
                I -= 1;
                R += 1;
            }
        }
        else if (agent.state== Susceptible) {
            int infected_neighbours = lattice.countInfectedNeighbours(agent.x , agent.y);

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


