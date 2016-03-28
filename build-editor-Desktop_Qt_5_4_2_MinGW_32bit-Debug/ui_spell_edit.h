/********************************************************************************
** Form generated from reading UI file 'spell_edit.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPELL_EDIT_H
#define UI_SPELL_EDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Spell_Edit
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *fName;
    QLabel *label_2;
    QSpinBox *fID;
    QLabel *label_3;
    QSpinBox *fLevel;
    QLabel *label_4;
    QComboBox *fClass;
    QLabel *label_5;
    QComboBox *fTarget;
    QLabel *label_6;
    QSpinBox *fRange;
    QLabel *label_7;
    QSpinBox *fRadius;
    QLabel *label_8;
    QTextEdit *fDescription;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Spell_Edit)
    {
        if (Spell_Edit->objectName().isEmpty())
            Spell_Edit->setObjectName(QStringLiteral("Spell_Edit"));
        Spell_Edit->resize(430, 527);
        verticalLayout = new QVBoxLayout(Spell_Edit);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(Spell_Edit);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        fName = new QLineEdit(Spell_Edit);
        fName->setObjectName(QStringLiteral("fName"));

        verticalLayout->addWidget(fName);

        label_2 = new QLabel(Spell_Edit);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        fID = new QSpinBox(Spell_Edit);
        fID->setObjectName(QStringLiteral("fID"));

        verticalLayout->addWidget(fID);

        label_3 = new QLabel(Spell_Edit);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        fLevel = new QSpinBox(Spell_Edit);
        fLevel->setObjectName(QStringLiteral("fLevel"));

        verticalLayout->addWidget(fLevel);

        label_4 = new QLabel(Spell_Edit);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        fClass = new QComboBox(Spell_Edit);
        fClass->setObjectName(QStringLiteral("fClass"));

        verticalLayout->addWidget(fClass);

        label_5 = new QLabel(Spell_Edit);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        fTarget = new QComboBox(Spell_Edit);
        fTarget->setObjectName(QStringLiteral("fTarget"));

        verticalLayout->addWidget(fTarget);

        label_6 = new QLabel(Spell_Edit);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

        fRange = new QSpinBox(Spell_Edit);
        fRange->setObjectName(QStringLiteral("fRange"));

        verticalLayout->addWidget(fRange);

        label_7 = new QLabel(Spell_Edit);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        fRadius = new QSpinBox(Spell_Edit);
        fRadius->setObjectName(QStringLiteral("fRadius"));

        verticalLayout->addWidget(fRadius);

        label_8 = new QLabel(Spell_Edit);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout->addWidget(label_8);

        fDescription = new QTextEdit(Spell_Edit);
        fDescription->setObjectName(QStringLiteral("fDescription"));

        verticalLayout->addWidget(fDescription);

        buttonBox = new QDialogButtonBox(Spell_Edit);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Spell_Edit);
        QObject::connect(buttonBox, SIGNAL(accepted()), Spell_Edit, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Spell_Edit, SLOT(reject()));

        QMetaObject::connectSlotsByName(Spell_Edit);
    } // setupUi

    void retranslateUi(QDialog *Spell_Edit)
    {
        Spell_Edit->setWindowTitle(QApplication::translate("Spell_Edit", "Dialog", 0));
        label->setText(QApplication::translate("Spell_Edit", "Name", 0));
        label_2->setText(QApplication::translate("Spell_Edit", "ID", 0));
        label_3->setText(QApplication::translate("Spell_Edit", "Level", 0));
        label_4->setText(QApplication::translate("Spell_Edit", "Class", 0));
        fClass->clear();
        fClass->insertItems(0, QStringList()
         << QApplication::translate("Spell_Edit", "No class", 0)
         << QApplication::translate("Spell_Edit", "Fighter", 0)
         << QApplication::translate("Spell_Edit", "Cleric", 0)
         << QApplication::translate("Spell_Edit", "Magic user", 0)
         << QApplication::translate("Spell_Edit", "Thief", 0)
         << QApplication::translate("Spell_Edit", "Monster", 0)
        );
        label_5->setText(QApplication::translate("Spell_Edit", "Target", 0));
        fTarget->clear();
        fTarget->insertItems(0, QStringList()
         << QApplication::translate("Spell_Edit", "Single neighbour", 0)
         << QApplication::translate("Spell_Edit", "Single range", 0)
         << QApplication::translate("Spell_Edit", "Area range", 0)
         << QApplication::translate("Spell_Edit", "Area neighbour", 0)
         << QApplication::translate("Spell_Edit", "Self", 0)
         << QApplication::translate("Spell_Edit", "Single range projectile", 0)
         << QApplication::translate("Spell_Edit", "Caster area", 0)
        );
        label_6->setText(QApplication::translate("Spell_Edit", "Range", 0));
        label_7->setText(QApplication::translate("Spell_Edit", "Radius", 0));
        label_8->setText(QApplication::translate("Spell_Edit", "Description", 0));
    } // retranslateUi

};

namespace Ui {
    class Spell_Edit: public Ui_Spell_Edit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPELL_EDIT_H
