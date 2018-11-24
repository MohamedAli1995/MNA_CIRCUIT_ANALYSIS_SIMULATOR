#include <vector>
#include<algorithm>
#include<string>
#include<fstream>
#include<iostream>

#define RESISTANCE 0
#define VOLTAGE_SOURCE 1
#define CURRENT_SOURCE 2
#define CAPACITOR 3
#define INDUCTOR 4


struct Component {
	int type;
	int src = 0;
	int dst = 0;
	bool generatedFromInductor = false;
	bool needEvaluation = false;
	double value = 0;
	double initialValue = 0;
	double constantPart = 0;
	Component(int type, int src, int dst, double value, double initialValue, double constantPart=0,
		bool needEvaluation=false, bool generatedFromInductor=false);
};
class Netlist {
public:
	std::vector<Component> components;
	void addComponent(int type, int src, int dst, double value, double InitialValue);
	
	int getNodesCount();

	int getVoltageSourceCount();

	void parseFile(std::string fileName);

};