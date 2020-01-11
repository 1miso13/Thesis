#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
#include <iostream>
#include "ParametricModel.h"



class OGLWidget : public QOpenGLWidget
{
	Q_OBJECT

		ParametricModel * paramModel;
public:
    explicit OGLWidget(QWidget *parent = nullptr);

	 void initializeGL() {
		 paramModel->InitRenderer();
	}
	 void setParamModel(ParametricModel * paramModel) {
		 this->paramModel = paramModel;
	 }
	void resizeGL(int w, int h) {

	}
	void paintGL() {

		// Draw
		paramModel->Draw(0,0,45,width(), height());
	}

};

#endif // OGLWIDGET_H
