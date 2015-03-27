#include "Node.h"
#include "Circuit.h"

Node::Node()
{
	resultValue = 0;
	valueSet = false;
}

Node::Node(string name, Circuit* circuit)
{
	this->name = name;
	this->circuit = circuit;
	resultValue = 0;
	valueSet = false;
}

void Node::setNodeType(string nodeType)
{
	this->type = nodeType;
}

void Node::addOutput(EdgePointer edge)
{
	outputs.push_back(edge);
}

void Node::addInput(EdgePointer edge)
{
	inputs.push_back(edge);
}

void Node::assignTask(const string& typeOfNode, const string& portsDescription)
{
	this->setNodeType(typeOfNode);
	regex pattern("\\.([A-Z]+)\\((.+?)\\),[^]+?\\.([A-Z]+)\\((.+?)\\)(?:,[^]+?\\.([A-Z]+)\\((.+?)\\))?(?:,[^]+?\\.([A-Z]+)\\((.+)\\))?(?:,[^]+?\\.([A-Z]+)\\((.+?)\\))?");
	smatch match;
	if (regex_search(portsDescription, match, pattern)){
		for (int i = 1; i < 10; i += 2){
			const string& Q = match[i].str();
			const string& W = match[i + 1].str();
			if (match[i].length() && match[i + 1].length()){
				if (match[i] == "Q" || match[i] == "Y"){
					addOutput(EdgePointer(circuit->edges.find(match[i + 1])));
					circuit->edges[match[i + 1]].setSourceNode(circuit->nodeIndex[name]);
				}
				else{
					addInput(EdgePointer(circuit->edges.find(match[i + 1])));
					circuit->edges[match[i + 1]].addDestinationNode(circuit->nodeIndex[name]);
				}
			}
		}
	}
}

std::string Node::getName() const
{
	return name;
}

std::string Node::getType() const
{
	return type;
}


bool Node::isInputPort() const
{
	return (type == "INPUT_PORT");
}

bool Node::isOutputPort() const
{
	return (type == "OUTPUT_PORT");
}

bool Node::getValue() const
{
	return resultValue;
}

void Node::setValue(bool resultValue)
{
	this->resultValue = resultValue;
	valueSet = true;
}

bool Node::isValueSet() const
{
	return valueSet;
}

