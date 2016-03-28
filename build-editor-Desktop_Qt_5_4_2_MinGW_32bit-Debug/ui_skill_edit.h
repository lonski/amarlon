/********************************************************************************
** Form generated from reading UI file 'skill_edit.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKILL_EDIT_H
#define UI_SKILL_EDIT_H

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

class Ui_SkillEdit
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
    QComboBox *fPassive;
    QLabel *label_5;
    QComboBox *fTarget;
    QLabel *label_6;
    QSpinBox *fRange;
    QLabel *label_7;
    QSpinBox *fRadius;
    QLabel *label_8;
    QTextEdit *fDescription;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SkillEdit)
    {
        if (SkillEdit->objectName().isEmpty())
            SkillEdit->setObjectName(QStringLiteral("SkillEdit"));
        SkillEdit->resize(429, 528);
        verticalLayout = new QVBoxLayout(SkillEdit);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(SkillEdit);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        fName = new QLineEdit(SkillEdit);
        fName->setObjectName(QStringLiteral("fName"));

        verticalLayout->addWidget(fName);

        label_2 = new QLabel(SkillEdit);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        fID = new QSpinBox(SkillEdit);
        fID->setObjectName(QStringLiteral("fID"));

        verticalLayout->addWidget(fID);

        label_3 = new QLabel(SkillEdit);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        fLevel = new QSpinBox(SkillEdit);
        fLevel->setObjectName(QStringLiteral("fLevel"));

        verticalLayout->addWidget(fLevel);

        label_4 = new QLabel(SkillEdit);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        fPassive = new QComboBox(SkillEdit);
        fPassive->setObjectName(QStringLiteral("fPassive"));

        verticalLayout->addWidget(fPassive);

        label_5 = new QLabel(SkillEdit);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        fTarget = new QComboBox(SkillEdit);
        fTarget->setObjectName(QStringLiteral("fTarget"));

        verticalLayout->addWidget(fTarget);

        label_6 = new QLabel(SkillEdit);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

        fRange = new QSpinBox(SkillEdit);
        fRange->setObjectName(QStringLiteral("fRange"));

        verticalLayout->addWidget(fRange);

        label_7 = new QLabel(SkillEdit);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        fRadius = new QSpinBox(SkillEdit);
        fRadius->setObjectName(QStringLiteral("fRadius"));

        verticalLayout->addWidget(fRadius);

        label_8 = new QLabel(SkillEdit);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout->addWidget(label_8);

        fDescription = new QTextEdit(SkillEdit);
        fDescription->setObjectName(QStringLiteral("fDescription"));

        verticalLayout->addWidget(fDescription);

        buttonBox = new QDialogButtonBox(SkillEdit);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SkillEdit);

        QMetaObject::connectSlotsByName(SkillEdit);
    } // setupUi

    void retranslateUi(QDialog *SkillEdit)
    {
        SkillEdit->setWindowTitle(QApplication::translate("SkillEdit", "Dialog", 0));
        label->setText(QApplication::translate("SkillEdit", "Name", 0));
        label_2->setText(QApplication::translate("SkillEdit", "ID", 0));
        label_3->setText(QApplication::translate("SkillEdit", "Level", 0));
        label_4->setText(QApplication::translate("SkillEdit", "Passive", 0));
        fPassive->clear();
        fPassive->insertItems(0, QStringList()
         << QApplication::translate("SkillEdit", "False", 0)
         << QApplication::translate("SkillEdit", "True", 0)
        );
        label_5->setText(QApplication::translate("SkillEdit", "Target", 0));
        fTarget->clear();
        fTarget->insertItems(0, QStringList()
         << QApplication::translate("SkillEdit", "Single neighbour", 0)
         << QApplication::translate("SkillEdit", "Single range", 0)
         << QApplication::translate("SkillEdit", "Area range", 0)
         << QApplication::translate("SkillEdit", "Area neighbour", 0)
         << QApplication::translate("SkillEdit", "Self", 0)
         << QApplication::translate("SkillEdit", "Single range projectile", 0)
         << QApplication::translate("SkillEdit", "Caster area", 0)
        );
        label_6->setText(QApplication::translate("SkillEdit", "Range", 0));
        label_7->setText(QApplication::translate("SkillEdit", "Radius", 0));
        label_8->setText(QApplication::translate("SkillEdit", "Description", 0));
    } // retranslateUi

};

namespace Ui {
    class SkillEdit: public Ui_SkillEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKILL_EDIT_H
