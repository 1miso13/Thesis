#pragma once
#include <vector>
#include "ParamRefStruct.h"
class ParamRef
{
public:
	static std::vector <paramRefStruct> *paramRefVecPtr;
	std::vector <paramRefStruct> paramRefVec;
	/*std::vector <std::string>	referecedObjectVec;
	std::vector <size_t>		referecedParamIndexVec;
	std::vector <std::string>	paramRefNameVec;*/
	void Reset() {
		paramRefVec.clear();
	}
	void InitPrimary() {
		paramRefVecPtr = &paramRefVec;
	}

	std::vector <paramRefStruct>* GetVec() {
		return &paramRefVec;
	}
	/// <summary>
	/// Add reference of parameter, if is possible
	/// If already exist, old reference name is changed to new
	/// </summary>
	/// <param name="ParamRefName">If empty or reference with same name already exist, return false</param>
	/// <param name="refObjectName">Object name</param>
	/// <param name="paramIndex">Parameter index</param>
	/// <param name="test">Only tests, if it's possible to insert. Do not add</param>
	/// <returns>false, if already exist</returns>
	bool AddRefParameter(std::string ParamRefName, std::string refObjectName, size_t paramIndex, bool test = false);
	/// <summary>
	/// Find referencied parameter and delete
	/// </summary>
	/// <param name="parameterName">Name of parameter to delete</param>
	void DeleteRefParameter(std::string ParamRefName);
	/// <summary>
	/// Find referencied parameter and delete
	/// </summary>
	/// <param name="refObjectName">Name of object</param>
	/// <param name="paramIndex">Index of parameter</param>
	void DeleteRefParameter(std::string refObjectName, size_t paramIndex);
	/// <summary>
	/// Return Value
	/// </summary>
	/// <param name="parameterName"></param>
	/// <param name="refObjectName"></param>
	/// <param name="paramIndex">If found</param>
	bool FindRefParameter(std::string ParamRefName, std::string *refObjectName, size_t *paramIndex);
	/// <summary>
	/// Find all referencies where is object name == refObjectName
	/// </summary>
	/// <param name="refObjectName"></param>
	/// <param name="paramStructVecPtr"></param>
	/// <returns></returns>
	bool FindRefParameterByObject(std::string refObjectName, std::vector <paramRefStruct> * paramStructVecPtr);
	/// <summary>
	/// Find reference name of object name and index of parameter
	/// </summary>
	/// <param name="refObjectName">Object name</param>
	/// <param name="paramIndex">Parameter index</param>
	/// <param name="paramRefName">OUT Parameter reference name</param>
	/// <returns>Found</returns>
	bool FindRefParameterByObjectAndIndex(std::string refObjectName, size_t paramIndex, std::string *paramRefName);
	/// <summary>
	/// remove from all referencies, where object name == refObjectName
	/// </summary>
	/// <param name="refObjectName"></param>
	void RemoveRefParamByObjectName(std::string refObjectName);
	ParamRef();
	~ParamRef();
};
inline void ParamRef::RemoveRefParamByObjectName(std::string refObjectName) {
	for (int i = (int)paramRefVec.size() - 1; i >= 0; i--)
	{
		if (paramRefVec.at(i).ObjectName == refObjectName)
		{
			paramRefVec.erase(paramRefVec.begin() + i);
		}
	}
}
inline bool ParamRef::FindRefParameter(std::string ParamRefName, std::string *refObjectNamePtr, size_t *paramIndexPtr) {
	for (size_t i = 0; i < paramRefVec.size(); i++) {
		if (paramRefVec.at(i).refName == ParamRefName)
		{
			*refObjectNamePtr = paramRefVec.at(i).ObjectName;
			*paramIndexPtr = paramRefVec.at(i).paramindex;
		}
	}
}
inline bool ParamRef::FindRefParameterByObject(std::string refObjectName, std::vector <paramRefStruct> * paramStructVecPtr) {
	for (size_t i = 0; i < paramRefVec.size(); i++) {
		if (paramRefVec.at(i).ObjectName == refObjectName)
		{
			paramStructVecPtr->push_back(paramRefVec.at(i));
		}
	}
}
inline bool ParamRef::FindRefParameterByObjectAndIndex(std::string refObjectName, size_t paramIndex, std::string *paramRefName) {
	for (size_t i = 0; i < paramRefVec.size(); i++) {
		if (paramRefVec.at(i).ObjectName == refObjectName && paramRefVec.at(i).paramindex == paramIndex)
		{
			*paramRefName= paramRefVec.at(i).refName;
			return true;
		}
	}
	return false;
}

inline bool ParamRef::AddRefParameter(std::string ParamRefName, std::string refObjectName, size_t paramIndex, bool test) {
	bool wd = false;
	for (size_t i = 0; i < ParamRefName.length(); i++)
	{
		if (!isspace(ParamRefName[i]))
		{
			wd = true;
		}
	}
	if (!wd)
	{
		return false;
	}
	//If already defined with another ref name
	int Index = -1;
	//Test if ref name doesnt exist
	for (size_t i = 0; i < paramRefVec.size(); i++)
	{
		if (paramRefVec.at(i).ObjectName == refObjectName && paramRefVec.at(i).paramindex == paramIndex)
		{
			Index = (int)i;
			continue;
		}
		if (paramRefVec.at(i).refName == ParamRefName)
		{
			return false;
		}
	}
	if (test)
	{///Test doesn't modify
		return true;
	}
	if (Index == -1)
	{///add new pramRef

		paramRefStruct paramRefstr;
		paramRefstr.ObjectName = refObjectName;
		paramRefstr.paramindex = paramIndex;
		paramRefstr.refName = ParamRefName;

		paramRefVec.push_back(paramRefstr);
	}
	else
	{///change ref name
		paramRefVec.at(Index).refName = ParamRefName;
	}

	return true;
}

inline void ParamRef::DeleteRefParameter(std::string ParamRefName) {
	for (int i = (int)paramRefVec.size()-1; i >= 0;i--)
	{
		if (paramRefVec.at(i).refName == ParamRefName)
		{
			paramRefVec.erase(paramRefVec.begin() + i);
			return;
		}
	}
}
inline void ParamRef::DeleteRefParameter(std::string refObjectName, size_t paramIndex) {
	for (int i = (int)paramRefVec.size()-1; i >= 0;i--)
	{
		if (paramRefVec.at(i).ObjectName == refObjectName && paramRefVec.at(i).paramindex == paramIndex)
		{
			paramRefVec.erase(paramRefVec.begin() + i);
			return;
		}
	}
}

inline ParamRef::ParamRef()
{

}


inline ParamRef::~ParamRef()
{
}
