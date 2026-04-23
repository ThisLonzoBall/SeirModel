#include "lattice.h"
#include "agent.h"

Lattice ::Lattice(int L):
    L(L), grid(L, std::vector<int>(L,0)) {}

bool Lattice::isEmpty(int x, int y){
    if(grid[x][y]== 0){
        return true;
    }
    else{
        return false;
    }
}

void Lattice::moveAgent(int old_x, int old_y, int new_x, int new_y, int state){
    grid[old_x][old_y] = Empty;
    grid[new_x][new_y] = state;
}

void Lattice::updateAgent(int x, int y,int new_state){
    grid[x][y] = new_state;
}

int Lattice::countInfectedNeighbours(int x, int y){
    int directions[4][2] = {{1,0}, {-1,0}, {0,1}, {0, -1}};
    int count = 0;
    for(int d=0; d < 4; ++d) {
        int new_x= ((x + directions[d][0]) + L) % L;
        int new_y= ((y + directions[d][1]) + L) % L;
        if (grid[new_x][new_y] == Infected) {
            count += 1;
        }

    }
    return count;
}