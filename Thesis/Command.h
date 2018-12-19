#pragma once
#include "OperationTypeEnum.h"
class Command
{
	/*
	POINT,
	LINE,
	SURFACE,
	CIRCLE,
	RECTANGLE,
	SHAPE,
	TRIANGLE,
	PYRAMID*/

public:
	std::vector <std::string> *CommandParameterVector=NULL;
	operationType::OperationTypeEnum operationType;
	float visibility = true;
	std::string name; 
	size_t typeOfParameters;
	//Enter only VALID command
	Command(std::string name,float visibility, operationType::OperationTypeEnum operationType,
		std::vector <std::string> *CommandParameterVector,
		size_t typeOfParameters) {
		this->CommandParameterVector = CommandParameterVector;
		this->operationType = operationType;
		this->visibility = visibility;
		this->name = name;
		this->typeOfParameters = typeOfParameters;
	}
	~Command() {
		//free commandParamsVector
		delete(CommandParameterVector);
	}
};
