#ifndef OGLWIDGET_H
#define OGLWIDGET_H


#include <QOpenGLWidget>
#include <iostream>
#include "ParametricModel.h"
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>

class OGLWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
    explicit OGLWidget(QWidget *parent = nullptr);

	ParametricModel * paramModel;
	void setParamModel(ParametricModel * paramModel) {
		this->paramModel = paramModel;
	}
	int x = 0;
	int y = 0;
	float Pitch = 0;
	float Yaw = 0;
	float distance = -10;
	float positionX=0;
	float positionY=0;
	void mousePressEvent(QMouseEvent* event)
	{
		x = event->x();
		y = event->y();
	}
	void mouseMoveEvent(QMouseEvent* event)
	{
		if (event->buttons() & Qt::LeftButton)
		{
			Yaw  -= (float)(x - event->x()) / 500.f;
			Pitch -= (float)(y - event->y()) /500.f;

			x = event->x();
			y = event->y();
		}
	}
	void wheelEvent(QWheelEvent *event)
	{
		/*if (event->modifiers().testFlag(Qt::ControlModifier))
		{*/
		distance -= event->delta()/5000.f*distance;
		
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

	void paintGL() {

		/*
		paramModel->SetRendererCameraRotation(sin(time) * 3.14f / 5.0f, time, 0);*/
		paramModel->SetRendererCameraRotation(Pitch, Yaw, 0);
		paramModel->SetRendererCameraPosition(positionX, positionY,distance);
		// Draw
		paramModel->Draw(0,0,120,width(), height());

		
	}
	float ambientStrength = 0.3f;
	void keyPressEvent(QKeyEvent* event)
	{
		switch (event->key())
		{
		case Qt::Key_W:
		case Qt::Key_Up:
			if (event->modifiers() & Qt::ShiftModifier)
				positionY += 0.1f;
			else
				Pitch += 0.1f;
			break;
		case Qt::Key_S:
		case Qt::Key_Down:
			if (event->modifiers() & Qt::ShiftModifier)
				positionY -= 0.1f;
			else
				Pitch -= 0.1f;
			break;
		case Qt::Key_A:
		case Qt::Key_Left:
			if (event->modifiers() & Qt::ShiftModifier)
				positionX += 0.1f;
			else
				Yaw += 0.1f;
			break;
		case Qt::Key_D:
		case Qt::Key_Right:
			if (event->modifiers() & Qt::ShiftModifier)
				positionX -= 0.1f;
			else
				Yaw -= 0.1f;
			break;
		case Qt::Key_Z:
			distance -= 0.1f;
			break;
		case Qt::Key_X:
			distance += 0.1f;
			break;
		case Qt::Key_P:
			if (ambientStrength>=0)
			{
				ambientStrength += 0.1f;
				paramModel->setRendererAmbientStrength(ambientStrength);
			}
			break;
		case Qt::Key_O:
			if (ambientStrength<=1)
			{
				ambientStrength -= 0.1f;
				paramModel->setRendererAmbientStrength(ambientStrength);
			}
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
