#ifndef LATTICE_H
#define LATTICE_H

#include <vector>

class Lattice{
public:
    int L;
    std::vector<std::vector<int>> grid;

    Lattice(int L);

    void moveAgent (int old_x, int old_y, int new_x, int new_y, int state);
    void updateAgent(int x, int y, int new_state);

};

#endif // LATTICE_H