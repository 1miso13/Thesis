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
		//double num;
		switch (parameterType)
		{
		case operationType::ParameterTypeFLOAT:
		//case operationType::ParameterTypeEXPRESSION:

			//char* end;
			//num = strtod((*OperationParametersVec)[i].c_str(), &end);
			//if (*end != '\0')
			//{

				pointer = (void*)new Expression((*OperationParametersVec)[i]);
				//return e.isValid ? TestExpressionsIdentifiers(&e, OperationsMap) : false;
				//parameterType = operationType::ParameterTypeEXPRESSION;
			//}
			//else
			//{
			//	pointer = (void*)new float((float)num);
			//}
				break;
		default:
			pointer = (void*)new std::string((*OperationParametersVec)[i]);
			break;
		}
		
		Parameters->push_back(std::make_pair(parameterType, pointer));
	}
}
