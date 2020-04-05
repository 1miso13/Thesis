#include "QtGuiApplication2.h"
#include "ParametricModel.h"
#include <fstream>

QtGuiApplication2::QtGuiApplication2(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);


	std::ifstream file("head.parammodel");
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	paramModel.AddOperations(content);
	ui.openGLWidget->setParamModel(&paramModel);



	updateTimer = new QTimer(this);
	connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateFunc()));
	updateTimer->start();

	paramModel.BuildModel();
	initValues();
}
void QtGuiApplication2::initValues() {
	ui.horizontalSlider->setValue(paramModel.GetObjectValue("head.radius") * 100 / 4);
	float tmp = paramModel.GetObjectValue("param1.x"/*earSize*/) * 100;
	ui.horizontalSlider_2->setValue(tmp);
	tmp = paramModel.GetObjectValue("paramEyes2.x"/*eyeSize*/) * 100;
	ui.horizontalSlider_3->setValue(tmp);

	Object::Point * a = (Object::Point*)paramModel.GetObject("paramEyes");
	ui.horizontalSlider_4->setValue(a->Position.X *100 / (3.14 / 4));//eyesWidth
	ui.horizontalSlider_5->setValue(a->Position.Y *100 / (3.14 / 4));//eyesHeight

	tmp = paramModel.GetObjectValue("param1.y"/*earDistance*/) * 100;
	ui.horizontalSlider_6->setValue(tmp / (3.14 / 2));
	
}

void QtGuiApplication2::updateFunc() {
	float a = ui.horizontalSlider->value();
	paramModel.SetRefValue("headSize", a / 100 * 4);
	float b = ui.horizontalSlider_2->value();
	paramModel.SetRefValue("earSize", b / 100);
	float c = ui.horizontalSlider_3->value();
	paramModel.SetRefValue("eyeSize", c / 100);
	float eyesWidth = ui.horizontalSlider_4->value();
	paramModel.SetRefValue("eyesWidth", eyesWidth / 100 * 3.14 / 4);
	float eyesHeight = ui.horizontalSlider_5->value();
	paramModel.SetRefValue("eyesHeight", eyesHeight / 100 * 3.14 / 4);
	float earDistance = ui.horizontalSlider_6->value();
	paramModel.SetRefValue("earDistance", earDistance / 100 * 3.14 / 2);

}