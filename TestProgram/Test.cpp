// Thesis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "ParametricModel.h"

//#define BREAK

void PrintOperations(ParametricModel *paramModel);
void PrintObjects(ParametricModel *paramModel);

int main()
{
	ParametricModel paramModel;

	//Pridanie 1 bodu na poziciu [5,6,0]
	paramModel.AddOperation("Point(Name,5,6,0.5,00112233)");
	paramModel.BuildModel();

	//Pridanie dalsieho bodu na poziciu [5,6,0]
	paramModel.AddOperation("Point(Name2,5,6,0.5,Name,00112233)");
	paramModel.AddOperations(R"(Point(p1,1:p1_X,2:p1_Y,3:p1_Z,12345678);
	Point(p2, 7, 8:p_Y, 9 : abc, 12345678);
	Point(p3, 1, 2, 3, p1, 12345678);
	Point(p4, sin(1 - 0.5), 2, 3, 12345678);
	Line(l1, p1, p2, 12345678);
	Line(l2, p1, p3, 12345678);
	Triangle(t1, l1, p1, 12345678);
	LinearInterpolationDist(lp, p1, p3, 2, 12345678);
	Point(p5, 7, 8, 9, 12345678);
	Point(p6, 1, 2, 3, p1, 12345678);
	Point(p7, 1, 2, 3, p5, 12345678);
	Polygon(poly_1, p1, p2, p3, p4, p5, p6, p7, 12345678);


	Point(Pociatocny bod, 0, 0:o, 0, 12345678);
	Point(Koncovy bod, 1, 2, 3, Pociatocny bod, 12345678);
	Line(Normala, Pociatocny bod, Koncovy bod, 12345678);
	Point(Stred zakladne, 7, 8, 9, 12345678);
	Circle(Podstava, Stred zakladne, 5:polomer, Normala, 12345678);
	Pyramid(Kuzel, Podstava, 10:vyska, 12345678);)");
	
	//paramModel.BuildModel();
	//paramModel.Save("Output.parammodel");
	//paramModel.DeleteModel();

	//paramModel.Load("Output.parammodel");

	paramModel.AddOperation("Sphere(Sphere1,Pociatocny bod,1,FF1122FF)");
	//paramModel.AddOperation("Sphere(Sphere2,Koncovy bod,1,00FF22FF)");
	//paramModel.AddOperation("Extrude(Ex1,poly_1,1,00FFFFFF)");
	paramModel.BuildModel();
	paramModel.Save("Output2.parammodel"); 

	PrintOperations(&paramModel);
	PrintObjects(&paramModel);

	std::cout << "Hello World!\n";

	paramModel.BuildModel();

#ifdef BREAK
	system("pause");
#endif // BREAK



	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	/*glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed
	//GLFWwindow* window =
	//	glfwCreateWindow(800, 600, "OpenGL", glfwGetPrimaryMonitor(), nullptr); // Fullscreen

	glfwMakeContextCurrent(window);

	std::cout << glGetString(GL_VERSION);
	
	paramModel.InitRenderer();
	
	float time = 0;
	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		time+=0.001f;
		paramModel.SetRendererCameraRotation(sin(time) * 3.14f / 5.0f, time, 0);



		paramModel.SetRefValue("o", time);


		paramModel.BuildModel();




		int width, height;
		
		glfwGetFramebufferSize(window,&width, &height);
		paramModel.Draw(width, height);



		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}


void PrintOperations(ParametricModel *paramModel) {
	for (size_t i = 0; i < paramModel->OperationsVec.size(); i++)
	{
		std::cout << "Operation Name>" << paramModel->OperationsVec[i]->name << std::endl;
		std::cout << "operationType>" << (int)paramModel->OperationsVec[i]->operationType << "->" <<
			operationType::OperationToString(paramModel->OperationsVec[i]->operationType) << std::endl;
		std::cout << "Color>" <<
			(int)paramModel->OperationsVec[i]->color[0] << "," <<
			(int)paramModel->OperationsVec[i]->color[1] << "," <<
			(int)paramModel->OperationsVec[i]->color[2] << "," <<
			(int)paramModel->OperationsVec[i]->color[3] << std::endl;

	}
}

void PrintObjects(ParametricModel *paramModel) {
	for (size_t i = 0; i < paramModel->Objects.size(); i++)
	{
		std::cout << (int)paramModel->Objects[i]->GeometricType << std::endl;
		std::cout << paramModel->Objects[i]->ObjectName << std::endl;
		std::cout << (int)paramModel->Objects[i]->color[0] << "," <<
					(int)paramModel->Objects[i]->color[1] << "," <<
					(int)paramModel->Objects[i]->color[2] << "," <<
					(int)paramModel->Objects[i]->color[3] << std::endl;

		if (paramModel->Objects[i]->GeometricType == Object::ObjectTypeEnum::POINT_ObjectType)
		{

			std::cout << "\t" << ((Object::Point *)paramModel->Objects[i])->Position.X << ":";
			std::cout << ((Object::Point *)paramModel->Objects[i])->Position.Y << ":";
			std::cout << ((Object::Point *)paramModel->Objects[i])->Position.Z << std::endl;
		}
	}
}
