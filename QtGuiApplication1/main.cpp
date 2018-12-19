#include "QtGuiApplication1.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//QOpenGLWidget https://bugreports.qt.io/browse/QTBUG-66915
	a.setAttribute(Qt::AA_DisableShaderDiskCache);
	QtGuiApplication1 w;
	w.show();
	return a.exec();
}
