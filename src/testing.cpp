#include <iostream>
#include <string>
#include <cmath>

#include "agent.h"
#include "lattice.h"
#include "p1_simulation.h"
#include "p2_simulation.h"

int tests_passed= 0;
int tests_failed = 0;

void report(bool passed, const std::string& name){
    if (passed) {
        tests_passed += 1;
        std::cout << "Pass" << name << "\n";
    }
    else{
        tests_failed += 1;
        std::cout << "Fail" << name << "\n";
    }

}

void testAgentUpdates(){
    Agent agent(0,0, Susceptible);
    agent.updatePosition(6,7);
    agent.updateState(Infected);

    if(agent.getX() == 6 && agent.getY() == 7 && agent.getState() == Infected){
        report(true, "Agent position and state update correctly");
    }
    else{
        report(false, "Agent position and state do not update correctly");
    }
}

void testLatticeMoveAgent(){
    Lattice lattice(10);
    
    lattice.updateAgent(1,2, Susceptible);
    lattice.moveAgent(1,2,3,4, Susceptible);

    if(lattice.isEmpty(1,2) && !lattice.isEmpty(3,4)){
        report(true, "Lattice updates sites correctly");
    }
    else{
        report(false, "Lattice does not update sites correctly");       
    }

}

void testLatticeCountInfectedNeighbours(){
    Lattice lattice(10);

    lattice.updateAgent(2,2, Susceptible);
    lattice.updateAgent(2,1, Infected);
    lattice.updateAgent(1,2, Infected);

    if(lattice.countInfectedNeighbours(2,2) ==2){
        report(true, "Lattice counts infected neighbours correctly");    
    }
    else{
        report(false, "Lattice does not count infected neighbours correctly"); 
    }
}

void testLatticeBoundary(){
    Lattice lattice(10);

    lattice.updateAgent(0,0, Infected);

    if(lattice.countInfectedNeighbours(9,0) == 1){
        report(true, "Lattice boundary works correctly");    
    }
    else{
        report(false, "Lattice boundary does not work correctly");    
    }
}

void testP1Compartments(){
    P1_simulation sim(1.0, 1.0, 0.1, 0.99, 0.01, 0.0, 0.0, 0.1);

    bool pass = true;
    for (int i = 0; i < 1000; i++){
        sim.euler_step();
        double total = sim.gets() + sim.gete() + sim.geti() + sim.getr();

        if (std::abs(total - 1.0) > 1e-6){
            pass = false;
        }
    }
    if(pass == true){
        report(true, "Compartments sum to 1 in ODE");
    }
    else{
        report(false, "Compartments do not sum to 1 in ODE");
    }
}


void testP2Compartments(){
    P2_simulation sim(250,1.0, 0.1, 0.005, 0.0, 100, 42);

    bool pass = true;
    for (int i = 0; i < 2000; i++){
        sim.step();
        int total = sim.getS() + sim.getE() + sim.getI() + sim.getR();

        if (total != sim.getN()){
            pass = false;
        }
    }
    if(pass == true){
        report(true, "Compartments sum to N in MCS");
    }
    else{
        report(false, "Compartments do not sum to N in MCS");
    }
}

int main() {
    std::cout << "SEIR Simulation Tests\n";

    testAgentUpdates();
    testLatticeMoveAgent();
    testLatticeBoundary();
    testLatticeCountInfectedNeighbours();
    testP1Compartments();
    testP2Compartments();

    std:: cout << "Passed:"<< tests_passed << "Failed:" << tests_failed << "\n";

}