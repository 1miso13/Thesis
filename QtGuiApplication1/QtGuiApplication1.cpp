#include "QtGuiApplication1.h"
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include "dialog.h"
#include "../Thesis/CommandStack.h"
#include "../Thesis/OperationTypes.h"
#include "DialogWindowType.h"
#include <qgraphicsscene.h>

CommandStack commandStack;
QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}
bool IsNotEmpty(std::string s)
{
	bool isNotEmpty = false;
	for (size_t i = 0; i < s.length(); i++)
	{
		if (!isspace (s[i]))
		{
			isNotEmpty = true;
		}
	}
	return isNotEmpty;
}
void ParseCommands(std::vector<std::string>* commandsVec, std::string s) {
	std::string delimiter = ";";
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		s.erase(0, pos + delimiter.length());
		if (IsNotEmpty(token))
		{
			(*commandsVec).push_back(token);
		}
	}if (IsNotEmpty(s))
	{
		(*commandsVec).push_back(s);
	}
}
void CommandToQStrings(Command *c, QTreeWidgetItem* qTreeWidgetItem) {
	// 0 - Operation Name
	qTreeWidgetItem->setText(0, QString::fromStdString(operationType::OperationToString(c->operationType)));
	// 1 - Command Name
	qTreeWidgetItem->setText(1, QString::fromStdString(c->name));
	// 2 - Visibility
	qTreeWidgetItem->setText(2, QString::number(c->visibility));

	std::vector <
		std::vector<
		operationType::ParameterTypesEnum
		>*
	>* paramVectors = NULL;
	operationType::GetOperationParameters(
		operationType::OperationToString(c->operationType),
		&paramVectors/*contain vector of parameters*/
	);
	size_t typeOfParameters = c->typeOfParameters - 1;

	auto l = (paramVectors)->at(typeOfParameters);
	std::string commandParameters = ParameterToString(l->at(0)) + " " + c->CommandParameterVector->at(0);
	for (size_t i = 1; i < c->CommandParameterVector->size(); i++)
	{
		std::string parameterType = c->operationType == operationType::Shape ? "POINT" : ParameterToString(l->at(i));
		commandParameters = commandParameters + ",\t" + parameterType + " " + c->CommandParameterVector->at(i);
	}
	// 3 - Parameters
	qTreeWidgetItem->setText(3, QString::fromStdString(commandParameters));
}
/// <summary>
/// Push button
/// </summary>
void QtGuiApplication1::on_pushButton_clicked()
{
   auto s = ui.lineEdit->text();


   std::vector<std::string> commandsVec;
   ParseCommands(&commandsVec, s.toStdString());

   for (size_t i = 0; i < commandsVec.size(); i++)
   {

	   if (commandStack.AddCommand(commandsVec.at(i)))
	   {
		   ui.lineEdit->setStyleSheet("color: #00FF00");

		   size_t commandID = commandStack.GraphCommand.size() - 1;
		   // Create new item (top level item)
		   QTreeWidgetItem *qTreeWidgetItem = new QTreeWidgetItem(ui.treeWidget);
		   // Add it on our tree as the top item.
		   ui.treeWidget->addTopLevelItem(qTreeWidgetItem);
	   
		   CommandToQStrings(commandStack.GraphCommand[commandID], qTreeWidgetItem);
	   }

   }
   ui.RefParam_tableWidget->RefillRefTable(&commandStack);
}
/*
void QtGuiApplication1::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    item->setText(item->text()+"ng");
}*/

void QtGuiApplication1::on_actionHelp_triggered()
{

}

void QtGuiApplication1::on_actionQuit_triggered()
{
	QtGuiApplication1::close();
}

void QtGuiApplication1::on_actionAdd_triggered()
{//add new command
	Command *c;
	Dialog dialog(&commandStack, &c, DialogWindowType::NEW, -1/*new*/, this);
	dialog.setModal(true);
	dialog.setWindowTitle("New command");
	if (dialog.exec())
	{//OK 
		
		// Create new item (top level item)
		QTreeWidgetItem *qTreeWidgetItem = new QTreeWidgetItem(ui.treeWidget);
		// Add it on our tree as the top item.
		ui.treeWidget->addTopLevelItem(qTreeWidgetItem);

		commandStack.AddCommand(c);
		CommandToQStrings(c, qTreeWidgetItem);
		
	}
}

