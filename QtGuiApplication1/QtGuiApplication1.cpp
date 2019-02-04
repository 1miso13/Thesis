#include "QtGuiApplication1.h"
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include "dialog.h"
//#include "../Thesis/ParametricModel.h"
//#include "../Thesis/OperationTypes.h"
#include "DialogWindowType.h"
#include <qgraphicsscene.h>


#include "ParametricModel.h"
#include "OperationTypes.h"
#include "OperationTypes.h"


QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	graph = new GVGraph("graph");
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
void QtGuiApplication1::CommandToQStrings(Operation *c, QTreeWidgetItem* qTreeWidgetItem) {
	// 0 - Operation Name
	qTreeWidgetItem->setText(0, QString::fromStdString(operationType::OperationToString(c->operationType)));
	qTreeWidgetItem->setIcon(0,setObjectIcon(operationType::findTypeOfOperation(c->operationType)));
	// 1 - Operation Name
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
	std::string commandParameters = ParameterToString(l->at(0)) + " " + c->OperationParametersVec->at(0);
	for (size_t i = 1; i < c->OperationParametersVec->size(); i++)
	{
		std::string parameterType = c->operationType == operationType::Polygon ? "POINT" : ParameterToString(l->at(i));
		commandParameters = commandParameters + ",\t" + parameterType + " " + c->OperationParametersVec->at(i);
	}
	// 3 - Parameters
	qTreeWidgetItem->setText(3, QString::fromStdString(commandParameters));
	operationType::ClearParamVectors(&paramVectors);
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

	   if (paramModel.AddCommand(commandsVec.at(i)))
	   {
		   ui.lineEdit->setStyleSheet("color: #00FF00");

		   size_t commandID = paramModel.GraphCommand.size() - 1;
		   // Create new item (top level item)
		   QTreeWidgetItem *qTreeWidgetItem = new QTreeWidgetItem(ui.treeWidget);
		   // Add it on our tree as the top item.
		   ui.treeWidget->addTopLevelItem(qTreeWidgetItem);
	   
		   CommandToQStrings(paramModel.GraphCommand[commandID], qTreeWidgetItem);
	   }

   }
   ui.RefParam_tableWidget->RefillRefTable(&paramModel);
   RefreshObjectList();
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
	Operation *c;
	Dialog dialog(&paramModel, &c, DialogWindowType::NEW, -1/*new*/, this);
	dialog.setModal(true);
	dialog.setWindowTitle("New command");
	if (dialog.exec())
	{//OK 
		
		// Create new item (top level item)
		QTreeWidgetItem *qTreeWidgetItem = new QTreeWidgetItem(ui.treeWidget);
		// Add it on our tree as the top item.
		ui.treeWidget->addTopLevelItem(qTreeWidgetItem);

		paramModel.AddCommand(c);
		CommandToQStrings(c, qTreeWidgetItem);

		RefreshObjectList();
	}
}

void QtGuiApplication1::on_actionDelete_triggered()
{
	if ((ui.treeWidget->currentItem() != NULL))
	{
		on_DeleteButton_clicked();
		RefreshObjectList();
	}
}

