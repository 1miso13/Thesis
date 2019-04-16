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
	unsigned char color[4] = {0,0,0,0};
	std::string getColorHEX() {
		std::string s = "";
		for (size_t i = 0; i < 4; i++)
		{
			unsigned char a[] = { (unsigned char)(color[i] / 16), (unsigned char)(color[i] % 16) };
			for (size_t j = 0; j < 2; j++)
			{
				if (a[j] <= 9)
				{
					a[j] += '0';
				}
				else//10-15 = A-F
				{
					a[j] += 'A' - 10;
				}
				s += a[j];
			}
		}
		return s;
	}
	std::string name; 
	size_t typeOfParameters;
	//Enter only VALID command
	Operation(std::string name, unsigned char color[4], operationType::OperationTypeEnum operationType,
		std::vector <std::string> *OperationParametersVec,
		size_t typeOfParameters,
		std::vector<operationType::ParameterTypesEnum> *paramTypes) 
	{
		this->OperationParametersVec = OperationParametersVec;
		this->operationType = operationType;
		this->color[0] = color[0];
		this->color[1] = color[1];
		this->color[2] = color[2];
		this->color[3] = color[3];
		this->name = name;
		this->typeOfParameters = typeOfParameters; 
		SetParams(paramTypes);
	}
	~Operation() {
		//free commandParamsVector
		if (OperationParametersVec!=NULL)
			delete(OperationParametersVec);
		for (size_t i = 0; i < Parameters->size(); i++)
		{
			delete Parameters->at(i).second;
		}
		delete Parameters;
	}
	/// <summary>
	/// call this to set expressions/// </summary>
	void ResetParameters();
private:
	void SetParams(std::vector<operationType::ParameterTypesEnum> *paramTypes);
};