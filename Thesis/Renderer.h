#pragma once

#include <Windows.h>
#include <vector>
#include <unordered_map>
class Renderer
{

	float backgroundColor[4];//R,G,B,A
	float cameraPosition[3] = { 0,0,0 };//X,Y,Z
	float TargetVector[3] = { 0,0,0 };//X,Y,Z
	float cameraRotation[3] = { 0,-90,0 };//Pitch, Yaw, Roll
public:
	float nearPlane=0.1f;
	float farPlane=10000;
	Renderer() {}
	~Renderer() {}

	unsigned int /*GLuint*/ vs = 0, fs = 0, program = 0;



	std::unordered_map <std::string, int> VOAmap;//<objectName, VAO>


	void setCameraPosition(float X, float Y, float Z) {
		cameraPosition[0] = X;
		cameraPosition[1] = Y;
		cameraPosition[2] = Z;
	}

	void setCameraLookAt(float X, float Y, float Z) {
		TargetVector[0] = X;
		TargetVector[1] = Y;
		TargetVector[2] = Z;
	}
	void setCameraRotation(float Pitch, float Yaw, float Roll) {
		cameraRotation[0] = Pitch;
		cameraRotation[1] = Yaw;
		cameraRotation[2] = Roll;
	}

	void SetBackgroundColor(float R, float G, float B, float A);
	void SetBackgroundColor(signed char R, signed char G, signed char B, signed char A);

	void init();

	void draw(float fov, float aspect);
};