void QtGuiApplication1::on_actionDelete_all_triggered()
{
	while (ui.treeWidget->topLevelItemCount() > 0)
	{

		size_t index = 0;
		//delete
		delete ui.treeWidget->takeTopLevelItem(index);
		paramModel.RemoveCommand(index);
		//paramModel.GraphCommand.erase(paramModel.GraphCommand.begin() + index);

	}
	DisableButtons();
	RefreshObjectList();
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
/// Operation line color
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

	paramModel.resetTest();
	for (size_t i = 0; i < commandsVec.size(); i++)
	{

		if (!paramModel.TestCommand(commandsVec.at(i)))
		{
			noError = false;
		}
	}
	paramModel.resetTest();
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
void CopyCommand(Operation * cFROM, Operation *& cTO) {
	std::vector <std::string> * commandParameterVector = new std::vector <std::string>();
	for (size_t i = 0; i < cFROM->OperationParametersVec->size(); i++)
	{
		std::string s = (cFROM->OperationParametersVec)->at(i);
		commandParameterVector->push_back(s);
	}
	cTO = new Operation(cFROM->name,cFROM->visibility,cFROM->operationType,commandParameterVector,cFROM->typeOfParameters);
}

/// <summary>
/// Test command referienciesat index
/// </summary>
/// <param name="paramModel">Operation list</param>
/// <param name="index">item index</param>
/// <returns>If all referencies in command are valid</returns>
bool TestCommandSemantic(ParametricModel *paramModel, size_t index) {
	std::string operationName = operationType::OperationToString(paramModel->GraphCommand.at(index)->operationType);//operationType::OperationToString((operationType::OperationTypeEnum) i);
	std::vector<std::vector<operationType::ParameterTypesEnum>*> *paramVectors;
	operationType::GetOperationParameters(operationName,
		&paramVectors);

	std::vector <operationType::ParameterTypesEnum> * k = paramVectors->at(paramModel->GraphCommand.at(index)->typeOfParameters - 1);
	operationType::ClearParamVectors(&paramVectors);
	//Test parameters
	for (size_t i = 0; i < k->size(); i++)
	{
		if (k->at(i) == operationType::ParameterTypeMULTIPLEPOINTS)
		{
			for (size_t j = 0;  j + i < paramModel->GraphCommand.at(index)->OperationParametersVec->size();  j++)
			{//Last parameter can be multipoits
				std::string parameterText = paramModel->GraphCommand.at(index)->OperationParametersVec->at(i+j);
				if (!operationType::TestValidParameterType(k->at(i), parameterText, &paramModel->GraphCommand, index))
				{
					return false;
				}
			}
		}
		else
		{
			std::string parameterText = paramModel->GraphCommand.at(index)->OperationParametersVec->at(i);
			if (!operationType::TestValidParameterType(k->at(i), parameterText, &paramModel->GraphCommand, index))
			{
				return false;
			}
		}
	}
	
	return true;
}
void QtGuiApplication1::TestCommandsValidity(size_t indexFrom) {
	size_t countOfInvalid = 0;
	for (size_t i = indexFrom; i < paramModel.GraphCommand.size(); i++)
	{
		//TODO;
		if (!TestCommandSemantic(&paramModel, i))
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
	Operation * c;
	CopyCommand(paramModel.GraphCommand[index], c);
	Dialog dialog(&paramModel, &c, DialogWindowType::MODIFY, index, this);
	dialog.setModal(true);
	dialog.setWindowTitle("Modify command");
	if (dialog.exec())
	{//OK
		//modify paramModel
		if (paramModel.GraphCommand.at(index)->operationType == c->operationType)
		{///Changed value in command
			paramModel.ModifyCommand(index,c);
		}
		else
		{///change whole command
			//delete old command
			paramModel.RemoveCommand(index);
			//delete paramModel.GraphCommand[index];
			//add new command
			paramModel.InsertCommand(index, c);
			//paramModel.GraphCommand[index] = c;		
		}
		//modify tree wiev
		CommandToQStrings(paramModel.GraphCommand[index], currentItem);

		//need to find all missing referencies after index and highlight
		{
			TestCommandsValidity(index);
		}

		RefreshObjectList();
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
	Operation *c;
	Dialog dialog(&paramModel, &c, DialogWindowType::INSERT, index/*insert position*/,this);
	dialog.setModal(true);
	dialog.setWindowTitle("Insert command");
	if (dialog.exec())
	{//OK 

		// Create new item (top level item)
		QTreeWidgetItem *qTreeWidgetItem = new QTreeWidgetItem();
		// Add it on our tree as the top item.
		ui.treeWidget->insertTopLevelItem(index,qTreeWidgetItem);

		paramModel.InsertCommand(index,c);
		CommandToQStrings(c, qTreeWidgetItem);
		ui.treeWidget->repaint();

		RefreshObjectList();
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
	paramModel.RemoveCommand(index); //.GraphCommand.erase(paramModel.GraphCommand.begin()+index);
	//test
	TestCommandsValidity(index);
	if (ui.treeWidget->topLevelItemCount()==0)
	{
		DisableButtons();
	}
	RefreshObjectList();
}
/// <summary>
/// Disable Insert and delete buttons
/// </summary>
void QtGuiApplication1::DisableButtons() {
	ui.InsertButton->setEnabled(false);
	ui.DeleteButton->setEnabled(false);
}
/// <summary>
/// Remove whole graph and create new  
/// </summary>
void QtGuiApplication1::CreateGraph() {
	graph->clearNodes();

	std::vector <
		std::vector<
		operationType::ParameterTypesEnum
		>*
	>* paramVectors;
	for (size_t i = 0; i < paramModel.GraphCommand.size(); i++)
	{
		Operation * o = paramModel.GraphCommand.at(i);
		graph->addNode(QString::fromStdString(o->name));

		operationType::GetOperationParameters(operationType::OperationToString(o->operationType), &paramVectors);
		/// <summary>
		/// for all non float parameters
		/// </summary>
		for (size_t j = 0; j < o->OperationParametersVec->size(); j++)
		{
			if (paramVectors->at(o->typeOfParameters - 1)->at(0) == operationType::ParameterTypesEnum::ParameterTypeMULTIPLEPOINTS || paramVectors->at(o->typeOfParameters-1)->at(j) != operationType::ParameterTypesEnum::ParameterTypeFLOAT)
			{
				//find parent object
				std::string par = o->OperationParametersVec->at(j);
				std::string parent = paramModel.OperationMap[par]->name;
				//add edge from parent to this
				graph->addEdge(QString::fromStdString(parent), QString::fromStdString(o->name), parent + "_" + o->name);
			}

		}
		operationType::ClearParamVectors(&paramVectors);
	}
	graph->applyLayout();
	graph->print();
}
//QtGuiApplication1::~QtGuiApplication1()
//{
//	//delete graph;
//}
QIcon QtGuiApplication1::setObjectIcon(Object::ObjectTypeEnum type) {
	switch (type)
	{
	case Object::POINTObjectType:
		return QIcon("Icons/Object icons/point.jpg");
	case Object::LINE:
		return QIcon("Icons/Object icons/Line.ico");
	case Object::SURFACE:
		return QIcon("Icons/Object icons/Invalid.png");
	case Object::CIRCLE:
		return QIcon("Icons/Object icons/Circle.png");
	case Object::RECTANGLE:
		return QIcon("Icons/Object icons/Rectangle.png");
	case Object::POLYGON:
		return QIcon("Icons/Object icons/Polygon.png");
	case Object::TRIANGLE:
		return QIcon("Icons/Object icons/Triangle.png");
	case Object::OBJECT3D:
		return QIcon("Icons/Object icons/point.jpg");
	case Object::PYRAMID:
		return QIcon("Icons/Object icons/Pyramid.png");
	case Object::SPHERE:
		return QIcon("Icons/Object icons/Sphere.png");
	case Object::INVALIDObjectType:
		return QIcon("Icons/Object icons/Invalid.png");
	default:
		break;
	}
}
/// <summary>
/// refresh object list
/// </summary>
void QtGuiApplication1::RefreshObjectList()
{
	//rebuild tree
	if (ReadyToBuild)
	{
		paramModel.ReBuildTree();
	}

	//delete 

	if (ReadyToBuild)
	{
		for (size_t i = 0; i < paramModel.Objects.size(); i++)
		{

			// Create new item (top level item)
			QTreeWidgetItem *qTreeWidgetItem = new QTreeWidgetItem(ui.treeWidget_2);
			// Add it on our tree as the top item.
			ui.treeWidget_2->addTopLevelItem(qTreeWidgetItem);

			qTreeWidgetItem->setText(0, QString::fromStdString(paramModel.Objects.at(i)->ObjectName));
			qTreeWidgetItem->setText(1, QString::fromStdString(paramModel.Objects.at(i)->TypeToText()));
			qTreeWidgetItem->setText(2, QString::number(paramModel.Objects.at(i)->visibility));
			qTreeWidgetItem->setIcon(0, setObjectIcon(paramModel.Objects.at(i)->GeometricType));
		
			ui.treeWidget_2->repaint();
		}
	}
	//
	CreateGraph();
}

/// <summary>
/// prepinanie tabov 
/// operations-parameters-objects
/// </summary>
/// <param name="index"></param>
void QtGuiApplication1::on_tabWidget_currentChanged(int index){
	switch (index)
	{
	case 0://Commands

		break;
	case 1://Referenced Variables
		//refill ref param list
		ui.RefParam_tableWidget->RefillRefTable(&paramModel);
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
/// <summary>
/// Parameter list
/// </summary>
/// <param name="row"></param>
/// <param name="column"></param>
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
	
	if(paramModel.TestRefParam(ParamValue, paramModel.paramRef.paramRefVec.at(row).ObjectName, paramModel.paramRef.paramRefVec.at(row).paramindex))
	{
		size_t i = 0;
		for (; i < paramModel.GraphCommand.size(); i++)
		{
			if (paramModel.GraphCommand.at(i)->name == paramModel.paramRef.paramRefVec.at(row).ObjectName)
			{
				break;
			}
		}
		//set new value d
		paramModel.SetRefValue(paramModel.paramRef.paramRefVec.at(row).ObjectName,paramModel.paramRef.paramRefVec.at(row).paramindex, ParamValue);
		//modify tree view
		//ui.RefParam_tableWidget->item(1, 1)
		CommandToQStrings(paramModel.GraphCommand[i], ui.treeWidget->topLevelItem(i) );
	}
}

void QtGuiApplication1::on_RefParam_UPButton_clicked()
{
	if (ui.RefParam_tableWidget->rowCount() > 0) {
		size_t position = ui.RefParam_tableWidget->currentIndex().row();
		if (position != 0)
		{//not first
			//move in vec
			std::swap(paramModel.paramRef.paramRefVec[position], paramModel.paramRef.paramRefVec[position - 1]);
			//move item in table
			ui.RefParam_tableWidget->Move(position, true);

		}
	}
}

void QtGuiApplication1::on_RefParam_DOWNButton_clicked()
{
	if (ui.RefParam_tableWidget->rowCount() > 0) {
		size_t position = ui.RefParam_tableWidget->currentIndex().row();
		if (position != paramModel.paramRef.paramRefVec.size() - 1)
		{//not last

			//move in vec
			std::swap(paramModel.paramRef.paramRefVec[position], paramModel.paramRef.paramRefVec[position + 1]);

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
			std::swap(paramModel.GraphCommand[row], paramModel.GraphCommand[row + 1]);

			//swap in tree
			QTreeWidgetItem* A = ui.treeWidget->takeTopLevelItem(row + 1);
			ui.treeWidget->insertTopLevelItem(row , A);
		}
		//test
		TestCommandsValidity(row);
		RefreshObjectList();
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
			std::swap(paramModel.GraphCommand[row], paramModel.GraphCommand[row - 1]);


			//swap in tree
			QTreeWidgetItem* B = ui.treeWidget->takeTopLevelItem(row - 1);
			ui.treeWidget->insertTopLevelItem(row , B);
		}
		//test
		TestCommandsValidity(row-1);
		RefreshObjectList();
	}
}
