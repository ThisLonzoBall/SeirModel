# include "agent.h"

// default constructor when agent position set in Empty state
Agent::Agent():
    x(0), y(0), state(Empty) {}

// constructor
Agent ::Agent(int x, int y, int state):
    x(x), y(y), state(state) {}

// updates agent compartment after transitions
void Agent::updateState(int new_state) {
    state = new_state;
}

// updates agent position after move
void Agent::updatePosition(int new_x, int new_y){
    x = new_x;
    y = new_y;
}

// getter functions 

int Agent::getState(){
    return state;
}

int Agent::getX(){
    return x;
}

int Agent::getY(){
    return y;    
}