#include "pch.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "ParametricModel.h"

//#define BREAK

void PrintOperations(ParametricModel *paramModel);
void PrintObjects(ParametricModel *paramModel);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
float distance = 10;

int main()
{
	ParametricModel paramModel;

	paramModel.AddOperations(R"(
Point(HouseTopCenter,0,2:houseHeight,0,00000000);
Point(PointUP,0,1,0,HouseTopCenter,00000000);
Line(LineUP,HouseTopCenter,PointUP,00000000);
Rectangle(Top,HouseTopCenter,3:houseX,2+sin(time/1500):houseY,sin(time/1000)-0.2:rotation,LineUP,00000000);
Extrude(House,Top,0-houseHeight,00FF00FF);)");
	
	paramModel.BuildModel();
	paramModel.Save("Output.parammodel");
	paramModel.DeleteModel();

	paramModel.Load("Output.parammodel");

	paramModel.AddOperation("Cone(Roof,Top,2:roofHeight,FF0000FF)");
	paramModel.BuildModel();
	paramModel.Save("Output2.parammodel"); 

	PrintOperations(&paramModel);
	PrintObjects(&paramModel);

	paramModel.BuildModel();

#ifdef BREAK
	system("pause");
#endif // BREAK


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed
	//GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", glfwGetPrimaryMonitor(), nullptr); // Fullscreen

	glfwMakeContextCurrent(window);
	glfwSetScrollCallback(window, scroll_callback);

	std::cout << glGetString(GL_VERSION) << std::endl;
	
	paramModel.InitRenderer();
	paramModel.SetBackgroundColor(1, 1, 1, 1.0f);

	float time = 1;
	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		time+=0.001f;
		paramModel.SetRendererCameraRotation(sin(time) * 3.14f / 5.0f, 0, 0);
		paramModel.SetRendererCameraPosition(0,0,-distance);

		paramModel.BuildModel();

		int width, height;
		
		glfwGetFramebufferSize(window,&width, &height);
		paramModel.Draw(0,0, 120.0f,width, height);


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


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	distance -= yoffset;
}