void QtGuiApplication1::on_actionDelete_triggered()
{
	if ((ui.treeWidget->currentItem() != NULL))
	{
		on_DeleteButton_clicked();
	}
}

void QtGuiApplication1::on_actionDelete_all_triggered()
{
	while (ui.treeWidget->topLevelItemCount() > 0)
	{

		size_t index = 0;
		//delete
		delete ui.treeWidget->takeTopLevelItem(index);
		commandStack.RemoveCommand(index);
		//commandStack.GraphCommand.erase(commandStack.GraphCommand.begin() + index);
		
	}
	DisableButtons();
}

void QtGuiApplication1::on_actionOpen_triggered()
{

}

void QtGuiApplication1::on_actionSave_triggered()
{

}

void QtGuiApplication1::on_actionSave_as_triggered()
{

}

void QtGuiApplication1::on_actionNew_triggered()
{
	on_actionDelete_all_triggered();
}

void QtGuiApplication1::on_actionCommand_list_triggered()
{

}
/// <summary>
/// Command line color
/// </summary>
/// <param name="arg1"></param>
void QtGuiApplication1::on_lineEdit_textEdited(const QString &arg1)
{
	bool noError = true;
	if (arg1.isEmpty())
	{
		return;
	}
	std::vector<std::string> commandsVec;
	ParseCommands(&commandsVec, arg1.toStdString());

	commandStack.resetTest();
	for (size_t i = 0; i < commandsVec.size(); i++)
	{

		if (!commandStack.TestCommand(commandsVec.at(i)))
		{
			noError = false;
		}
	}
	commandStack.resetTest();
	if (noError)
	{
		ui.lineEdit->setStyleSheet("color: #000000");
	}
	else
	{
		ui.lineEdit->setStyleSheet("color: #FF0000");
	}
	ui.pushButton->setEnabled(noError);
}
/// <summary>
/// Create copy of command
/// </summary>
/// <param name="cFROM"></param>
/// <param name="cTO"></param>
void CopyCommand(Command * cFROM, Command *& cTO) {
	std::vector <std::string> * commandParameterVector = new std::vector <std::string>();
	for (size_t i = 0; i < cFROM->CommandParameterVector->size(); i++)
	{
		std::string s = (cFROM->CommandParameterVector)->at(i);
		commandParameterVector->push_back(s);
	}
	cTO = new Command(cFROM->name,cFROM->visibility,cFROM->operationType,commandParameterVector,cFROM->typeOfParameters);
}

