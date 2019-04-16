/********************************************************************************
** Form generated from reading UI file 'QtGuiApplication1.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIAPPLICATION1_H
#define UI_QTGUIAPPLICATION1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "oglwidget.h"
#include "reftablewidget.h"

QT_BEGIN_NAMESPACE

class Ui_QtGuiApplication1Class
{
public:
    QAction *actionHelp;
    QAction *actionAdd;
    QAction *actionDelete;
    QAction *actionDelete_all;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionQuit;
    QAction *actionNew;
    QAction *actionAplication_info;
    QAction *actionCommand_list;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QSplitter *splitter_2;
    QSplitter *splitter;
    OGLWidget *openGLWidget;
    QGraphicsView *graphicsView;
    QTabWidget *tabWidget;
    QWidget *commands_tab;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *UP_command_Button;
    QPushButton *DOWN_command_Button;
    QSpacerItem *horizontalSpacer;
    QPushButton *NewButton;
    QPushButton *InsertButton;
    QPushButton *DeleteButton;
    QWidget *ref_Params_tab;
    QVBoxLayout *verticalLayout_2;
    RefTableWidget *RefParam_tableWidget;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *RefParam_UPButton;
    QPushButton *RefParam_DOWNButton;
    QWidget *objects_tab;
    QVBoxLayout *verticalLayout_3;
    QTreeWidget *treeWidget_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QMenu *menuHelp;
    QMenu *menuFile;
    QMenu *menuObjects;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGuiApplication1Class)
    {
        if (QtGuiApplication1Class->objectName().isEmpty())
            QtGuiApplication1Class->setObjectName(QStringLiteral("QtGuiApplication1Class"));
        QtGuiApplication1Class->setEnabled(true);
        QtGuiApplication1Class->resize(956, 531);
        QtGuiApplication1Class->setMaximumSize(QSize(16777215, 16777215));
        QtGuiApplication1Class->setLayoutDirection(Qt::LeftToRight);
        actionHelp = new QAction(QtGuiApplication1Class);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionAdd = new QAction(QtGuiApplication1Class);
        actionAdd->setObjectName(QStringLiteral("actionAdd"));
        actionDelete = new QAction(QtGuiApplication1Class);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        actionDelete_all = new QAction(QtGuiApplication1Class);
        actionDelete_all->setObjectName(QStringLiteral("actionDelete_all"));
        actionOpen = new QAction(QtGuiApplication1Class);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(QtGuiApplication1Class);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_as = new QAction(QtGuiApplication1Class);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionQuit = new QAction(QtGuiApplication1Class);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionNew = new QAction(QtGuiApplication1Class);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionAplication_info = new QAction(QtGuiApplication1Class);
        actionAplication_info->setObjectName(QStringLiteral("actionAplication_info"));
        actionCommand_list = new QAction(QtGuiApplication1Class);
        actionCommand_list->setObjectName(QStringLiteral("actionCommand_list"));
        centralWidget = new QWidget(QtGuiApplication1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        splitter_2 = new QSplitter(centralWidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy);
        splitter_2->setOrientation(Qt::Vertical);
        splitter_2->setOpaqueResize(true);
        splitter_2->setChildrenCollapsible(false);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(true);
        splitter->setChildrenCollapsible(true);
        openGLWidget = new OGLWidget(splitter);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        splitter->addWidget(openGLWidget);
        graphicsView = new QGraphicsView(splitter);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setEnabled(false);
        graphicsView->setMaximumSize(QSize(0, 16777215));
        splitter->addWidget(graphicsView);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        commands_tab = new QWidget();
        commands_tab->setObjectName(QStringLiteral("commands_tab"));
        horizontalLayout_3 = new QHBoxLayout(commands_tab);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        treeWidget = new QTreeWidget(commands_tab);
        QFont font;
        font.setItalic(true);
        font.setKerning(true);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setFont(3, font);
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setMaximumSize(QSize(16777215, 16777215));
        treeWidget->setBaseSize(QSize(200, 0));
        treeWidget->setFrameShape(QFrame::StyledPanel);
        treeWidget->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
        treeWidget->setColumnCount(4);

        verticalLayout->addWidget(treeWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        UP_command_Button = new QPushButton(commands_tab);
        UP_command_Button->setObjectName(QStringLiteral("UP_command_Button"));
        UP_command_Button->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(UP_command_Button);

        DOWN_command_Button = new QPushButton(commands_tab);
        DOWN_command_Button->setObjectName(QStringLiteral("DOWN_command_Button"));
        DOWN_command_Button->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(DOWN_command_Button);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        NewButton = new QPushButton(commands_tab);
        NewButton->setObjectName(QStringLiteral("NewButton"));
        NewButton->setEnabled(true);
        NewButton->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(NewButton);

        InsertButton = new QPushButton(commands_tab);
        InsertButton->setObjectName(QStringLiteral("InsertButton"));
        InsertButton->setEnabled(false);
        InsertButton->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(InsertButton);

        DeleteButton = new QPushButton(commands_tab);
        DeleteButton->setObjectName(QStringLiteral("DeleteButton"));
        DeleteButton->setEnabled(false);
        DeleteButton->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(DeleteButton);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout);

        tabWidget->addTab(commands_tab, QString());
        ref_Params_tab = new QWidget();
        ref_Params_tab->setObjectName(QStringLiteral("ref_Params_tab"));
        verticalLayout_2 = new QVBoxLayout(ref_Params_tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        RefParam_tableWidget = new RefTableWidget(ref_Params_tab);
        if (RefParam_tableWidget->columnCount() < 4)
            RefParam_tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        RefParam_tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        RefParam_tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        RefParam_tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        RefParam_tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        RefParam_tableWidget->setObjectName(QStringLiteral("RefParam_tableWidget"));

        verticalLayout_2->addWidget(RefParam_tableWidget);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        RefParam_UPButton = new QPushButton(ref_Params_tab);
        RefParam_UPButton->setObjectName(QStringLiteral("RefParam_UPButton"));
        RefParam_UPButton->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_4->addWidget(RefParam_UPButton);

        RefParam_DOWNButton = new QPushButton(ref_Params_tab);
        RefParam_DOWNButton->setObjectName(QStringLiteral("RefParam_DOWNButton"));
        RefParam_DOWNButton->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_4->addWidget(RefParam_DOWNButton);


        verticalLayout_2->addLayout(horizontalLayout_4);

        tabWidget->addTab(ref_Params_tab, QString());
        objects_tab = new QWidget();
        objects_tab->setObjectName(QStringLiteral("objects_tab"));
        verticalLayout_3 = new QVBoxLayout(objects_tab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        treeWidget_2 = new QTreeWidget(objects_tab);
        treeWidget_2->setObjectName(QStringLiteral("treeWidget_2"));

        verticalLayout_3->addWidget(treeWidget_2);

        tabWidget->addTab(objects_tab, QString());
        splitter->addWidget(tabWidget);
        splitter_2->addWidget(splitter);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_6->addWidget(lineEdit);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setEnabled(false);

        horizontalLayout_6->addWidget(pushButton);

        splitter_2->addWidget(layoutWidget);

        horizontalLayout_2->addWidget(splitter_2);

        QtGuiApplication1Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtGuiApplication1Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 956, 21));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuObjects = new QMenu(menuBar);
        menuObjects->setObjectName(QStringLiteral("menuObjects"));
        QtGuiApplication1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtGuiApplication1Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setEnabled(true);
        QtGuiApplication1Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtGuiApplication1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtGuiApplication1Class->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuObjects->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionCommand_list);
        menuHelp->addAction(actionHelp);
        menuHelp->addAction(actionAplication_info);
        menuFile->addAction(actionNew);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuObjects->addAction(actionAdd);
        menuObjects->addSeparator();
        menuObjects->addAction(actionDelete);
        menuObjects->addAction(actionDelete_all);

        retranslateUi(QtGuiApplication1Class);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(QtGuiApplication1Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiApplication1Class)
    {
        QtGuiApplication1Class->setWindowTitle(QApplication::translate("QtGuiApplication1Class", "Parametric 3D models", nullptr));
        actionHelp->setText(QApplication::translate("QtGuiApplication1Class", "Help", nullptr));
        actionAdd->setText(QApplication::translate("QtGuiApplication1Class", "Add ...", nullptr));
        actionDelete->setText(QApplication::translate("QtGuiApplication1Class", "Delete ...", nullptr));
        actionDelete_all->setText(QApplication::translate("QtGuiApplication1Class", "Delete all", nullptr));
        actionOpen->setText(QApplication::translate("QtGuiApplication1Class", "Load ...", nullptr));
        actionSave->setText(QApplication::translate("QtGuiApplication1Class", "Save", nullptr));
        actionSave_as->setText(QApplication::translate("QtGuiApplication1Class", "Save as ...", nullptr));
        actionQuit->setText(QApplication::translate("QtGuiApplication1Class", "Quit", nullptr));
        actionNew->setText(QApplication::translate("QtGuiApplication1Class", "New", nullptr));
        actionAplication_info->setText(QApplication::translate("QtGuiApplication1Class", "About", nullptr));
        actionCommand_list->setText(QApplication::translate("QtGuiApplication1Class", "Command list", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(3, QApplication::translate("QtGuiApplication1Class", "Parameters", nullptr));
        ___qtreewidgetitem->setText(2, QApplication::translate("QtGuiApplication1Class", "Visibility", nullptr));
        ___qtreewidgetitem->setText(1, QApplication::translate("QtGuiApplication1Class", "ObjectName", nullptr));
        ___qtreewidgetitem->setText(0, QApplication::translate("QtGuiApplication1Class", "Operation", nullptr));
        UP_command_Button->setText(QApplication::translate("QtGuiApplication1Class", "UP", nullptr));
        DOWN_command_Button->setText(QApplication::translate("QtGuiApplication1Class", "DOWN", nullptr));
        NewButton->setText(QApplication::translate("QtGuiApplication1Class", "New", nullptr));
        InsertButton->setText(QApplication::translate("QtGuiApplication1Class", "Insert", nullptr));
        DeleteButton->setText(QApplication::translate("QtGuiApplication1Class", "Delete", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(commands_tab), QApplication::translate("QtGuiApplication1Class", "Operations", nullptr));
        QTableWidgetItem *___qtablewidgetitem = RefParam_tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QtGuiApplication1Class", "Reference name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = RefParam_tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QtGuiApplication1Class", "Value", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = RefParam_tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QtGuiApplication1Class", "Object", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = RefParam_tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("QtGuiApplication1Class", "Index", nullptr));
        RefParam_UPButton->setText(QApplication::translate("QtGuiApplication1Class", "UP", nullptr));
        RefParam_DOWNButton->setText(QApplication::translate("QtGuiApplication1Class", "DOWN", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(ref_Params_tab), QApplication::translate("QtGuiApplication1Class", "Parameters", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget_2->headerItem();
        ___qtreewidgetitem1->setText(2, QApplication::translate("QtGuiApplication1Class", "Visibility", nullptr));
        ___qtreewidgetitem1->setText(1, QApplication::translate("QtGuiApplication1Class", "Type", nullptr));
        ___qtreewidgetitem1->setText(0, QApplication::translate("QtGuiApplication1Class", "Name", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(objects_tab), QApplication::translate("QtGuiApplication1Class", "Objects", nullptr));
        pushButton->setText(QApplication::translate("QtGuiApplication1Class", "Push", nullptr));
        menuHelp->setTitle(QApplication::translate("QtGuiApplication1Class", "Help", nullptr));
        menuFile->setTitle(QApplication::translate("QtGuiApplication1Class", "File", nullptr));
        menuObjects->setTitle(QApplication::translate("QtGuiApplication1Class", "Objects", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGuiApplication1Class: public Ui_QtGuiApplication1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIAPPLICATION1_H
