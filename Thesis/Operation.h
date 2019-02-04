#pragma once
#include "OperationTypeEnum.h"
#include <vector>
class Operation
{
	/*
	POINT,
	LINE,
	SURFACE,
	CIRCLE,
	RECTANGLE,
	Polygon,
	TRIANGLE,
	PYRAMID*/

public:
	std::vector <Operation*> * childs;
	std::vector <std::string> *OperationParametersVec=NULL;
	operationType::OperationTypeEnum operationType;
	float visibility = true;
	std::string name; 
	size_t typeOfParameters;
	//Enter only VALID command
	Operation(std::string name,float visibility, operationType::OperationTypeEnum operationType,
		std::vector <std::string> *OperationParametersVec,
		size_t typeOfParameters) {
		this->childs = new std::vector <Operation*>();
		this->OperationParametersVec = OperationParametersVec;
		this->operationType = operationType;
		this->visibility = visibility;
		this->name = name;
		this->typeOfParameters = typeOfParameters;
	}
	~Operation() {
		//free commandParamsVector
		delete(OperationParametersVec);
	}
};