/// <summary>
/// Test command referienciesat index
/// </summary>
/// <param name="commandStack">Command list</param>
/// <param name="index">item index</param>
/// <returns>If all referencies in command are valid</returns>
bool TestCommandSemantic(CommandStack *commandStack, size_t index) {
	std::string operationName = operationType::OperationToString(commandStack->GraphCommand.at(index)->operationType);//operationType::OperationToString((operationType::OperationTypeEnum) i);
	std::vector<std::vector<operationType::ParameterTypesEnum>*> *paramVectors;
	operationType::GetOperationParameters(operationName,
		&paramVectors);

	std::vector <operationType::ParameterTypesEnum> * k = paramVectors->at(commandStack->GraphCommand.at(index)->typeOfParameters - 1);
	//Test parameters
	for (size_t i = 0; i < k->size(); i++)
	{
		std::string parameterText = commandStack->GraphCommand.at(index)->CommandParameterVector->at(i);
		if (!operationType::TestValidParameterType(k->at(i), parameterText, &commandStack->GraphCommand, index))
		{
			return false;
		}
	}
	
	return true;
}
void QtGuiApplication1::TestCommandsValidity(size_t indexFrom) {
	size_t countOfInvalid = 0;
	for (size_t i = indexFrom; i < commandStack.GraphCommand.size(); i++)
	{
		//TODO;
		if (!TestCommandSemantic(&commandStack, i))
		{
			countOfInvalid++;
			//set red color on invalid item
			ui.treeWidget->topLevelItem(i)->setBackgroundColor(1, QColor(255, 0, 0));
		}
		else
		{

			ui.treeWidget->topLevelItem(i)->setBackgroundColor(1, QColor(255, 255, 255));
		}
	}
	ReadyToBuild = countOfInvalid == 0;
}
void QtGuiApplication1::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
	QTreeWidgetItem* currentItem = ui.treeWidget->currentItem();
	int index = ui.treeWidget->currentIndex().row();
	Command * c;
	CopyCommand(commandStack.GraphCommand[index], c);
	Dialog dialog(&commandStack, &c, DialogWindowType::MODIFY, index, this);
	dialog.setModal(true);
	dialog.setWindowTitle("Modify command");
	if (dialog.exec())
	{//OK
		//modify commandStack
		if (commandStack.GraphCommand.at(index)->operationType == c->operationType)
		{///Changed value in command
			commandStack.ModifyCommand(index,c);
		}
		else
		{///change whole command
			//delete old command
			commandStack.RemoveCommand(index);
			//delete commandStack.GraphCommand[index];
			//add new command
			commandStack.InsertCommand(index, c);
			//commandStack.GraphCommand[index] = c;		
		}
		//modify tree wiev
		CommandToQStrings(commandStack.GraphCommand[index], currentItem);

		//need to find all missing referencies after index and highlight
		{
			TestCommandsValidity(index);
		}
	}
	else
	{
		delete c;
	}
	
	//test
	TestCommandsValidity(index);

	//currentItem->setText(0,"csc" + QString::number()); ///for testing
}
/// <summary>
/// Insert command after selected item in ui.treeWidget
/// </summary>
void QtGuiApplication1::on_InsertButton_clicked()
{
	int index = ui.treeWidget->currentIndex().row();
	Command *c;
	Dialog dialog(&commandStack, &c, DialogWindowType::INSERT, index/*insert position*/,this);
	dialog.setModal(true);
	dialog.setWindowTitle("Insert command");
	if (dialog.exec())
	{//OK 

		// Create new item (top level item)
		QTreeWidgetItem *qTreeWidgetItem = new QTreeWidgetItem();
		// Add it on our tree as the top item.
		ui.treeWidget->insertTopLevelItem(index,qTreeWidgetItem);

		commandStack.InsertCommand(index,c);
		CommandToQStrings(c, qTreeWidgetItem);
		ui.treeWidget->repaint();

	}
	//ui.treeWidget->topLevelItem(3)->setBackgroundColor(1, QColor(123, 147, 158));
	//test
	TestCommandsValidity(index);
}

void QtGuiApplication1::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
	ui.InsertButton->setEnabled(true);
	ui.DeleteButton->setEnabled(true);
}

void QtGuiApplication1::on_NewButton_clicked()
{
	on_actionAdd_triggered();
}
/// <summary>
/// Delete selected item
/// </summary>
void QtGuiApplication1::on_DeleteButton_clicked()
{
	size_t index = ui.treeWidget->currentIndex().row();
	//delete
	delete ui.treeWidget->takeTopLevelItem(index);
	commandStack.RemoveCommand(index); //.GraphCommand.erase(commandStack.GraphCommand.begin()+index);
	//test
	TestCommandsValidity(index);
	if (ui.treeWidget->topLevelItemCount()==0)
	{
		DisableButtons();
	}
}
/// <summary>
/// Disable Insert and delete buttons
/// </summary>
void QtGuiApplication1::DisableButtons() {
	ui.InsertButton->setEnabled(false);
	ui.DeleteButton->setEnabled(false);
}

