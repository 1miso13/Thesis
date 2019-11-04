#include "QtGuiApplication2.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setAttribute(Qt::AA_DisableShaderDiskCache);
	QtGuiApplication2 w;
	w.show();
	return a.exec();
}
