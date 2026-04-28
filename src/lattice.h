#ifndef LATTICE_H
#define LATTICE_H

#include <vector>

// Lattice class
class Lattice{
private:
    int L; // width of lattice grid
    std::vector<std::vector<int>> grid; // grid to store states of agents at positions

public:
    Lattice(int L); // constructor

    bool isEmpty(int x, int y); // checks whether site on grid is empty

    void moveAgent (int old_x, int old_y, int new_x, int new_y, int state); // updates position of agent on grid
    void updateAgent(int x, int y, int new_state); // updates state stored at x,y on grid

    int countInfectedNeighbours(int x , int y); // checks adjacent sites to give infected neighbour count

    int getL(); //getter function
};

#endif // LATTICE_H