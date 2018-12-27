#include "dialog.h"
#include "GeneratedFiles/ui_dialog.h"
#include "Header.h"

Dialog::Dialog(CommandStack *commandStack, Command ** c, DialogWindowType DialogType, int index, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
	this->setWindowFlags(this->windowFlags() | Qt::WindowMinMaxButtonsHint);
	this->index = index;
	this->commandStack = commandStack;
	this->DialogType = DialogType;
   // ui->splitter->setSizes(QList<int>() << 200 << 100 );
	this->c = c;
	//ui->buttonBox->setEnabled(false);
	FillCommandList();
	if (DialogType == DialogWindowType::MODIFY)
	{
		int operType = commandStack->GraphCommand.at(index)->operationType;
		int paramType = commandStack->GraphCommand.at(index)->typeOfParameters-1;
		size_t i = 0;
		for (; i < CommandsVec.size(); i++)
		{
			if (CommandsVec.at(i).operationID==operType && CommandsVec.at(i).ParameterID == paramType)
			{
				break;
			}
		}
		//modify existing command
		ui->treeWidget->setCurrentItem(ui->treeWidget->topLevelItem(i),    // item
			0,                          // column
			QItemSelectionModel::Select // command
		);
	}
	else
	{
		//new Command
	}
	//ui->tableWidget->setItem(0, 1, new QTableWidgetItem("dvddfvdvsd"));
}

Dialog::~Dialog()
{
    delete ui;
}

