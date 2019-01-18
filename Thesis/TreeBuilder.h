#pragma once
class TreeBuilder
{
public:
	void Build(
		std::vector <Command*> *GraphCommand,
		std::vector <GeometricObject*> *Objects);
	TreeBuilder();
	~TreeBuilder();

	GeometricObject* BuildObject(Command* command)
};

