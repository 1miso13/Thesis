#pragma once

#include <QtWidgets/QMainWindow>
#include "GeneratedFiles/ui_QtGuiApplication1.h"
#include "GraphViz.h"

class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	ParametricModel paramModel;
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);
	static QIcon setObjectIcon(Object::ObjectTypeEnum type);
	GVGraph *graph;
private slots:

	/// <summary>
	/// add new operations from text
	/// </summary>
    void on_pushButton_clicked();

   // void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_actionHelp_triggered();

    void on_actionQuit_triggered();

	/// <summary>
	/// Add new operation
	/// </summary>
    void on_actionAdd_triggered();

	/// <summary>
	/// remove selected operation
	/// </summary>
    void on_actionDelete_triggered();

	/// <summary>
	/// remove all operation
	/// </summary>
    void on_actionDelete_all_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionNew_triggered();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_actionCommand_list_triggered();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

	/// <summary>
	/// insert new operation
	/// </summary>
    void on_InsertButton_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_NewButton_clicked();

    void on_DeleteButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tableWidget_cellChanged(int row, int column);

    void on_RefParam_UPButton_clicked();

    void on_RefParam_DOWNButton_clicked();

    void on_RefParam_tableWidget_cellChanged(int row, int column);

    void on_UP_command_Button_clicked();

    void on_DOWN_command_Button_clicked();


private:
	Ui::QtGuiApplication1Class ui;
	bool ReadyToBuild = true;
	void TestOperationsValidity(size_t indexFrom);
	void DisableButtons();
	void RefreshObjectList();
	void CreateGraph();


	void OperationToQStrings(Operation *c, QTreeWidgetItem* qTreeWidgetItem);
	//~QtGuiApplication1();
};
