#ifndef LATTICE_H
#define LATTICE_H

#include <vector>

class Lattice{
public:
    int L;
    std::vector<std::vector<int>> grid;

    Lattice(int L);

    bool isEmpty(int x, int y);

    void moveAgent (int old_x, int old_y, int new_x, int new_y, int state);
    void updateAgent(int x, int y, int new_state);

    int countInfectedNeighbours(int x , int y);

};

#endif // LATTICE_H