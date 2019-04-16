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



//std::vector<glm::vec3> vertices = {
//	/*glm::vec3(-50.0f, -50.0f, 0.0f),
//	glm::vec3(50, -50.0f, 0.0f),
//	glm::vec3(0.0f,  25.0f, 0.0f),
//	glm::vec3(0.0f,  50.0f, 50.0f)*/
//	// Front face
//	glm::vec3(- 1.0, -1.0,  1.0),
//	glm::vec3(1.0, -1.0,  1.0),
//	glm::vec3(1.0,  1.0,  1.0),
//	glm::vec3(-1.0,  1.0,  1.0),
//
//	// Back face
//	glm::vec3(-1.0, -1.0, -1.0),
//	glm::vec3(-1.0,  1.0, -1.0),
//	glm::vec3( 1.0,  1.0, -1.0),
//	glm::vec3( 1.0, -1.0, -1.0),
//	
//	// Top face
//	glm::vec3(-1.0,  1.0, -1.0),
//	glm::vec3(-1.0,  1.0,  1.0),
//	glm::vec3( 1.0,  1.0,  1.0),
//	glm::vec3( 1.0,  1.0, -1.0),
//	
//	// Bottom face
//	glm::vec3(-1.0, -1.0, -1.0),
//	glm::vec3( 1.0, -1.0, -1.0),
//	glm::vec3( 1.0, -1.0,  1.0),
//	glm::vec3(-1.0, -1.0,  1.0),
//	
//	// Right face
//	glm::vec3( 1.0, -1.0, -1.0),
//	glm::vec3( 1.0,  1.0, -1.0),
//	glm::vec3( 1.0,  1.0,  1.0),
//	glm::vec3( 1.0, -1.0,  1.0),
//	
//	// Left face
//	glm::vec3(-1.0, -1.0, -1.0),
//	glm::vec3(-1.0, -1.0,  1.0),
//	glm::vec3(-1.0,  1.0,  1.0),
//	glm::vec3(-1.0,  1.0, -1.0)
//};
//float color[] = {
//	0.5f, 0.5f, 0.5f,
//	 0.5f, 0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f,
//	 0.5f, 0.5f, 0.0f,
//	0.5f, 0.5f, 0.5f,
//	 0.5f, 0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f,
//	 0.5f, 0.5f, 0.0f,
//	0.5f, 0.5f, 0.5f,
//	 0.5f, 0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f,
//	 0.5f, 0.5f, 0.0f,
//	0.5f, 0.5f, 0.5f,
//	 0.5f, 0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f,
//	 0.5f, 0.5f, 0.0f,
//	0.5f, 0.5f, 0.5f,
//	 0.5f, 0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f,
//	 0.5f, 0.5f, 0.0f,
//	0.5f, 0.5f, 0.5f,
//	 0.5f, 0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f,
//	 0.5f, 0.5f, 0.0f,
//	0.5f, 0.5f, 0.5f,
//	 0.5f, 0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f,
//	 0.5f, 0.5f, 0.0f,
//	0.5f, 0.5f, 0.5f,
//	 0.5f, 0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f,
//	 0.5f, 0.5f, 0.0f,
//	0.5f, 0.5f, 0.5f,
//	 0.5f, 0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f,
//	 0.5f, 0.5f, 0.0f,
//	0.5f, 0.5f, 0.5f,
//	 0.5f, 0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f,
//	 0.5f, 0.5f, 0.0f,
//	0.5f, 0.5f, 0.5f,
//	 0.5f, 0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f,
//	 0.5f, 0.5f, 0.0f,
//	0.5f, 0.5f, 0.5f,
//	 0.5f, 0.5f, 0.0f,
//	 0.0f,  0.5f, 0.0f,
//	 0.5f, 0.5f, 0.0f,
//};




void Renderer::SetBackgroundColor(signed char R, signed char G, signed char B, signed char A) {
	backgroundColor[0] = R/255.0f;
	backgroundColor[1] = G/255.0f;
	backgroundColor[2] = B/255.0f;
	backgroundColor[3] = A/255.0f;
}
void Renderer::SetBackgroundColor(float R, float G, float B, float A) {
	backgroundColor[0] = R;
	backgroundColor[1] = G;
	backgroundColor[2] = B;
	backgroundColor[3] = A;
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
layout (location = 1) in vec3 aNormal;

uniform mat4 mvp;
uniform vec3 lightPos;  

out vec3 Normal;
out vec3 FragPos; 
out vec4 lightPosTran;

void main()
{	
	lightPosTran = mvp * vec4(lightPos, 1.0);
    gl_Position = mvp * vec4(aPos, 1.0);
	FragPos = aPos;
	Normal = aNormal;
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
in vec3 Normal;  
in vec3 FragPos; 
in vec4 lightPosTran;
uniform vec4 color;
uniform vec3 lightColor;

out vec4 FragColor;

void main()
{
	float ambientStrength = 0.3;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPosTran.xyz - FragPos);  

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;


	
	FragColor = vec4(ambient + diffuse,1) * color;
	//FragColor = color*(FragPos.r+lightColor.r+lightPos.r);//lightColor.x;
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
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Renderer::draw(float aspect, float fov) {

	glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Light
	int lightLocation = glGetUniformLocation(program, "lightPos");
	glUniform3f(lightLocation, lightPosition[0], lightPosition[1], lightPosition[2]);
	int lightColorLocation = glGetUniformLocation(program, "lightColor");
	glUniform3f(lightColorLocation, lightColor[0], lightColor[1], lightColor[2]);



	//transform
	glm::mat4 perspectiveProjection = glm::perspective(45.0f, aspect, nearPlane, farPlane);
	
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(cameraPosition[0], cameraPosition[1], cameraPosition[2]));
	view = glm::rotate(view, cameraRotation[0], glm::vec3(1, 0, 0));
	view = glm::rotate(view, cameraRotation[1], glm::vec3(0, 1, 0));
	view = glm::rotate(view, cameraRotation[2], glm::vec3(0, 0, 1));


	glm::mat4 mvp = perspectiveProjection * view;// (model transform is identity)

	// Set uniform for scene (transform)
	int mvpLocation = glGetUniformLocation(program, "mvp");
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);

	//draw globjects
	for (auto obj : GLObjects_map) {

		auto _obj = (GLObject*)obj.second;
		


		if (!_obj->isInitialized())
			_obj->glInit();
		_obj->glUpdateIfNeeded();
		if (_obj->mode == GL_TRIANGLES)
		{
			_obj->glDraw(program);
		}
	}
	std::cout << std::endl;
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "OpenGL error: " << err << std::endl;
	}

}