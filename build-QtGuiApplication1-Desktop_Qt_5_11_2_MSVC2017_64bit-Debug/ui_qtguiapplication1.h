/********************************************************************************
** Form generated from reading UI file 'qtguiapplication1.ui'
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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "oglwidget.h"

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
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *NewButton;
    QPushButton *InsertButton;
    QPushButton *DeleteButton;
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
        splitter->addWidget(graphicsView);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        treeWidget = new QTreeWidget(verticalLayoutWidget);
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
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        NewButton = new QPushButton(verticalLayoutWidget);
        NewButton->setObjectName(QStringLiteral("NewButton"));
        NewButton->setEnabled(true);

        horizontalLayout->addWidget(NewButton);

        InsertButton = new QPushButton(verticalLayoutWidget);
        InsertButton->setObjectName(QStringLiteral("InsertButton"));
        InsertButton->setEnabled(false);

        horizontalLayout->addWidget(InsertButton);

        DeleteButton = new QPushButton(verticalLayoutWidget);
        DeleteButton->setObjectName(QStringLiteral("DeleteButton"));
        DeleteButton->setEnabled(false);

        horizontalLayout->addWidget(DeleteButton);


        verticalLayout->addLayout(horizontalLayout);

        splitter->addWidget(verticalLayoutWidget);
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
        menuBar->setGeometry(QRect(0, 0, 956, 26));
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
        ___qtreewidgetitem->setText(0, QApplication::translate("QtGuiApplication1Class", "Command", nullptr));
        NewButton->setText(QApplication::translate("QtGuiApplication1Class", "New", nullptr));
        InsertButton->setText(QApplication::translate("QtGuiApplication1Class", "Insert after", nullptr));
        DeleteButton->setText(QApplication::translate("QtGuiApplication1Class", "Delete", nullptr));
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
