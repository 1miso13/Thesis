#pragma once
#include "OperationTypeEnum.h"
#include <vector>
#include <utility>
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
	std::vector <std::string> *OperationParametersVec=NULL;

	std::vector <std::pair<operationType::ParameterTypesEnum,void*>> *Parameters = new std::vector <std::pair<operationType::ParameterTypesEnum, void*>>();

	operationType::OperationTypeEnum operationType;
	float visibility = true;
	std::string name; 
	size_t typeOfParameters;
	//Enter only VALID command
	Operation(std::string name,float visibility, operationType::OperationTypeEnum operationType,
		std::vector <std::string> *OperationParametersVec,
		size_t typeOfParameters,
		std::vector<operationType::ParameterTypesEnum> *paramTypes) 
	{
		this->OperationParametersVec = OperationParametersVec;
		this->operationType = operationType;
		this->visibility = visibility;
		this->name = name;
		this->typeOfParameters = typeOfParameters; 
		SetParams(paramTypes);
	}
	~Operation() {
		//free commandParamsVector
		delete(OperationParametersVec);
		for (size_t i = 0; i < Parameters->size(); i++)
		{
			delete Parameters->at(i).second;
		}
		delete Parameters;
	}
private:
	void SetParams(std::vector<operationType::ParameterTypesEnum> *paramTypes);
};
