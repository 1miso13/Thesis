#pragma once

#include <Windows.h>

class Renderer
{
public:
	Renderer() {}
	~Renderer() {}

	unsigned int /*GLuint*/ vs = 0, fs = 0, program = 0;

	void setCameraPosition(float X, float Y, float Z) {

	}

	void setCameraLookAt(float X, float Y, float Z) {

	}



	void init();

	void draw(float aspect);
};

