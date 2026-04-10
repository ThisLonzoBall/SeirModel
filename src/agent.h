#ifndef AGENT_H
#define AGENT_H

const int Empty=0;
const int Susceptible=1;
const int Exposed=2;
const int Infected=3;
const int Recovered=4;

class Agent {
public:
    int x,y;
    int state;

    Agent();
    Agent(int x, int y, int state);

    void updatePosition(int new_x, int new_y);
    void updateState(int new_state);

};

#endif // AGENT_H