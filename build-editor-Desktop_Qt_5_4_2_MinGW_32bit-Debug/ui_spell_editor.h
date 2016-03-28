/********************************************************************************
** Form generated from reading UI file 'spell_editor.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPELL_EDITOR_H
#define UI_SPELL_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_spell_editor
{
public:
    QAction *actionOpen;
    QAction *actionNew;
    QAction *actionSave;
    QAction *actionSpellNew;
    QAction *actionDelete_spell;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTableWidget *sTable;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *spell_editor)
    {
        if (spell_editor->objectName().isEmpty())
            spell_editor->setObjectName(QStringLiteral("spell_editor"));
        spell_editor->resize(800, 600);
        actionOpen = new QAction(spell_editor);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionNew = new QAction(spell_editor);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionSave = new QAction(spell_editor);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSpellNew = new QAction(spell_editor);
        actionSpellNew->setObjectName(QStringLiteral("actionSpellNew"));
        actionDelete_spell = new QAction(spell_editor);
        actionDelete_spell->setObjectName(QStringLiteral("actionDelete_spell"));
        centralwidget = new QWidget(spell_editor);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        sTable = new QTableWidget(splitter);
        sTable->setObjectName(QStringLiteral("sTable"));
        sTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        sTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        splitter->addWidget(sTable);
        sTable->verticalHeader()->setVisible(false);

        horizontalLayout->addWidget(splitter);

        spell_editor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(spell_editor);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        spell_editor->setMenuBar(menubar);
        statusbar = new QStatusBar(spell_editor);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        spell_editor->setStatusBar(statusbar);
        toolBar = new QToolBar(spell_editor);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        spell_editor->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        toolBar->addSeparator();
        toolBar->addAction(actionSpellNew);
        toolBar->addAction(actionDelete_spell);

        retranslateUi(spell_editor);

        QMetaObject::connectSlotsByName(spell_editor);
    } // setupUi

    void retranslateUi(QMainWindow *spell_editor)
    {
        spell_editor->setWindowTitle(QApplication::translate("spell_editor", "MainWindow", 0));
        actionOpen->setText(QApplication::translate("spell_editor", "Open..", 0));
        actionNew->setText(QApplication::translate("spell_editor", "New", 0));
        actionSave->setText(QApplication::translate("spell_editor", "Save as..", 0));
        actionSpellNew->setText(QApplication::translate("spell_editor", "New spell", 0));
        actionDelete_spell->setText(QApplication::translate("spell_editor", "Delete spell", 0));
        menuFile->setTitle(QApplication::translate("spell_editor", "File", 0));
        toolBar->setWindowTitle(QApplication::translate("spell_editor", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class spell_editor: public Ui_spell_editor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPELL_EDITOR_H
