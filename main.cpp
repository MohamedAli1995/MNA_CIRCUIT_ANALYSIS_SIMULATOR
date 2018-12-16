#include <iostream>
#include "Simulator.h"

using namespace std;

int main() {
    string netlistFile = "input.txt";
    Simulator sim(netlistFile);
    sim.initializeModelParameters();
    sim.simulate(20);
    sim.logResult("output.txt");

    return 0;
}
