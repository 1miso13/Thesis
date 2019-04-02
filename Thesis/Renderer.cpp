#include "pch.h"
#include "Renderer.h"


#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/GLU.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLObject.h"

#define DEBUG
	#ifdef DEBUG
	#include <iostream>
	#include <sstream>

	#define DBOUT( s )            \
	{                             \
	   std::wostringstream os_;    \
	   os_ << s;                   \
	   OutputDebugString( os_.str().c_str() );  \
	}
#endif // DEBUG

//struct vec3 {
//	float x, y, z;
//	vec3(float x, float y, float z) : x(x), y(y), z(z) {} 
//};



std::vector<glm::vec3> vertices = {
	/*glm::vec3(-50.0f, -50.0f, 0.0f),
	glm::vec3(50, -50.0f, 0.0f),
	glm::vec3(0.0f,  25.0f, 0.0f),
	glm::vec3(0.0f,  50.0f, 50.0f)*/
	// Front face
	glm::vec3(- 1.0, -1.0,  1.0),
	glm::vec3(1.0, -1.0,  1.0),
	glm::vec3(1.0,  1.0,  1.0),
	glm::vec3(-1.0,  1.0,  1.0),

	// Back face
	glm::vec3(-1.0, -1.0, -1.0),
	glm::vec3(-1.0,  1.0, -1.0),
	glm::vec3( 1.0,  1.0, -1.0),
	glm::vec3( 1.0, -1.0, -1.0),
	
	// Top face
	glm::vec3(-1.0,  1.0, -1.0),
	glm::vec3(-1.0,  1.0,  1.0),
	glm::vec3( 1.0,  1.0,  1.0),
	glm::vec3( 1.0,  1.0, -1.0),
	
	// Bottom face
	glm::vec3(-1.0, -1.0, -1.0),
	glm::vec3( 1.0, -1.0, -1.0),
	glm::vec3( 1.0, -1.0,  1.0),
	glm::vec3(-1.0, -1.0,  1.0),
	
	// Right face
	glm::vec3( 1.0, -1.0, -1.0),
	glm::vec3( 1.0,  1.0, -1.0),
	glm::vec3( 1.0,  1.0,  1.0),
	glm::vec3( 1.0, -1.0,  1.0),
	
	// Left face
	glm::vec3(-1.0, -1.0, -1.0),
	glm::vec3(-1.0, -1.0,  1.0),
	glm::vec3(-1.0,  1.0,  1.0),
	glm::vec3(-1.0,  1.0, -1.0)
};
float color[] = {
	0.5f, 0.5f, 0.5f,
	 0.5f, 0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.5f,
	 0.5f, 0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.5f,
	 0.5f, 0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.5f,
	 0.5f, 0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.5f,
	 0.5f, 0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.5f,
	 0.5f, 0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.5f,
	 0.5f, 0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.5f,
	 0.5f, 0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.5f,
	 0.5f, 0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.5f,
	 0.5f, 0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.5f,
	 0.5f, 0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.5f,
	 0.5f, 0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f,
	 0.5f, 0.5f, 0.0f,
};




void Renderer::SetBackgroundColor(signed char R, signed char G, signed char B, signed char A) {
	
}
void Renderer::SetBackgroundColor(float R, float G, float B, float A) {
	
}

void Renderer::init() {

	// Init shaders
	static bool glewInitializedOnceToken = false;
	if (!glewInitializedOnceToken) {
		//glewExperimental = GL_TRUE;
		GLenum glewError = glewInit();
#ifdef DEBUG
		if (glewError != GLEW_OK) DBOUT("Error initialization GLEW!" << (int)glewError); //GLEWFatal("Error initialization GLEW!". glewError);
#endif // DEBUG
		glewInitializedOnceToken = true;
	}


	int success = 0;
	char infoLog[512];
	{
		vs = glCreateShader(GL_VERTEX_SHADER);
		const char *vertexShaderSourceCode = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 mvp;

void main()
{	
    gl_Position = mvp * vec4(aPos, 1.0);
}
)";
		glShaderSource(vs, 1, &vertexShaderSourceCode, NULL);
		glCompileShader(vs);

		glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
		if (!success) {
#ifdef DEBUG
			glGetShaderInfoLog(vs, 512, NULL, infoLog);
			// Print to console shader error
			DBOUT("VS Shader Error" << infoLog);
#endif
		}
	}
	{
		fs = glCreateShader(GL_FRAGMENT_SHADER);
		const char *fragmentShaderSourceCode = R"(
#version 330 core
out vec4 FragColor;
uniform vec4 color;

void main()
{
	FragColor = color;
   // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 
)";
		glShaderSource(fs, 1, &fragmentShaderSourceCode, NULL);
		glCompileShader(fs);

		glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
		if (!success) {
#ifdef DEBUG
			glGetShaderInfoLog(fs, 512, NULL, infoLog);
			// Print to console shader error
			DBOUT("VS Shader Error" << infoLog);
#endif
		}
	}

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glGetProgramiv(vs, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(vs, 512, NULL, infoLog);
#ifdef DEBUG
		// Print to console shader error
		DBOUT("VS Shader Error" << infoLog);
#endif
	}

	glGetProgramiv(fs, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(fs, 512, NULL, infoLog);
#ifdef DEBUG
		// Print to console shader error
		DBOUT("VS Shader Error" << infoLog);
#endif
	}
	glDeleteShader(vs);
	glDeleteShader(fs);
}
float scas = 0;
#include <iostream>
void Renderer::draw(float fov, float aspect) {

	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scas += 0.001f;
	TargetVector[0] = cos(glm::radians(cameraRotation[0])) * cos(glm::radians(cameraRotation[1]));
	TargetVector[1] = sin(glm::radians(cameraRotation[0]));
	TargetVector[2] = cos(glm::radians(cameraRotation[0])) * sin(glm::radians(cameraRotation[1]));
	//std::cout << cameraPosition[0]++ << ":" << cameraPosition[1] << ":" << cameraPosition[2] << ">";
	//std::cout << TargetVector[0] << ":" << TargetVector[1] << ":" << TargetVector[2] << std::endl;

	glm::vec3 cameraPos = glm::vec3(cameraPosition[0], cameraPosition[1], cameraPosition[2]);
	glm::vec3 cameraTarget = glm::vec3(cameraPosition[0], cameraPosition[1], cameraPosition[2]) + glm::vec3(TargetVector[0], TargetVector[1], TargetVector[2]);

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 

	glm::mat4 perspectiveProjection = glm::perspective(glm::radians(45.0f), aspect, nearPlane, farPlane);
	glm::mat4 viewMatrix = glm::translate(glm::mat4(),glm::vec3(0,0,-1.0f));// glm::lookAt(cameraPos, cameraTarget, up);//(translate to -Z axis)

	glm::mat4 mvp = perspectiveProjection * viewMatrix;// (model transform is identity)

	// Set uniform for scene (transform)
	int mvpLocation = glGetUniformLocation(program, "mvp");
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);


	// Testing
	for (auto& obj : GLObjects_map) {

		auto _obj = obj.second;
		


		if (!_obj->isInitialized())
			_obj->glInit();
		_obj->glUpdateIfNeeded();
		_obj->glDraw(program);
	}
}