#include "pch.h"
#include "TreeBuilder.h"


void TreeBuilder::Build(std::vector<Command*>* GraphCommand, std::vector<GeometricObject*>* Objects)
{
	/*std::vector <std::string> *CommandParameterVector = NULL;
	operationType::OperationTypeEnum operationType;
	float visibility = true;
	std::string name;
	size_t typeOfParameters;*/
	for (size_t i = 0; i < GraphCommand->size(); i++)
	{
		Objects->push_back(BuildObject(GraphCommand[i]));
	}
}

TreeBuilder::TreeBuilder()
{
}


TreeBuilder::~TreeBuilder()
{
}
