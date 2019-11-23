#include "oglwidget.h"

OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	setFocusPolicy(Qt::StrongFocus);
	setMouseTracking(true);
}
