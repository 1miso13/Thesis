#pragma once

#include <Windows.h>
#include <vector>
#include <unordered_map>
class Renderer
{

	float backgroundColor[4] = {0.3f,0.53f,0.8f,1};//R,G,B,A
	float cameraPosition[3] = { 0,0,-10 };//X,Y,Z
	float cameraRotation[3] = { 0,-90,0 };//Pitch, Yaw, Roll
	float lightPosition[3] = { 0, 0, -10 };//X,Y,Z
	float lightColor[3] = { 1,1,1};//R,G,B
	bool lightWithCamera = true;
public:
	std::unordered_map<std::string, void*> GLObjects_map;
	float nearPlane=0.1f;
	float farPlane=1000;
	float ambientStrength =0.3;
	Renderer() {}
	~Renderer() {}

	unsigned int /*GLuint*/ vs = 0, fs = 0, program = 0, program_withoutLight = 0;

	void setAmbientStrength(float ambientStrength) {
		this->ambientStrength = ambientStrength;
	}

	void setLightToCamera() {
		lightWithCamera = true;
	}
	void setLightPosition(float X, float Y, float Z) {
		lightWithCamera = false;
		lightPosition[0] = X;
		lightPosition[1] = Y;
		lightPosition[2] = Z;
	}

	void setCameraPosition(float X, float Y, float Z) {
		cameraPosition[0] = X;
		cameraPosition[1] = Y;
		cameraPosition[2] = Z;
	}


	void setCameraRotation(float Pitch, float Yaw, float Roll) {
		cameraRotation[0] = Pitch;
		cameraRotation[1] = Yaw;
		cameraRotation[2] = Roll;
	}

	void SetBackgroundColor(float R, float G, float B, float A);
	void SetBackgroundColor(signed char R, signed char G, signed char B, signed char A);

	void init();

	void draw(float aspect, float fov, int width, int height);

	void PolygonModeFILL();
	void PolygonModeLINE();
};

