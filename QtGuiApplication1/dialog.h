#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "../Thesis/ParametricModel.h"
#include <QTableWidgetItem>
#include <QTreeWidgetItem>
#include <string>
#include <QMessageBox>
#include "DialogWindowType.h"
#include <QLineEdit>
namespace Ui {
class Dialog;
}

struct CommandStruct {
	std::string operationName;
	std::string parameterList;
	size_t operationID;
	size_t ParameterID;
	std::string Info;
};

class Dialog : public QDialog
{
    Q_OBJECT

public:
	explicit Dialog(ParametricModel *paramModel, Command ** c, DialogWindowType DialogType, int  index = -1, QWidget *parent = nullptr);
//	explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

	void FillCommandList();

private slots:
    void on_treeWidget_itemSelectionChanged();

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void on_cancelButton_clicked();

    void on_okButton_clicked();

    void on_tableWidget_cellChanged(int row, int column);

private:
    Ui::Dialog *ui;
	std::vector <
		std::vector<
		operationType::ParameterTypesEnum
		>*
	>* paramVectors;
	long index=-1;
	ParametricModel *paramModel=NULL;
	Command ** c;

	std::vector<CommandStruct> CommandsVec;
	void Clean();
	DialogWindowType DialogType;
};

#endif // DIALOG_H
