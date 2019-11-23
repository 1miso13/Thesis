#pragma once
#include <vector>
#include "Operation.h"
#include "Parser.h"
#include "ParamRef.h"
#include <string>
#include "TreeBuilder.h"
#include <map>

#include "Renderer.h"
class ParametricModel
{
private :

	TreeBuilder *treeBuilder;
	Renderer renderer;
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
	void UpdateGLObjects();
	ParametricModel() {
		treeBuilder = new TreeBuilder(&OperationsVec,&Objects,&ObjectMap, &paramRef,&OperationMap);
		paramRef.InitPrimary();
	}
	Object::GeometricObject* GetObject(std::string objectName) {
		return ObjectMap[objectName];
	}
	/// <summary>
	/// Rebuild objects in model
	/// Call this to apply modifications
	/// </summary>
	void BuildModel() {
		treeBuilder->Build();
		UpdateGLObjects();
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
private:
	bool IsNotEmpty(std::string s)
	{
		bool isNotEmpty = false;
		for (size_t i = 0; i < s.length(); i++)
		{
			if (!isspace(s[i]))
			{
				isNotEmpty = true;
			}
		}
		return isNotEmpty;
	}
	void ParseCommands(std::vector<std::string>* commandsVec, std::string s) {
		std::string delimiter = ";";
		size_t pos = 0;
		std::string token;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			s.erase(0, pos + delimiter.length());
			if (IsNotEmpty(token))
			{
				(*commandsVec).push_back(token);
			}
		}if (IsNotEmpty(s))
		{
			(*commandsVec).push_back(s);
		}
	}
	void RemoveAllGLObjects();
public:

	/// <summary>
	/// Resets whole instance of model
	/// </summary>
	/// <returns></returns>
	void DeleteModel() {
		paramRef.Reset();
		for (size_t i = 0; i < OperationsVec.size(); i++)
		{
			delete(OperationsVec[i]);
		}
		OperationsVec.clear();
		OperationMap.clear();
		for (size_t i = 0; i < Objects.size(); i++)
		{
			//delete(Objects[i]);
		}
		Objects.clear();
		ObjectMap.clear();

		GraphCommandTMP.clear();
		OperationMapTMP.clear();
		if (GLContext)
		{
			RemoveAllGLObjects();
		}
	}
	/// <summary>
	/// Add multiple operations devided by semicolon ;
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	bool AddOperations(std::string s) {
		std::vector<std::string> commandsVec;
		ParseCommands(&commandsVec, s);
		bool valid = true;
		resetTest();
		for (size_t i = 0; i < commandsVec.size(); i++)
		{//before creating, need to test, if all operations are valid
			if (!TestOperation(commandsVec[i]))
			{
				valid = false;
			}
		}

		resetTest();
		if (!valid)
		{
			return false;
		}
		Parser parser;
		Operation *c = NULL;
		parser.InitParser(&OperationsVec, &OperationMap, &paramRef);
		for (size_t i = 0; i < commandsVec.size(); i++)
		{
			try
			{
				if (parser.CreateOperation(commandsVec[i], &c))
				{
					AddOperation(c);
				}
			}
			catch (const std::exception&)
			{
				return false;
			}
		}
		return true;

	}
	bool AddOperation(std::string s) {
		try
		{
			Parser parser;
			Operation *c = NULL;
			parser.InitParser(&OperationsVec, &OperationMap, &paramRef);
			if (parser.CreateOperation(s, &c))
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
private:
	std::vector <Operation*> GraphCommandTMP;
	std::map <std::string,Operation*> OperationMapTMP;
	ParamRef paramRefTMP;
	size_t InsertedTests=0;
public:
	void resetTest() {
		for (size_t i = OperationsVec.size() ; i < GraphCommandTMP.size(); i++)
		{
			delete(GraphCommandTMP[i]);
		}
		GraphCommandTMP.clear();
		paramRefTMP.Reset();
		OperationMapTMP.clear();
		StartTest();
	}
private:
	void StartTest() {

		for (size_t i = 0; i < OperationsVec.size(); i++)
		{
			GraphCommandTMP.push_back(OperationsVec.at(i));
			OperationMapTMP[OperationsVec.at(i)->name] = OperationsVec.at(i);
		}
		for (size_t i = 0; i < paramRef.paramRefVec.size(); i++)
		{
			paramRefTMP.paramRefVec.push_back(paramRef.paramRefVec.at(i));
		}
	}
public:
	bool TestOperation(std::string s) {
		try
		{
			Parser parser;
			Operation *c = NULL;

			//copy GCs

			parser.InitParser(&GraphCommandTMP, &OperationMapTMP ,&paramRefTMP);

			if (parser.CreateOperation(s, &c))
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
		DeleteModel();
		delete treeBuilder;
	}

public:
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
		operation->ResetParameters();
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
	/// <summary>
	/// Get object value in string form
	/// </summary>
	/// <returns>object value</returns>
	float GetObjectValue(std::string s,bool* Err) {
		return ObjectsValues::GetObjectValue(&ObjectMap, s, Err);
	}
private:
	bool GLContext = false;
public:
	/// <summary>
	/// Init renderer
	/// </summary>
	void InitRenderer() {
		renderer.init();
		GLContext = true;

		UpdateGLObjects();
	}

	/// <summary>
	/// Draw OpenGL 
	/// </summary>
	/// <param name="aspect"></param>
	void Draw(int width, int height) {
		if (width == 0 || height == 0)
		{
			return;
		}
		float aspect = (float)width / (float)height;
		if (GLContext)
		{
			renderer.draw(aspect, 45, width, height);
		}
	}
	void SetRendererCameraPosition(float X, float Y, float Z) {
		renderer.setCameraPosition(X, Y, Z);
	}
	void SetRendererCameraRotation(float Pitch, float Yaw, float Roll) {
		renderer.setCameraRotation(Pitch, Yaw, Roll);
	}

	/// <summary>
	/// Save parametric model to file
	/// </summary>
	/// <param name="filePath">file path</param>
	void Save(std::string filePath);
	bool Load(std::string filePath);

	void setRendererAmbientStrength(float ambientStrength) {
		renderer.setAmbientStrength(ambientStrength);
	}
};

