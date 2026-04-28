#include "lattice.h"
#include "agent.h"

// lattice Constructor
Lattice ::Lattice(int L):
    L(L), grid(L, std::vector<int>(L,0)) {}

// checks if grid is empty at position x,y
bool Lattice::isEmpty(int x, int y){
    if(grid[x][y]== 0){
        return true;
    }
    else{
        return false;
    }
}

// updates the lattice when an agent moves between sites
void Lattice::moveAgent(int old_x, int old_y, int new_x, int new_y, int state){
    grid[old_x][old_y] = Empty;
    grid[new_x][new_y] = state;
}

// updates the state of a site on the lattice grid
void Lattice::updateAgent(int x, int y,int new_state){
    grid[x][y] = new_state;
}

// checks adajacent sites to x and y to see if any number are infected and counts these
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

// getter function for L
int Lattice::getL(){
    return L;
}