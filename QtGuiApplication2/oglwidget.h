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

	 void initializeGL() {
		//const GLubyte *version = glGetString(GL_VERSION);

		renderer.init();
	}

	void resizeGL(int w, int h) {

	}

	void paintGL() {

		// Draw
		float aspect = (float)width() / (float)height();
		renderer.draw(45,aspect);

		
		//SwapBuffers(this);
		//glFinish();
	}

};

#endif // OGLWIDGET_H
