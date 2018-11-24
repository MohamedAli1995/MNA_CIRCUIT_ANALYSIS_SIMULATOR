// assignment2_modeling.cpp : Defines the entry point for the application.
//

#include "assignment2_modeling.h"
#include "Simulator.h"
using namespace std;

int main()
{
	string netlistFile = "input.txt";
	Simulator sim(netlistFile);
	sim.initializeModelParameters();
	sim.simulate(20);

	system("pause");
	return 0;
}
