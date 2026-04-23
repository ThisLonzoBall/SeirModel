# include "agent.h"

Agent::Agent():
    x(0), y(0), state(Empty) {}

Agent ::Agent(int x, int y, int state):
    x(x), y(y), state(state) {}

void Agent::updateState(int new_state) {
    state = new_state;
}

void Agent::updatePosition(int new_x, int new_y){
    x = new_x;
    y = new_y;
}

int Agent::getState(){
    return state;
}

int Agent::getX(){
    return x;
}

int Agent::getY(){
    return y;    
}