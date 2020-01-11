//#pragma once
//

#include "pch.h"
#include "GLObject.h"
//
//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/GLU.h>
//#include <glm/glm.hpp>
//
//class GLObject {
//	GLuint _vbo = 0, _ebo = 0, _vao = 0;
//	bool _needsUpdate = false;
//	bool _initialized = false;
//public:
//	std::vector<glm::vec3> vertices;
//	std::vector<unsigned> indices;
//
//	void setNeedsUpdate() {
//		_needsUpdate = true;
//	}
//
//	void glInit() {
//		glGenVertexArrays(1, &_vao);
//		glGenBuffers(1, &_vbo);
//		glGenBuffers(1, &_ebo);
//
//		glBindVertexArray(_vao);
//		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
//
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), NULL);
//		glEnableVertexAttribArray(0);
//
//		glBindVertexArray(0);
//		_initialized = true;
//	}
//
//	bool isInitialized() const {
//		return _initialized;
//	}
//
//	void glDestroy() {
//		glDeleteVertexArrays(1, &_vao);
//		glDeleteBuffers(1, &_vbo);
//		glDeleteBuffers(1, &_ebo);
//		_initialized = false;
//	}
//
//	void glUpdate() {
//		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
//		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_DYNAMIC_DRAW);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_DYNAMIC_DRAW);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	}
//
//	void glUpdateIfNeeded() {
//		if (_needsUpdate) glUpdate();
//		_needsUpdate = false;
//	}
//
//	void glDraw(GLuint program, GLenum mode = GL_TRIANGLES) {
//		glUseProgram(program);
//		// Uniforms (Color)
//		//glProgramUniform4fv(program,...);
//		glBindVertexArray(_vao);
//		glDrawElements(mode, (GLsizei)indices.size(), GL_UNSIGNED_INT, NULL);
//		glBindVertexArray(0);
//	}
//};