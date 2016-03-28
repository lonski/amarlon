/********************************************************************************
** Form generated from reading UI file 'skill_editor.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKILL_EDITOR_H
#define UI_SKILL_EDITOR_H

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

class Ui_SkillEditor
{
public:
    QAction *actionNew_Skill;
    QAction *actionDelete_Skill;
    QAction *actionNew_file;
    QAction *actionSave_as;
    QAction *actionOpen;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTableWidget *sTable;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *SkillEditor)
    {
        if (SkillEditor->objectName().isEmpty())
            SkillEditor->setObjectName(QStringLiteral("SkillEditor"));
        SkillEditor->resize(800, 600);
        actionNew_Skill = new QAction(SkillEditor);
        actionNew_Skill->setObjectName(QStringLiteral("actionNew_Skill"));
        actionDelete_Skill = new QAction(SkillEditor);
        actionDelete_Skill->setObjectName(QStringLiteral("actionDelete_Skill"));
        actionNew_file = new QAction(SkillEditor);
        actionNew_file->setObjectName(QStringLiteral("actionNew_file"));
        actionSave_as = new QAction(SkillEditor);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionOpen = new QAction(SkillEditor);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        centralwidget = new QWidget(SkillEditor);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        sTable = new QTableWidget(centralwidget);
        sTable->setObjectName(QStringLiteral("sTable"));
        sTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        sTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        sTable->setCornerButtonEnabled(true);
        sTable->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(sTable);

        SkillEditor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SkillEditor);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        SkillEditor->setMenuBar(menubar);
        statusbar = new QStatusBar(SkillEditor);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        SkillEditor->setStatusBar(statusbar);
        toolBar = new QToolBar(SkillEditor);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        SkillEditor->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew_file);
        menuFile->addAction(actionSave_as);
        menuFile->addAction(actionOpen);
        toolBar->addAction(actionNew_Skill);
        toolBar->addAction(actionDelete_Skill);

        retranslateUi(SkillEditor);

        QMetaObject::connectSlotsByName(SkillEditor);
    } // setupUi

    void retranslateUi(QMainWindow *SkillEditor)
    {
        SkillEditor->setWindowTitle(QApplication::translate("SkillEditor", "MainWindow", 0));
        actionNew_Skill->setText(QApplication::translate("SkillEditor", "New Skill", 0));
        actionDelete_Skill->setText(QApplication::translate("SkillEditor", "Delete Skill", 0));
        actionNew_file->setText(QApplication::translate("SkillEditor", "New", 0));
        actionSave_as->setText(QApplication::translate("SkillEditor", "Save as..", 0));
        actionOpen->setText(QApplication::translate("SkillEditor", "Open..", 0));
        menuFile->setTitle(QApplication::translate("SkillEditor", "File", 0));
        toolBar->setWindowTitle(QApplication::translate("SkillEditor", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class SkillEditor: public Ui_SkillEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKILL_EDITOR_H
