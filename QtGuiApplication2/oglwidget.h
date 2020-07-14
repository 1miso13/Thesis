#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
//#include <iostream>
#include "ParametricModel.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>



class OGLWidget : public QOpenGLWidget
{
	Q_OBJECT

		ParametricModel * paramModel;
public:
    explicit OGLWidget(QWidget *parent = nullptr);

	 void initializeGL() {
		 paramModel->InitRenderer();
		 paramModel->SetBackgroundColor(1, 1, 1, 0.5f);
		 drawTimer = new QTimer(this);
		 connect(drawTimer, SIGNAL(timeout()), this, SLOT(update()));
		 drawTimer->start();
	}
	 void setParamModel(ParametricModel * paramModel) {
		 this->paramModel = paramModel;
	 }
	void resizeGL(int w, int h) {

	}
	void paintGL() {
		

		paramModel->BuildModel();
		paramModel->SetRendererCameraRotation(Pitch, Yaw, 0);
		paramModel->SetRendererCameraPosition(positionX, positionY, distance);
		// Draw
		paramModel->Draw(0,0,45,width(), height());
	}
	void mousePressEvent(QMouseEvent* event)
	{
		x = event->x();
		y = event->y();
	}
	void mouseMoveEvent(QMouseEvent* event)
	{
		if (event->buttons() & Qt::LeftButton)
		{
			Yaw -= (float)(x - event->x()) / 500.f;
			Pitch -= (float)(y - event->y()) / 500.f;

			x = event->x();
			y = event->y();
		}
		if (event->buttons() & Qt::RightButton)
		{
			//lookAtX, 0:, 10 : lookAtDistance
			float winX = this->mapFromGlobal(QCursor::pos()).x() - this->width()/2;
			float winY = this->mapFromGlobal(QCursor::pos()).y() - this->height()/2;
			paramModel->SetRefValue("lookAtX", winX / 50.f * lookAtPointDistance/10);
			paramModel->SetRefValue("lookAtY", -winY / 50.f *lookAtPointDistance/10);
		}
	}
	void wheelEvent(QWheelEvent *event)
	{
		if (event->modifiers() & Qt::ControlModifier)
		{
			distance -= event->delta() / 5000.f*distance;
		}
		else
		{
			lookAtPointDistance -= event->delta() / 500.f*lookAtPointDistance;
			paramModel->SetRefValue("lookAtDistance", lookAtPointDistance);

			float winX = this->mapFromGlobal(QCursor::pos()).x() - this->width() / 2;
			float winY = this->mapFromGlobal(QCursor::pos()).y() - this->height() / 2;
			paramModel->SetRefValue("lookAtX", winX / 50.f * lookAtPointDistance / 10);
			paramModel->SetRefValue("lookAtY", -winY / 50.f *lookAtPointDistance / 10);
		}
	}
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
			if (ambientStrength <= 1)
			{
				ambientStrength += 0.1f;
				paramModel->setRendererAmbientStrength(ambientStrength);
			}
			break;
		case Qt::Key_O:
			if (ambientStrength >= 0)
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
	int x = 0;
	int y = 0;
	float Pitch = 0;
	float Yaw = 0;
	float distance = -10;
	float positionX = 0;
	float positionY = 0;
	float ambientStrength = 0.3f;
	QTimer *drawTimer;
	float lookAtPointDistance = 10;
};

#endif // OGLWIDGET_H
