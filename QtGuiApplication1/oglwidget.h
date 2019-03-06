#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include "Renderer.h"
#include <QOpenGLWidget>
#include <iostream>



class OGLWidget : public QOpenGLWidget
{
	Q_OBJECT

		Renderer renderer;
public:
    explicit OGLWidget(QWidget *parent = nullptr);

	virtual void initializeGL() {
		//const GLubyte *version = glGetString(GL_VERSION);

		renderer.init();
	}

	virtual void resizeGL(int w, int h) {

	}

	virtual void paintGL() {
		//glClearColor(1, 0, 0, 1);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glViewport(0, 0, width(), height());

		// Draw
		float aspect = (float)width() / (float)height();
		renderer.draw(aspect);

		//auto s = glGetString(GL_VERSION);
		
		//SwapBuffers(this);
		//glFinish();
	}

};

#endif // OGLWIDGET_H
