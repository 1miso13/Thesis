#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication2.h"
#include "ParametricModel.h"

class QtGuiApplication2 : public QMainWindow
{
	Q_OBJECT

private:
	ParametricModel paramModel;
public:
	QtGuiApplication2(QWidget *parent = Q_NULLPTR);
private:
	Ui::QtGuiApplication2Class ui;
	QTimer* updateTimer;
	void initValues();
public Q_SLOTS:
	void updateFunc();
};
