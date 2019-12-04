#include "pch.h"
#include "Operation.h"
#include <string>
#include "Expression.h"

void Operation::SetParams(std::vector<operationType::ParameterTypesEnum> *paramTypes)
{
	for (size_t i = 0; i < OperationParametersVec->size(); i++)
	{
		void* pointer; 
		operationType::ParameterTypesEnum parameterType = paramTypes->size()<OperationParametersVec->size()? operationType::ParameterTypesEnum::ParameterTypePOINT :(*paramTypes)[i];

		switch (parameterType)
		{
		case operationType::ParameterTypeFLOAT:

				pointer = (void*)new Expression((*OperationParametersVec)[i]);

				break;
		default:
			pointer = (void*)new std::string((*OperationParametersVec)[i]);
			break;
		}
		
		Parameters->push_back(std::make_pair(parameterType, pointer));
	}
}
/// <summary>
/// Need to call every time, if parameters value is changed
/// </summary>
void Operation::ResetParameters() {
		for (size_t i = 0; i < OperationParametersVec->size(); i++) {
			if (Parameters->at(i).first == operationType::ParameterTypeFLOAT)
			{
				delete Parameters->at(i).second;
				Parameters->at(i).second = (void*)new Expression((*OperationParametersVec)[i]);
			}
		}
		this->modified = true;
}