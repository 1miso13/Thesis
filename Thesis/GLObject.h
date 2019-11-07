#pragma once

#include <Windows.h>
#include "pch.h"
#include "Renderer.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/GLU.h>
#include <glm/glm.hpp>

#include <iostream>


class GLObject {
	GLuint _vbo = 0, _vboN = 0, _ebo = 0, _vao = 0;
	bool _needsUpdate = false;
	bool _initialized = false;
public:
	std::vector<float> *vertices;
	std::vector<float> *normals;
	std::vector<int> *indices;
	glm::vec4 color;

	void setNeedsUpdate() {
		_needsUpdate = true;
	}

	void glInit() {
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);
		glGenBuffers(1, &_vboN);
		glGenBuffers(1, &_ebo);

		glBindVertexArray(_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, _vboN);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, NULL);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		_initialized = true;
	}

	bool isInitialized() const {
		return _initialized;
	}

	void glDestroy() {
		glDeleteVertexArrays(1, &_vao);
		glDeleteBuffers(1, &_vbo);
		glDeleteBuffers(1, &_vboN);
		glDeleteBuffers(1, &_ebo);
		_initialized = false;
	}

	void glUpdate() {
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(float), vertices->data(), GL_DYNAMIC_DRAW);
		//std::cout << glGetError();
		glBindBuffer(GL_ARRAY_BUFFER, _vboN);
		glBufferData(GL_ARRAY_BUFFER, normals->size() * sizeof(float), normals->data(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(int), indices->data(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void glUpdateIfNeeded() {
		if (_needsUpdate) glUpdate();
		_needsUpdate = false;
	}
	GLenum mode = GL_TRIANGLES;
//float timeValue = 0;
	void glDraw(GLuint program/*, GLenum mode = GL_TRIANGLES*/) {
		// Uniforms (Color)
		//glProgramUniform4fv(program,...);
		int vertexColorLocation = glGetUniformLocation(program, "color");
		// use our shader program when we want to render an object
		glUseProgram(program);
		//timeValue += 0.01;
		//float greenValue = sin(timeValue) / 2.0f + 0.5f;
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glUniform4f(vertexColorLocation, color.r, color.g, color.b, color.a);

		glBindVertexArray(_vao);
		glDrawElements(mode, (GLsizei)indices->size(), GL_INT, NULL);
		glBindVertexArray(0);
	}
};
