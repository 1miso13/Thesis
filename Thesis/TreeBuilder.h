#pragma once
#include "GeometricOperation.h"
#include "Command.h"
class TreeBuilder
{
private:
	GeometricObject* BuildObject(Command* command);
public:
	TreeBuilder(std::vector <Command*> *GraphCommand,
		std::vector <GeometricObject*> *Objects) {
		this->GraphCommand = GraphCommand;
		this->Objects = Objects;
	}
	std::vector <GeometricObject*> *Objects;
	std::vector <Command*> *GraphCommand;
	void Build();

	GeometricObject* FindObjectByName(std::vector <GeometricObject*> *Objects,std::string objectName);
};

