#pragma once

#include <Windows.h>
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

class Renderer
{
public:
	Renderer() {}
	~Renderer() {}

	GLuint vs = 0, fs = 0, program = 0;

	void setCameraPosition(float X, float Y, float Z) {

	}

	void setCameraLookAt(float X, float Y, float Z) {

	}



	void init() {

		// Init shaders
		static bool glewInitializedOnceToken = false;
		if (!glewInitializedOnceToken) {
			glewExperimental = GL_TRUE;
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
#version 450"

in vec3 position;

void main()
{
	gl_Position = vec4(position, 1.0);
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
#version 450
 
out vec4 colorOut;
 
void main()
{
    colorOut = vec4(1.0, 0.0, 0.0, 1.0);
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
		//glCreateBuffers
		//glBindBuffer
		//glBufferData

		// Setup vertex pointer arrays
		//glEnableVertexArrayAttrib(0);
		//glVertexAttribPointer(0, 2, ...)
			
	}

	void draw(float aspect) {
		
		glClearColor(1, 0, 0, 1);
		glLoadIdentity();

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
		glEnd();
		//glUseProgram(program);
		// Setup program unifroms: transform, colors, etc ..
		//glUniform


		//glBindVertexArray(VBA);

		//glDrawArrays = Triangles, Lines, LineLoop
		//glDrawElements

		//SwapBuffers(this);
	}
};

