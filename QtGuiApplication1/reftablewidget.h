#pragma once
#include <QTableWidget>
#include <QLineEdit>
#include "../Thesis/ParametricModel.h"
class RefTableWidget :
	public QTableWidget
{
	Q_OBJECT
public:
	void Move(size_t index, bool up);
	void RefillRefTable(ParametricModel *paramModel);
	explicit RefTableWidget(QWidget *parent = nullptr);
};