void ClearParamVectors(std::vector <
	std::vector<
	operationType::ParameterTypesEnum
	>*
>** paramVectors) {
	for (size_t i = 0; i < (*paramVectors)->size(); i++)
	{
		delete (*paramVectors)->at(i);
	}
	delete (*paramVectors);
}
void Dialog::FillCommandList()
{
	
	for (size_t i=0; i != operationType::INVALID; i++) {

		std::string operationName = operationType::OperationToString((operationType::OperationTypeEnum) i);
		std::vector<std::vector<std::string>*> *paramInfo;
		operationType::GetOperationParameters(operationName,
			&paramVectors, &paramInfo, true);

		for (size_t j = 0; j < paramVectors->size(); j++)
		{
			std::string s = ""; 
			bool first = true;
			for (size_t k = 0; k < paramVectors->at(j)->size(); k++)
			{
				 s += (first?"":", ") + operationType::ParameterToString(paramVectors->at(j)->at(k));
				 first = false;
			}
			CommandStruct c;
			c.operationID = i;
			c.ParameterID = j;
			c.operationName = operationName;
			c.parameterList = s;
			c.Info = paramInfo->at(j)->at(0);
			CommandsVec.push_back(c);
		}
		ClearParamVectors(&paramVectors);
	}	
	for (size_t i = 0; i < CommandsVec.size(); i++)
	{
		QTreeWidgetItem *qTreeWidgetItemRoot = new QTreeWidgetItem(ui->treeWidget);
		// Add it on our tree as the top item.
		ui->treeWidget->addTopLevelItem(qTreeWidgetItemRoot);
		//command name
		qTreeWidgetItemRoot->setText(0, QString::number(CommandsVec.at(i).operationID) + ":" + QString::number(CommandsVec.at(i).ParameterID));
		qTreeWidgetItemRoot->setText(1, QString::fromStdString(CommandsVec.at(i).operationName));
		qTreeWidgetItemRoot->setText(2, QString::fromStdString(CommandsVec.at(i).parameterList));
		qTreeWidgetItemRoot->setText(3, QString::fromStdString(CommandsVec.at(i).Info));
	}
}
/// <summary>
/// Parameters table
/// </summary>
void Dialog::on_treeWidget_itemSelectionChanged()
{

	auto c = CommandsVec.at(ui->treeWidget->currentIndex().row());
	bool modif = false;
	if (DialogType == DialogWindowType::MODIFY)
	{//Modify
		if (c.operationID == commandStack->GraphCommand.at(index)->operationType && c.ParameterID == commandStack->GraphCommand.at(index)->typeOfParameters - 1)
		{
			modif = true;
		}
	}

	



	std::vector<std::vector<std::string>*> *paramInfo;
	operationType::GetOperationParameters(c.operationName,
		&paramVectors, &paramInfo, true);



	std::vector <std::string> *f = paramInfo->at(c.ParameterID);
	std::vector <operationType::ParameterTypesEnum> * sasa = paramVectors->at(c.ParameterID);


	//reset table
	ui->tableWidget->setRowCount(0);

	//Name Of Object
	std::string objectName = c.operationName + "_" + std::to_string(commandStack->GraphCommand.size());
	if (modif)
	{
		objectName = commandStack->GraphCommand.at(index)->name;
	}
	ui->tableWidget->insertRow(ui->tableWidget->rowCount());
	QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString("Name"), QTableWidgetItem::Type);
	item->setFlags(item->flags() ^ Qt::ItemIsEditable);
	item->setBackgroundColor(QColor(100, 200, 100));
	ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, item); 
	QTableWidgetItem *item2 = new QTableWidgetItem(QString::fromStdString(objectName), QTableWidgetItem::Type);
	item2->setBackgroundColor(QColor(100, 200, 100));
	ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, item2);
	QTableWidgetItem *item3 = new QTableWidgetItem(QString::fromStdString("-"), QTableWidgetItem::Type);
	item3->setFlags(item3->flags() ^ Qt::ItemIsEditable);
	item3->setBackgroundColor(QColor(100, 200, 100));
	ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, item3);
	QTableWidgetItem *item4 = new QTableWidgetItem(QString::fromStdString("Object name. By this name, can be object refferenced"), QTableWidgetItem::Type);
	item4->setFlags(item4->flags() ^ Qt::ItemIsEditable);
	item4->setBackgroundColor(QColor(100, 200, 100));
	ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, item4);
	ui->tableWidget->repaint();


	//Visibility
	ui->tableWidget->insertRow(ui->tableWidget->rowCount());
	QTableWidgetItem *itemVisib = new QTableWidgetItem(QString::fromStdString("Visibility"), QTableWidgetItem::Type);
	itemVisib->setFlags(itemVisib->flags() ^ Qt::ItemIsEditable);
	itemVisib->setBackgroundColor(QColor(100, 150, 100));
	ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, itemVisib);
	std::string visibilityVal="";
	if (modif)
	{
		visibilityVal = std::to_string(commandStack->GraphCommand.at(index)->visibility);
	}
	else
	{
		visibilityVal = "1";
	}
	QTableWidgetItem *itemVisib2 = new QTableWidgetItem(QString::fromStdString(visibilityVal), QTableWidgetItem::Type);
	itemVisib2->setBackgroundColor(QColor(255, 255, 255));
	ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, itemVisib2);
	QTableWidgetItem *itemVisib3 = new QTableWidgetItem(QString::fromStdString("-"), QTableWidgetItem::Type);
	itemVisib3->setFlags(itemVisib3->flags() ^ Qt::ItemIsEditable);
	itemVisib3->setBackgroundColor(QColor(100, 150, 100));
	ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, itemVisib3);
	QTableWidgetItem *itemVisib4 = new QTableWidgetItem(QString::fromStdString("Object visibility. [0 - invisible, 1 - fully visible]"), QTableWidgetItem::Type);
	itemVisib4->setFlags(itemVisib4->flags() ^ Qt::ItemIsEditable);
	itemVisib4->setBackgroundColor(QColor(100, 150, 100));
	ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, itemVisib4);
	ui->tableWidget->repaint();

	//Parameters
	for (size_t i = 0; i < sasa->size(); i++)
	{
		ui->tableWidget->insertRow(ui->tableWidget->rowCount());
		QTableWidgetItem *item = new QTableWidgetItem(QString::fromStdString(operationType::ParameterToString(sasa->at(i))), QTableWidgetItem::Type);
		item->setFlags(item->flags() ^ Qt::ItemIsEditable);   
		item->setBackgroundColor(QColor(200, 200, 200));
		ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, item);
		std::string paramValueStr = "";
		if (modif)
		{
			//add existing value
			paramValueStr = commandStack->GraphCommand.at(index)->CommandParameterVector->at(i);
			if (sasa->at(i) ==operationType::ParameterTypesEnum::ParameterTypeMULTIPLEPOINTS)
			{
				/// <summary>
				/// all parameters are merged to this param, delimited with ';'
				/// </summary>
				for (size_t j = i+1; j < commandStack->GraphCommand.at(index)->CommandParameterVector->size(); j++)
				{
					paramValueStr += ";" + commandStack->GraphCommand.at(index)->CommandParameterVector->at(j);
				}
			}
		}
		QTableWidgetItem *itemValue = new QTableWidgetItem(QString::fromStdString(paramValueStr), QTableWidgetItem::Type);
		ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, itemValue);

		QTableWidgetItem *item2 = new QTableWidgetItem(QString::fromStdString(""), QTableWidgetItem::Type);
		if (sasa->at(i) != operationType::ParameterTypesEnum::ParameterTypeFLOAT)
		{
			item2->setFlags(item2->flags() ^ Qt::ItemIsEditable);
			item2->setBackgroundColor(QColor(200, 200, 200));
			item2->setText(QString::fromStdString("-"));
		}
		else
		{//test if param is referenced
			std::string paramRefName;
			if (commandStack->paramRef.FindRefParameterByObjectAndIndex(objectName, i, &paramRefName))
			{
				item2->setText(QString::fromStdString(paramRefName));
			} 
			
			//= !commandStack->TestRefParam(commandStack->paramRef.FindRefParameterByObject(), objectName, i);
		}
		ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, item2);
		QTableWidgetItem *item3 = new QTableWidgetItem(QString::fromStdString(f->at(i + 1)), QTableWidgetItem::Type);
		item3->setFlags(item3->flags() ^ Qt::ItemIsEditable);
		item3->setBackgroundColor(QColor(200, 200, 200));
		ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, item3);
		ui->tableWidget->repaint();
	}

	//unlock OK button
	ui->okButton->setEnabled(true);
}
bool IsEmpty(std::string cellText) {
	bool empty=true;
	for (size_t i = 0; i < cellText.length(); i++)
	{
		if (!isspace(cellText[i]))
		{
			empty = false;
		}
	}
	return empty;
}
/// <summary>
/// DO NOT USE!
/// </summary>
/// <param name="current"></param>
/// <param name="previous"></param>
void Dialog::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
	//reaguje na kazde klikutie, aj v rovnakom riadku!!!
}
void Dialog::Clean() {
	//clean TODO
}
/// <summary>
/// Cancel button
/// </summary>
void Dialog::on_cancelButton_clicked()
{
	Clean();
	this->reject();
}
/// <summary>
/// OK button
/// </summary>
void Dialog::on_okButton_clicked()
{

	//get values
	/*for (size_t i = 0; i < length; i++)
	{
		ui->tableWidget->item(0, 0)->text().toStdString();
	}*/



	//test valid parameters
	bool validParameters = true;
	
	CommandStruct cStruct = CommandsVec.at(ui->treeWidget->currentIndex().row());
	std::vector <operationType::ParameterTypesEnum> * k = paramVectors->at(cStruct.ParameterID);
	//Test name 
	bool validName = true;
	std::string objectName = ui->tableWidget->item(0, 1)->text().toStdString();
	if (IsEmpty(objectName))
	{
		validName = false;
	}
	else
	{
		for (size_t i = 0; i < commandStack->GraphCommand.size(); i++)
		{
			if (DialogType == DialogWindowType::MODIFY && i == index)
			{//jump now editing command
				continue;
			}
			if (commandStack->GraphCommand.at(i)->name == objectName)
			{
				validName = false;
				break;
			}
		}
	}


	std::string visibilityValue = ui->tableWidget->item(1, 1)->text().toStdString();
	if (validName)
	{
		//visibility
		validParameters = operationType::TestValidParameterType(operationType::ParameterTypesEnum::ParameterTypeFLOAT, visibilityValue, &commandStack->GraphCommand, index);
		//Test parameters
		for (size_t i = 0; i < k->size(); i++)
		{
			std::string cellText = ui->tableWidget->item(i+2, 1)->text().toStdString();
			if (!operationType::TestValidParameterType(k->at(i), cellText, &commandStack->GraphCommand, index))
			{
				validParameters = false;
			}
			if (k->at(i) == operationType::ParameterTypesEnum::ParameterTypeFLOAT)
			{
				std::string refname= ui->tableWidget->item(i + 2, 2)->text().toStdString();
				for (size_t j = 0; j < ui->tableWidget->rowCount()-2; j++)
				{
					if (j != i && refname == ui->tableWidget->item(j+2, 2)->text().toStdString() && !IsEmpty(refname))
					{//same as another parameter
						validParameters = false;
					}
				}
				if (!commandStack->TestRefParam(refname, objectName, i) && !IsEmpty(refname)) {
					validParameters = false;
				}
			}
		}
	}
	//test
	if (!validParameters || !validName)
	{
		QMessageBox msgBox;
		msgBox.setText("Error");
		msgBox.setInformativeText("Some values are not valid");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setDefaultButton(QMessageBox::Ok);
		int ret = msgBox.exec();
		return;
	}
	std::vector <std::string> * commandParamVec= new std::vector <std::string>();
	for (size_t i = 0; i < k->size(); i++)
	{
		if (paramVectors->at(cStruct.ParameterID)->at(i) == operationType::ParameterTypesEnum::ParameterTypeMULTIPLEPOINTS)
		{//point1;point2;point3;point4;...;pointN
			/// parse
			std::string toParse = (ui->tableWidget->item(i + 2, 1)->text().toStdString());
			size_t pos = 0;
			std::string token;
			while ((pos = toParse.find(';')) != std::string::npos) {
				token = toParse.substr(0, pos);
				commandParamVec->push_back(token);
				toParse.erase(0, pos + 1);
			}
			commandParamVec->push_back(toParse);
		}
		else
		{
			/// push to vector
			commandParamVec->push_back(ui->tableWidget->item(i + 2, 1)->text().toStdString());
			/// <summary>
			/// Add param reference
			/// </summary>
			if (k->at(i) == operationType::ParameterTypesEnum::ParameterTypeFLOAT)
			{
				std::string paramRefName;
				if(!IsEmpty(paramRefName = ui->tableWidget->item(i + 2, 2)->text().toStdString()))
					commandStack->AddReferenceParamWithoutValidCheck(paramRefName, objectName, i);
				else
				{
					commandStack->RemoveReferenceParam(objectName, i);
				}
			}
		}
	}

	*c = new Command(objectName, std::stof(visibilityValue),(operationType::OperationTypeEnum)cStruct.operationID,commandParamVec,cStruct.ParameterID+1);

	//clean
	Clean();
    this->accept();
}
void Dialog::on_tableWidget_cellChanged(int row, int column)
{
	ui->tableWidget->item(row, column)->setText(QString::fromStdString(RemoveWhitespaceChars(ui->tableWidget->item(row, column)->text().toStdString())));
	//1 - param value
	//2 - ref param name
	if (column != 1 && column != 2 )
	{
		return;
	}
	if (column == 2 && row >= 2 && (paramVectors->at(CommandsVec.at(ui->treeWidget->currentIndex().row()).ParameterID)->at(row - 2) != operationType::ParameterTypesEnum::ParameterTypeFLOAT))
	{
		return;
	}
	short retType = 1;
	std::string cellText = RemoveWhitespaceChars(ui->tableWidget->item(row, column)->text().toStdString());
	if (IsEmpty(cellText) )
	{
		
		retType = 2;
	}
	else 
	{
		if (column == 1)
		{

			if (row == 0)
			{//name
				//test if name doesnt already exist
				retType = 1;
				for (size_t i = 0; i < commandStack->GraphCommand.size(); i++)
				{
					if (DialogType == DialogWindowType::MODIFY && i == index)
					{//jump now editing command
						continue;
					}
					if (commandStack->GraphCommand.at(i)->name == cellText)
					{
						retType = 0;
						break;
					}
				}
			}
			else {
				if (row == 1)
				{//visibility
					retType = operationType::TestValidParameterType(operationType::ParameterTypeFLOAT, cellText, &commandStack->GraphCommand, index);
				}
				else
				{
					//test valid parameter
					CommandStruct c = CommandsVec.at(ui->treeWidget->currentIndex().row());
					std::vector <operationType::ParameterTypesEnum> *  k = paramVectors->at(c.ParameterID);
					//	for (size_t i = 0; i < k->size(); i++)
					{
						//operationType::CompareTypes(k->at(i), operationType::Find(&(commandStack->GraphCommand), cellText));
						retType = operationType::TestValidParameterType(k->at((size_t)(row - 2)), cellText, &commandStack->GraphCommand, index);
						//k->at(i);
					}

				}
			}

		}
		else {//column == 2
			std::string objectName = ui->tableWidget->item(0, 1)->text().toStdString();
			for (size_t i = 2; i < ui->tableWidget->rowCount(); i++)
			{
				if (i!=row && cellText == ui->tableWidget->item(i, 2)->text().toStdString() && cellText!="")
				{
					retType = false;
				}
			}
			retType = commandStack->TestRefParam(cellText, objectName, (size_t)(row - 2)) && retType;
		}
	}
	switch (retType)
	{
	case 0:
		//Invalid
		ui->tableWidget->item(row, column)->setBackgroundColor(QColor(200, 0, 0));
		break;
	case 1:
		//Is valid
		ui->tableWidget->item(row, column)->setBackgroundColor(QColor(0, 200, 0));
		break;
	case 2:
		//not set
		ui->tableWidget->item(row, column)->setBackgroundColor(QColor(255, 255, 255));
		break;
	default:
		break;
	}
	
}
