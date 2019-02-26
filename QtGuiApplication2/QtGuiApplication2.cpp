#include "QtGuiApplication2.h"
#include "ParametricModel.h"

ParametricModel QtGuiApplication2::paramModel;
QtGuiApplication2::QtGuiApplication2(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}
