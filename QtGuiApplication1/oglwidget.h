#ifndef OGLWIDGET_H
#define OGLWIDGET_H


#include <QOpenGLWidget>
#include <iostream>
#include "ParametricModel.h"
#include <QTimer>
#include <QKeyEvent>

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
		drawTimer = new QTimer(this);
		connect(drawTimer, SIGNAL(timeout()), this, SLOT(update()));
		drawTimer->start();

	}
	virtual void resizeGL(int w, int h) {

	}
	float time = 0;
	float rotationP = 0;
	bool rotationTimer = false;;
	float distance=0;

	void paintGL() {

		/*time += 0.001f;
		if (rotationTimer && time> rotationP)
		{
			time = 0;
			rotationP += 0.1f;
		}
		paramModel->SetRendererCameraRotation(sin(time) * 3.14f / 5.0f, time, 0);*/
		paramModel->SetRendererCameraRotation(sin(time) * 3.14f / 5.0f, rotationP, 0);
		paramModel->SetRendererCameraPosition(0,0,-10+distance);
		// Draw
		float aspect = (float)width() / (float)height();
		//QtGuiApplication1::paramModel.Draw(aspect);
		paramModel->Draw(aspect,45);

		
	}
	void keyPressEvent(QKeyEvent* event)
	{
		switch (event->key())
		{
		case Qt::Key_W:
		case Qt::Key_Up:
			break;
		case Qt::Key_S:
		case Qt::Key_Down:
			break;
		case Qt::Key_Q:
		case Qt::Key_Left:
			rotationTimer = true;
			rotationP += 0.1f;
			break;
		case Qt::Key_E:
		case Qt::Key_Right:
			rotationTimer = true;
			rotationP -= 0.1f;
			break;
		case Qt::Key_Z:
			distance -= 0.1f;
			break;
		case Qt::Key_X:
			distance+=0.1f;
			break;
		default:
			event->accept();
			break;
		}
		
	}
private:
	
	QTimer *drawTimer;
};

#endif // OGLWIDGET_H
