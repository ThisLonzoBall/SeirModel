#ifndef LATTICE_H
#define LATTICE_H

#include <vector>

class Lattice{
private:
    int L;
    std::vector<std::vector<int>> grid;

public:
    Lattice(int L);

    bool isEmpty(int x, int y);

    void moveAgent (int old_x, int old_y, int new_x, int new_y, int state);
    void updateAgent(int x, int y, int new_state);

    int countInfectedNeighbours(int x , int y);

    int getL();

};

#endif // LATTICE_H