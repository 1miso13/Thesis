#include "QtGuiApplication2.h"
#include "ParametricModel.h"

QtGuiApplication2::QtGuiApplication2(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.openGLWidget->setParamModel(&paramModel);
}