void QtGuiApplication1::on_tabWidget_currentChanged(int index){
	switch (index)
	{
	case 0://Commands

		break;
	case 1://Referenced Variables
		//refill ref param list
		ui.RefParam_tableWidget->RefillRefTable(&commandStack);
		break;
	case 2://Objects
		break;
	default:
		break;
	}
}
bool isFloat(const std::string& s) {
	try {
		std::stof(s);
		return true;
	}
	catch (...) {
		return false;
	}
}
void QtGuiApplication1::on_tableWidget_cellChanged(int row, int column)
{
	if (column != 1)
	{
		return;
	}
	std::string ParamValue = ui.RefParam_tableWidget->item(row, 1)->text().toStdString();
	if (!isFloat(ParamValue))
	{
		ui.RefParam_tableWidget->item(row, column)->setBackgroundColor(QColor(200, 0, 0));
		return;
	}
	else
	{
		ui.RefParam_tableWidget->item(row, column)->setBackgroundColor(QColor(255, 255, 255));
	}
	
	if(commandStack.TestRefParam(ParamValue, commandStack.paramRef.paramRefVec.at(row).ObjectName, commandStack.paramRef.paramRefVec.at(row).paramindex))
	{
		size_t i = 0;
		for (; i < commandStack.GraphCommand.size(); i++)
		{
			if (commandStack.GraphCommand.at(i)->name == commandStack.paramRef.paramRefVec.at(row).ObjectName)
			{
				break;
			}
		}
		//set new value d
		commandStack.SetRefValue(commandStack.paramRef.paramRefVec.at(row).ObjectName,commandStack.paramRef.paramRefVec.at(row).paramindex, ParamValue);
		//modify tree view
		//ui.RefParam_tableWidget->item(1, 1)
		CommandToQStrings(commandStack.GraphCommand[i], ui.treeWidget->topLevelItem(i) );
	}
}

void QtGuiApplication1::on_RefParam_UPButton_clicked()
{
	if (ui.RefParam_tableWidget->rowCount() > 0) {
		size_t position = ui.RefParam_tableWidget->currentIndex().row();
		if (position != 0)
		{//not first
			//move in vec
			std::swap(commandStack.paramRef.paramRefVec[position], commandStack.paramRef.paramRefVec[position - 1]);
			//move item in table
			ui.RefParam_tableWidget->Move(position, true);

		}
	}
}

void QtGuiApplication1::on_RefParam_DOWNButton_clicked()
{
	if (ui.RefParam_tableWidget->rowCount() > 0) {
		size_t position = ui.RefParam_tableWidget->currentIndex().row();
		if (position != commandStack.paramRef.paramRefVec.size() - 1)
		{//not last

			//move in vec
			std::swap(commandStack.paramRef.paramRefVec[position], commandStack.paramRef.paramRefVec[position + 1]);

			//move item in table
			ui.RefParam_tableWidget->Move(position, false);
		}
	}
}

void QtGuiApplication1::on_RefParam_tableWidget_cellChanged(int row, int column)
{
	on_tableWidget_cellChanged(row,column);
}

void QtGuiApplication1::on_DOWN_command_Button_clicked()
{
	if (ui.treeWidget->topLevelItemCount() > 0) {
		QTreeWidgetItem *item = ui.treeWidget->currentItem();
		
		int row = ui.treeWidget->currentIndex().row();
		if (item && row < ui.treeWidget->topLevelItemCount()-1)
		{
			//move in vec
			std::swap(commandStack.GraphCommand[row], commandStack.GraphCommand[row + 1]);

			//swap in tree
			QTreeWidgetItem* A = ui.treeWidget->takeTopLevelItem(row + 1);
			ui.treeWidget->insertTopLevelItem(row , A);
		}
		//test
		TestCommandsValidity(row);
	}
}

void QtGuiApplication1::on_UP_command_Button_clicked()
{
	if (ui.treeWidget->topLevelItemCount() > 0) {
		QTreeWidgetItem *item = ui.treeWidget->currentItem();

		int row = ui.treeWidget->currentIndex().row();
		if (item && row > 0)
		{
			//move in vec
			std::swap(commandStack.GraphCommand[row], commandStack.GraphCommand[row - 1]);


			//swap in tree
			QTreeWidgetItem* B = ui.treeWidget->takeTopLevelItem(row - 1);
			ui.treeWidget->insertTopLevelItem(row , B);
		}
		//test
		TestCommandsValidity(row-1);
	}
}
