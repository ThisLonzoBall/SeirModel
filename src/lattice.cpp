#include "lattice.h"
#include "agent.h"

Lattice ::Lattice(int L):
    L(L), grid(L, std::vector<int>(L,0)) {}

void Lattice::moveAgent(int old_x, int old_y, int new_x, int new_y, int_state){
    grid[old_x][old_y] = Empty;
    grid[new_x][new_y] = state;
}

void Lattice::updateAgent(int x, int y,int new_state){
    grid[x][y] = new_state;
}