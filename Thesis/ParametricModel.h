#pragma once
#include <vector>
#include "Operation.h"
#include "Parser.h"
#include "ParamRef.h"
#include <string>
#include "TreeBuilder.h"
#include <map>
class ParametricModel
{
private :

	TreeBuilder *treeBuilder;
public:
	/// <summary>
	/// For sorting operations
	/// </summary>
	std::vector <Operation*> OperationsVec;
	/// <summary>
	/// for easier access to operations by name
	/// </summary>
	std::map<std::string, Operation*> OperationMap;

	/// <summary>
	/// Generated objects of parametric model
	/// </summary>
	std::vector <Object::GeometricObject*> Objects;
	/// <summary>
	/// map for objects of parametric model
	/// </summary>
	std::map<std::string, Object::GeometricObject*> ObjectMap;

	/// <summary>
	/// Parameter referencies
	/// </summary>
	ParamRef paramRef;
	ParametricModel() {
		treeBuilder = new TreeBuilder(&OperationsVec,&Objects,&ObjectMap);
	}

	void ReBuildTree() {
		treeBuilder->Build();
			
	}
	/// <summary>
	/// Remove operation from stack at index
	/// Can cause instability! 
	/// </summary>
	/// <param name="index"></param>
	void RemoveOperation(size_t index) {
		//remove all param refs
		paramRef.RemoveRefParamByObjectName(OperationsVec.at(index)->name);
		OperationMap.erase(OperationsVec.at(index)->name);
		OperationsVec.erase(OperationsVec.begin() + index);
	}
	void AddOperation(Operation *c) {
		OperationsVec.push_back(c);
		OperationMap[c->name] = c;
	}
	void InsertOperation(size_t index,Operation *c) {
		OperationsVec.insert(OperationsVec.begin() + index, c);
		OperationMap[c->name] = c;
	}
	bool AddOperation(std::string s) {
		try
		{
			Parser parser;
			Operation *c = NULL;
			parser.InitParser(&OperationsVec,&paramRef);
			if (parser.CreateCommand(s, &c))
			{
				AddOperation(c);
				return true;
			}
			return false;

		}
		catch (const std::exception&)
		{
			return false;
		}
	}
	std::vector <Operation*> GraphCommandTMP;
	ParamRef paramRefTMP;
	size_t InsertedTests=0;
	void resetTest() {
		for (size_t i = OperationsVec.size() ; i < GraphCommandTMP.size(); i++)
		{
			delete(GraphCommandTMP[i]);
		}
		GraphCommandTMP.clear();
		paramRefTMP.Reset();
		StartTest();
	}
	void StartTest() {

		for (size_t i = 0; i < OperationsVec.size(); i++)
		{
			GraphCommandTMP.push_back(OperationsVec.at(i));
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
			Operation *c = NULL;

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
	
	~ParametricModel()
	{
		delete treeBuilder;
		for (size_t i = 0; i < OperationsVec.size(); i++)
		{
			delete(OperationsVec[i]);
		}
		OperationsVec.clear();
	}


	bool AddReferenceParam(std::string ParamRefName, std::string refObjectName, size_t paramIndex) {
		//test if Object with name really exist
		if (OperationMap[refObjectName]!= NULL) {
			return paramRef.AddRefParameter(ParamRefName, refObjectName, paramIndex);
		}

		/*old
		for (size_t i = 0; i < OperationsVec.size(); i++)
		{
			if (OperationsVec.at(i)->name == refObjectName)
			{
				return paramRef.AddRefParameter(ParamRefName, refObjectName, paramIndex);
			}

		}*/
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
	/// Replace operation
	/// </summary>
	/// <param name="index"></param>
	/// <param name="c"></param>
	void ReplaceOperation(size_t index, Operation *c) {
		//delete old operation
		OperationMap.erase(OperationsVec[index]->name);
		delete OperationsVec[index];
		//add new operation
		OperationsVec[index] = c;		
		OperationMap[c->name] = c;
	}

	void SetRefValue(std::string ObjectName, size_t paramindex, std::string value) {
		
		/*old
		for (size_t i = 0; i < OperationsVec.size(); i++)
		{
			if (OperationsVec.at(i)->name == ObjectName) {
				//set value
				OperationsVec.at(i)->OperationParametersVec->at(paramindex) = value;
				break;
			}
		}
		*/


		Operation*  operation = OperationMap[ObjectName];
		if (operation != NULL)
		{
			operation->OperationParametersVec->at(paramindex) = value;
		}
	}
	void SetRefValue(std::string ObjectName, size_t paramindex, float value) {
		SetRefValue(ObjectName, paramindex, std::to_string(value));
	}
	void SetRefValue(std::string RefName,float value) {
		//find by refname objectName and paramIndex
		for (size_t i = 0; i < paramRef.paramRefVec.size(); i++)
		{
			if (paramRef.paramRefVec.at(i).refName == RefName)
			{
				SetRefValue(paramRef.paramRefVec.at(i).ObjectName, paramRef.paramRefVec.at(i).paramindex,  value);
				break;
			}
		}
	}
};

