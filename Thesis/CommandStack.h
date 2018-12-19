#pragma once
#include <vector>
#include "Command.h"
#include "Parser.h"
#include "ParamRef.h"
#include <string>
class CommandStack
{
public:
	ParamRef paramRef;
	std::vector <Command*> GraphCommand;
	void Build() {
		for (size_t i = 0; i < GraphCommand.size(); i++) {
			Command *c = GraphCommand[i];
			if ((*c).visibility>0) {

			}//else invisible
		}
	}
	/// <summary>
	/// Can cause instability!
	/// </summary>
	/// <param name="index"></param>
	void RemoveCommand(size_t index) {
		//remove all param refs
		paramRef.RemoveRefParamByObjectName(GraphCommand.at(index)->name);
		GraphCommand.erase(GraphCommand.begin() + index);
	}
	void AddCommand(Command *c) {
		GraphCommand.push_back(c);
	}
	void InsertCommand(size_t index,Command *c) {
		GraphCommand.insert(GraphCommand.begin() + index, c);
	}
	bool AddCommand(std::string s) {
		try
		{
			Parser parser;
			Command *c = NULL;
			parser.InitParser(&GraphCommand,&paramRef);
			if (parser.CreateCommand(s, &c))
			{
				AddCommand(c);
				return true;
			}
			return false;

		}
		catch (const std::exception&)
		{
			return false;
		}
	}
	std::vector <Command*> GraphCommandTMP;
	ParamRef paramRefTMP;
	size_t InsertedTests=0;
	void resetTest() {
		for (size_t i = GraphCommand.size() ; i < GraphCommandTMP.size(); i++)
		{
			delete(GraphCommandTMP[i]);
		}
		GraphCommandTMP.clear();
		paramRefTMP.Reset();
		StartTest();
	}
	void StartTest() {

		for (size_t i = 0; i < GraphCommand.size(); i++)
		{
			GraphCommandTMP.push_back(GraphCommand.at(i));
		}
		for (size_t i = 0; i < paramRef.paramRefVec.size(); i++)
		{
			paramRefTMP.paramRefVec.push_back(paramRef.paramRefVec.at(i));
		}
	}
	bool TestCommand(std::string s) {
		try
		{
			Parser parser;
			Command *c = NULL;

			//copy GCs

			parser.InitParser(&GraphCommandTMP, &paramRefTMP);

			if (parser.CreateCommand(s, &c))
			{

				GraphCommandTMP.push_back(c);
				return true;
			}
			return false;

		}
		catch (const std::exception&)
		{
			return false;
		}
	}
	
	~CommandStack()
	{
		for (size_t i = 0; i < GraphCommand.size(); i++)
		{
			delete(GraphCommand[i]);
		}
		GraphCommand.clear();
	}


	bool AddReferenceParam(std::string ParamRefName, std::string refObjectName, size_t paramIndex) {
		//test if Object with name really exist
		for (size_t i = 0; i < GraphCommand.size(); i++)
		{
			if (GraphCommand.at(i)->name == refObjectName)
			{
				return paramRef.AddRefParameter(ParamRefName, refObjectName, paramIndex);
			}

		}
		return false;
	}
	bool AddReferenceParamWithoutValidCheck(std::string ParamRefName, std::string refObjectName, size_t paramIndex) {
		return paramRef.AddRefParameter(ParamRefName, refObjectName, paramIndex);
	}
	bool TestRefParam(std::string ParamRefName, std::string refObjectName, size_t paramIndex) {
		return paramRef.AddRefParameter(ParamRefName, refObjectName, paramIndex, true);
	}

	void RemoveReferenceParam(std::string ParamRefName) {
		paramRef.DeleteRefParameter(ParamRefName);
	}
	void RemoveReferenceParam(std::string refObjectName, size_t paramIndex) {
		paramRef.DeleteRefParameter(refObjectName,paramIndex);
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="index"></param>
	/// <param name="c"></param>
	void ModifyCommand(size_t index, Command *c) {
		//delete old command
		delete GraphCommand[index];
		//add new command
		GraphCommand[index] = c;		
	}

	void SetRefValue(std::string ObjectName, size_t paramindex, std::string value) {
		for (size_t i = 0; i < GraphCommand.size(); i++)
		{
			if (GraphCommand.at(i)->name == ObjectName) {
				//set value
				GraphCommand.at(i)->CommandParameterVector->at(paramindex) = value;
				break;
			}
		}
	}
	void SetRefValue(std::string ObjectName, size_t paramindex, float value) {
		SetRefValue(ObjectName, paramindex, std::to_string(value));
	}
	void SetRefValue(std::string RefName,float value) {
		//find by refname objectName and paramIndex
		//SetRefValue(std::string ObjectName, size_t paramindex); TODO
	}
};

