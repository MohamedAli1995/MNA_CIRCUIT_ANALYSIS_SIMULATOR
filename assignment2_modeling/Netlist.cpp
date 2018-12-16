#include "Netlist.h"

void Netlist::addComponent(int type, int src, int dst, double value, double initialValue) {
	if (type == CAPACITOR) {
		this->hasActiveComponents = true;
		components.push_back(Component(CURRENT_SOURCE, src, dst, initialValue * (value / 0.1) , initialValue, (value / 0.1), true));
		components.push_back(Component(RESISTANCE, src, dst, (0.1 / value), 0));
		//std::cout << " capacitor value " << (value / 0.1) << std::endl;
	}
	else if (type == INDUCTOR) {
		this->hasActiveComponents = true;
		components.push_back(Component(VOLTAGE_SOURCE, src, dst, initialValue * (-value / 0.1), initialValue, (-value / 0.1), true, true));
		//components.push_back(Component(RESISTANCE, src, dst, (value / 0.1), 0));
		//std::cout << " Inductor value " << (-value / 0.1) << std::endl;

	}
	else{
	components.push_back(Component(type, src, dst, value, initialValue));
	}
}
int Netlist::getNodesCount() {
	int nodesCount = 0;
	for (Component comp : components) {
		nodesCount = std::max(nodesCount, comp.src);
		nodesCount = std::max(nodesCount, comp.dst);
	}
	return nodesCount;
}

int Netlist::getVoltageSourceCount() {
	int voltageSourceCount = 0;
	for (Component comp : components) {
		if (comp.type == VOLTAGE_SOURCE) {
			voltageSourceCount++;
		}
		
	}
	return voltageSourceCount;
}

void Netlist::parseFile(std::string fileName) {
	std::ifstream file;
	file.open(fileName);
	std::string compType;
	int dst, src;
	double value, initialValue;

	if (!file)
		std::cerr << "Cant open input file " << std::endl;
	while (file >> compType >> dst >> src >> value >> initialValue) {
		std::cout << " " << compType << " " << dst << " " << src << " " << value << " " << initialValue << std::endl;
		compType.erase(std::remove(compType.begin(), compType.end(), ' '),
			compType.end());
		
		int type;
		switch (compType[0]) {
		case'R':
			type = RESISTANCE;
			break;
		case 'V':
			type = VOLTAGE_SOURCE;
			break;
		case 'C':
			type = CAPACITOR;
			break;
		case 'I':
			if (compType.size() == 1) {
				type = INDUCTOR;
			}
			else {
				type = CURRENT_SOURCE;
			}
			break;
		default:
			std::cerr << "component: " << compType << " not defined in netlist components list" << std::endl;
			abort();
			break;

		}

		this->addComponent(type, src, dst, value, initialValue);
	}


}
Component::Component(int type, int src, int dst, double value, double initialValue, double constantPart,
	bool needEvaluation, bool generatedFromInductor){
	this->type = type;
	this->src = src;
	this->dst = dst;
	this->value = value;
	this->initialValue = initialValue;
	this->constantPart = constantPart;
	this->needEvaluation = needEvaluation;
	this->generatedFromInductor = generatedFromInductor;
}


