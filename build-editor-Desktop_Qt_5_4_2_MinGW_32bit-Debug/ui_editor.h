/********************************************************************************
** Form generated from reading UI file 'editor.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOR_H
#define UI_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editor
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *editor)
    {
        if (editor->objectName().isEmpty())
            editor->setObjectName(QStringLiteral("editor"));
        editor->resize(269, 370);
        centralWidget = new QWidget(editor);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(pushButton);

        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(pushButton_4);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(pushButton_3);

        editor->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(editor);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 269, 21));
        editor->setMenuBar(menuBar);
        mainToolBar = new QToolBar(editor);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        editor->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(editor);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        editor->setStatusBar(statusBar);

        retranslateUi(editor);

        QMetaObject::connectSlotsByName(editor);
    } // setupUi

    void retranslateUi(QMainWindow *editor)
    {
        editor->setWindowTitle(QApplication::translate("editor", "editor", 0));
        pushButton->setText(QApplication::translate("editor", "Spells Editor", 0));
        pushButton_4->setText(QApplication::translate("editor", "Skills Editor", 0));
        pushButton_2->setText(QApplication::translate("editor", "Tiles Editor", 0));
        pushButton_3->setText(QApplication::translate("editor", "Actors Editor", 0));
    } // retranslateUi

};

namespace Ui {
    class editor: public Ui_editor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
