#ifndef OGLWIDGET_H
#define OGLWIDGET_H


#include <QOpenGLWidget>
#include <iostream>
#include "ParametricModel.h"


class OGLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
    explicit OGLWidget(QWidget *parent = nullptr);

	ParametricModel * paramModel;
	void setParamModel(ParametricModel * paramModel) {
		this->paramModel = paramModel;
	}

	virtual void initializeGL() {
		//const GLubyte *version = glGetString(GL_VERSION);

		//QtGuiApplication1::paramModel.InitRenderer();
		paramModel->InitRenderer();
	}
	virtual void resizeGL(int w, int h) {

	}
	virtual void paintGL() {
		//glClearColor(1, 0, 0, 1);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glViewport(0, 0, width(), height());

		// Draw
		float aspect = (float)width() / (float)height();
		//QtGuiApplication1::paramModel.Draw(aspect);
		paramModel->Draw(360,aspect);

		//auto s = glGetString(GL_VERSION);
		
		//SwapBuffers(this);
		//glFinish();
		//repaint();
		//glBindTexture(GL_TEXTURE_2D, 0);
	}

};

#endif // OGLWIDGET_H
