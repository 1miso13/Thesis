#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>

class OGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit OGLWidget(QWidget *parent = nullptr);

};

#endif // OGLWIDGET_H
