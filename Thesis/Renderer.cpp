#include "pch.h"
#include "Renderer.h"


#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/GLU.h>


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
float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

void Renderer::init(){

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

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
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

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 1, 0, 1);
	glLoadIdentity();


	// Create VBA per object buffer array contains all VBO
	//glCreateVertexArrays()

	// Create VBO vertices, normals, uvs
	// glGenBuffers(1, &VBO);
	glCreateBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Setup vertex pointer arrays
	//glEnableVertexArrayAttrib(0);
	//glVertexAttribPointer(0, 2, ...)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}
void Renderer::draw(float aspect) {

	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*glLoadIdentity();

	glBegin(GL_TRIANGLES);

	glColor3f(0, 1, 0);

	glVertex2f(0, 0);
	glVertex2f(1, 1);
	glVertex2f(-1, 1);

	glEnd();


	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 1);
	glNormal3f(-1, 0, 0.707);
	glVertex3f(-1, 1, 0);
	glVertex3f(-1, -1, 0);
	glVertex3f(0, 0, 1.2);
	glEnd();*/
	//glUseProgram(program);
	// Setup program unifroms: transform, colors, etc ..
	//glUniform


	//glBindVertexArray(VBA);

	//glDrawArrays = Triangles, Lines, LineLoop
	//glDrawElements

	//SwapBuffers(this);

	// 0. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 1. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 2. use our shader program when we want to render an object
	glUseProgram(program);
	// 3. now draw the object 
	glDrawArrays(GL_TRIANGLES, 0, 3);

}