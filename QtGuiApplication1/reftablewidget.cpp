#include "reftablewidget.h"

void RefTableWidget::Move(size_t index ,bool up) {
	//GET
	QList<QTableWidgetItem*> rowItems1;
	QList<QTableWidgetItem*> rowItems2;
	size_t secIndex = up? index - 1 : index + 1;
	for (int col = 0; col < columnCount(); ++col)
	{
		rowItems1 << takeItem(index, col);
		rowItems2 << takeItem(secIndex, col);
	}

	//SET
	for (int col = 0; col < columnCount(); ++col)
	{
		setItem(index, col, rowItems2.at(col));
		setItem(secIndex, col, rowItems1.at(col));
	}
	//move current item
	
	this->setCurrentCell(this->currentIndex().row() + (up ? -1 : 1), this->currentIndex().column());
}

void RefTableWidget::RefillRefTable(ParametricModel *paramModel)
{
	//clear all
	this->setRowCount(0);
	size_t count = paramModel->paramRef.paramRefVec.size();
	std::vector <paramRefStruct> * paramRefVec = &paramModel->paramRef.paramRefVec;
	std::string value = "";
	for (size_t i = 0; i < count; i++)
	{
		//find value 
		for (size_t j = 0; j < paramModel->GraphCommand.size(); j++)
		{

			if (paramModel->GraphCommand.at(j)->name == paramRefVec->at(i).ObjectName)
			{
				value = paramModel->GraphCommand.at(j)->CommandParameterVector->at(paramRefVec->at(i).paramindex);
				break;
			}
		}
		insertRow(rowCount());
		QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(paramRefVec->at(i).refName), QTableWidgetItem::Type);
		item->setFlags(item->flags() ^ Qt::ItemIsEditable);
		item->setBackgroundColor(QColor(100, 200, 100));
		setItem(rowCount() - 1, 0, item);
		QTableWidgetItem *item2 = new QTableWidgetItem(QString::fromStdString(value), QTableWidgetItem::Type);
		item2->setBackgroundColor(QColor(255, 255, 255));
		setItem(rowCount() - 1, 1, item2);
		QTableWidgetItem *item3 = new QTableWidgetItem(QString::fromStdString(paramRefVec->at(i).ObjectName), QTableWidgetItem::Type);
		item3->setFlags(item3->flags() ^ Qt::ItemIsEditable);
		item3->setBackgroundColor(QColor(100, 200, 100));
		setItem(rowCount() - 1, 2, item3);
		QTableWidgetItem *item4 = new QTableWidgetItem(QString::number(paramRefVec->at(i).paramindex), QTableWidgetItem::Type);
		item4->setFlags(item4->flags() ^ Qt::ItemIsEditable);
		item4->setBackgroundColor(QColor(100, 200, 100));
		setItem(rowCount() - 1, 3, item4);
	}
	repaint();
}

RefTableWidget::RefTableWidget(QWidget *parent) : QTableWidget(parent)
{
}