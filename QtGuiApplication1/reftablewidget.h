#pragma once
#include <QTableWidget>
#include <QLineEdit>
#include "../Thesis/CommandStack.h"
class RefTableWidget :
	public QTableWidget
{
	Q_OBJECT
public:
	void Move(size_t index, bool up);
	void RefillRefTable(CommandStack *commandStack);
	explicit RefTableWidget(QWidget *parent = nullptr);
};

