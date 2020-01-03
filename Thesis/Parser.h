#pragma once
#include <vector>
#include <string>
#include "pch.h"
#include "Operation.h"
#include <ctype.h>
#include "OperationTypes.h"
#include "ParamRef.h"
#include <map>
class Parser
{
	std::vector <Operation*> *OperationsVec = NULL;
	std::map <std::string,Operation*> *OperationsMap = NULL;
	ParamRef *paramRef;
	std::string removeSpace(std::string param) {
		//remove first empty char
		size_t i = 0;
		for (; i < param.size(); i++)
		{

			if (!isspace(param[i])) {
				break;
			}
		}
		//remove last empty char
		int j = (int)param.size()-1;
		for (; j >0; j--)
		{

			if (!isspace(param[j])) {
				break;
			}
		}
		return param.substr(i,j-i+1);
	}
	std::string tolower(std::string in) {
		for (size_t i = 0; i < in.size(); i++)
		{
			if (in[i] <= 'Z' && in[i] >= 'A')
				in[i] = in[i] - ('Z' - 'z');
		}
		return in;
	}
	bool TestValidObjectName(std::string objectName) {
		//test valid name
		return (*OperationsMap)[objectName] == NULL;
	}
	bool toFloat(const std::string s,float * val) {
		const char *begin = s.c_str();
		char *end;
		*val = std::strtof(begin, &end);
		bool ret = true;
		if (end == begin) return false;
		size_t len = strlen(end);
		for (size_t i = 0; i < len; i++, end++) {
			if (!isspace(*end)) {
				return false;
			}
		}
		return ret;
	}
private:
	bool RemoveParenthesisChar(std::string& s) {
		if (s.length()>0 && s[s.length()-1]==')')
		{
			s.pop_back();
			return true;
		}
		else
		{
			return false;
		}
	}
public:
	bool ParseCom(std::string *sPtr, std::string *commandNamePtr, std::vector<std::string> *OperationParametersVec) {
		size_t length=(*sPtr).length();

		std::string token = "";
		*commandNamePtr = "";
		size_t i = 0;
		for (; i < length; i++)
		{
			if ((*sPtr)[i]=='(')
			{
				break;
			}
			token = token + (*sPtr)[i];
		}
		*commandNamePtr = token;
		token = "";
		if (i==length-1)
		{
			return false;
		}
		i++;
		size_t paramIndex = 0;
		for (;  i< length; i++)
		{
			if ((*sPtr)[i] == ',')
			{
				if (token=="")
				{
					return false;
				}
				OperationParametersVec->push_back(removeSpace(token));
				token = "";
			}
			else
			{
				token = token + (*sPtr)[i];
			}
		}
		//remove last character )
		if (!RemoveParenthesisChar(token)) {
			return false;
		}

		OperationParametersVec->push_back(removeSpace(token));

		return true;
	}
	bool ParseOperation(std::string *commandStringPtr, std::string *commandNamePtr, std::string *objectNamePtr, std::vector <std::string> *CommandParameterVectorPtr, unsigned char color[4], std::vector <paramRefStruct> *refStructVec) {
		///divide command name and parameters
		///"operationName(parameter1,parameter2,...,parameterN)"

		//divide operationString by '('
		//	[0] - command name 
		//	[1] - command parameters
		*commandStringPtr =removeSpace(*commandStringPtr);
		if (!ParseCom(commandStringPtr, commandNamePtr, CommandParameterVectorPtr))
		{
			return false;
		}


		///1.Parameter is Name
		*objectNamePtr = (*CommandParameterVectorPtr)[0];

		(*CommandParameterVectorPtr).erase((*CommandParameterVectorPtr).begin());

		///Last parameter is color in format RRGGBBAA
		if (!operationType::colorParser((*CommandParameterVectorPtr).at((*CommandParameterVectorPtr).size() - 1), color))
		{
			return false;
		}
		//remove color parameter
		(*CommandParameterVectorPtr).erase((*CommandParameterVectorPtr).end()-1);

		//REFERENCE params
		//parameterValue : referenceName
		for (size_t i = 0; i < (*CommandParameterVectorPtr).size(); i++)
		{
			std::string s = CommandParameterVectorPtr->at(i);
			char delimiter = ':';
			size_t pos=0;
			if ((pos = s.find(delimiter)) != std::string::npos)
			{
				std::string token;
				token = s.substr(0, pos);
				token = removeSpace(token);
				s.erase(0, pos + 1);
				
				if(s.find(delimiter) != std::string::npos) { //only one ':' is allowed
					return false;
				}
				paramRefStruct paramRef;
				paramRef.paramindex = i;
				paramRef.refName = s;
				refStructVec->push_back(paramRef);
				CommandParameterVectorPtr->at(i)= token;
			}
		}
		return true;
	}
public:
	void InitParser(
		std::vector <Operation*> *OperationsVec, std::map <std::string, Operation*> *OperationsMap, ParamRef *paramRef) {
		this->OperationsVec = OperationsVec;
		this->OperationsMap = OperationsMap;
		this->paramRef = paramRef;
	}
	bool CreateOperation(std::string operationString,Operation **cPtrPtr) {
		std::string operationName;
		std::string objectName;
		*cPtrPtr = NULL;
		if (OperationsVec==NULL || OperationsMap== NULL)
		{
			return false;
		}
		unsigned char color[4] = {0,0,0,0};
			//parse parameters
		std::vector <std::string> *OperationParametersVec = new std::vector <std::string>();

		std::vector <paramRefStruct> refStructVec;
		if (!ParseOperation(&operationString, &operationName, &objectName, OperationParametersVec,color, &refStructVec))//test command syntax
		{
			return false;
		}

		//test commands
		operationType::OperationTypeEnum operationType;
		size_t typeOfParameters=0;
		//if ((operationType = operationType::GetOperationType(operationName, OperationParametersVec, OperationsVec ,&typeOfParameters))== operationType::INVALID)
		//{
		//	return false;
		//}
		std::vector<operationType::ParameterTypesEnum> *paramTypes;
		if ((operationType = operationType::GetOperation(operationName, &typeOfParameters , OperationsVec, OperationsMap, OperationParametersVec,&paramTypes)) == operationType::INVALID)
		{
			return false;
		}


		if (!TestValidObjectName(objectName)) {
			//bad name ERROR
			return false;
		}
		//add referencied parameters
		
		for (size_t i = 0; i < refStructVec.size(); i++)
		{
			if(!(*paramRef).AddRefParameter(refStructVec.at(i).refName, objectName, refStructVec.at(i).paramindex)){
				return false;
			}//.paramRefVec.push_back(refStructVec.at(i));
		}
		
			//add parameter list to command parameter vector
		*cPtrPtr = new Operation(objectName, color,operationType,OperationParametersVec,typeOfParameters, paramTypes);

		return true;
	}
	std::vector <Operation> * Parse(std::string inputString) {//TODO multiple commands
		std::vector <Operation*> *commandsVector = new std::vector<Operation*>();
		//get command;
		std::string s;
		Operation *c;
		if (CreateOperation(s,&c)) {
			commandsVector->push_back(c);
		}
	}
	//Parse
};
