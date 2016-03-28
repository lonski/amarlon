/********************************************************************************
** Form generated from reading UI file 'tiles_editor.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TILES_EDITOR_H
#define UI_TILES_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TilesEditor
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave_as;
    QAction *actionNew_tile;
    QAction *actionDelete_tile;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTableWidget *tTable;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *TilesEditor)
    {
        if (TilesEditor->objectName().isEmpty())
            TilesEditor->setObjectName(QStringLiteral("TilesEditor"));
        TilesEditor->resize(800, 600);
        actionNew = new QAction(TilesEditor);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen = new QAction(TilesEditor);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave_as = new QAction(TilesEditor);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionNew_tile = new QAction(TilesEditor);
        actionNew_tile->setObjectName(QStringLiteral("actionNew_tile"));
        actionDelete_tile = new QAction(TilesEditor);
        actionDelete_tile->setObjectName(QStringLiteral("actionDelete_tile"));
        centralwidget = new QWidget(TilesEditor);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tTable = new QTableWidget(centralwidget);
        tTable->setObjectName(QStringLiteral("tTable"));

        verticalLayout->addWidget(tTable);

        TilesEditor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TilesEditor);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        TilesEditor->setMenuBar(menubar);
        statusbar = new QStatusBar(TilesEditor);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        TilesEditor->setStatusBar(statusbar);
        toolBar = new QToolBar(TilesEditor);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        TilesEditor->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave_as);
        toolBar->addAction(actionNew_tile);
        toolBar->addAction(actionDelete_tile);

        retranslateUi(TilesEditor);

        QMetaObject::connectSlotsByName(TilesEditor);
    } // setupUi

    void retranslateUi(QMainWindow *TilesEditor)
    {
        TilesEditor->setWindowTitle(QApplication::translate("TilesEditor", "MainWindow", 0));
        actionNew->setText(QApplication::translate("TilesEditor", "New", 0));
        actionOpen->setText(QApplication::translate("TilesEditor", "Open..", 0));
        actionSave_as->setText(QApplication::translate("TilesEditor", "Save as..", 0));
        actionNew_tile->setText(QApplication::translate("TilesEditor", "New tile", 0));
        actionDelete_tile->setText(QApplication::translate("TilesEditor", "Delete tile", 0));
        menuFile->setTitle(QApplication::translate("TilesEditor", "File", 0));
        toolBar->setWindowTitle(QApplication::translate("TilesEditor", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class TilesEditor: public Ui_TilesEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TILES_EDITOR_H
