// Thesis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "ParametricModel.h"

void PrintOperations(ParametricModel *paramModel);
void PrintObjects(ParametricModel *paramModel);
int main()
{
	ParametricModel paramModel;

	paramModel.AddOperation("Point(Name,5,6,0.5,0)");
	paramModel.ReBuildTree();
	paramModel.AddOperation("Point(Name2,5,6,0.5,Name,0.5)");
	paramModel.ReBuildTree();

	PrintOperations(&paramModel);
	PrintObjects(&paramModel);

    std::cout << "Hello World!\n"; 
	system("pause");
}


void PrintOperations(ParametricModel *paramModel) {
	for (size_t i = 0; i < paramModel->OperationsVec.size(); i++)
	{
		std::cout << "Operation Name>" << paramModel->OperationsVec[i]->name << std::endl;
		std::cout << "operationType>" << paramModel->OperationsVec[i]->operationType << "->" <<
			operationType::OperationToString(paramModel->OperationsVec[i]->operationType) << std::endl;
		std::cout << "visibility>" << paramModel->OperationsVec[i]->visibility << std::endl;
	}
}

void PrintObjects(ParametricModel *paramModel) {
	for (size_t i = 0; i < paramModel->Objects.size(); i++)
	{
		std::cout << paramModel->Objects[i]->GeometricType << std::endl;
		std::cout << paramModel->Objects[i]->ObjectName << std::endl;
		std::cout << paramModel->Objects[i]->visibility << std::endl;

		if (paramModel->Objects[i]->GeometricType == ObjectTypeEnum::POINTObjectType)
		{

			std::cout << "\t" << ((Point *)paramModel->Objects[i])->Position.X << ":";
			std::cout << ((Point *)paramModel->Objects[i])->Position.Y << ":";
			std::cout << ((Point *)paramModel->Objects[i])->Position.Z << std::endl;
		}
	}
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
