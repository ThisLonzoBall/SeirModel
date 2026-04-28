#ifndef AGENT_H
#define AGENT_H

// represents the state of each agent/lattice site
const int Empty=0;
const int Susceptible=1;
const int Exposed=2;
const int Infected=3;
const int Recovered=4;

class Agent {
private:

    int x,y; // lattice coordinates
    int state; // current compartment

public:
    // constructor
    Agent();
    Agent(int x, int y, int state);

    void updatePosition(int new_x, int new_y); // updates agent's lattice coordinates after a move 
    void updateState(int new_state); // updates agents compartment after transition

    // getter functions
    int getState();
    int getX();
    int getY();

};

#endif // AGENT_H