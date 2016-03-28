/********************************************************************************
** Form generated from reading UI file 'tileeditdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TILEEDITDLG_H
#define UI_TILEEDITDLG_H

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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TileEditDlg
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *fName;
    QLabel *label_2;
    QSpinBox *fID;
    QLabel *label_3;
    QLineEdit *fCharacter;
    QLabel *label_4;
    QLineEdit *fColor;
    QLabel *label_5;
    QComboBox *fWalkable;
    QLabel *label_6;
    QComboBox *fTransparent;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TileEditDlg)
    {
        if (TileEditDlg->objectName().isEmpty())
            TileEditDlg->setObjectName(QStringLiteral("TileEditDlg"));
        TileEditDlg->resize(184, 368);
        verticalLayout = new QVBoxLayout(TileEditDlg);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(TileEditDlg);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        fName = new QLineEdit(TileEditDlg);
        fName->setObjectName(QStringLiteral("fName"));

        verticalLayout->addWidget(fName);

        label_2 = new QLabel(TileEditDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        fID = new QSpinBox(TileEditDlg);
        fID->setObjectName(QStringLiteral("fID"));

        verticalLayout->addWidget(fID);

        label_3 = new QLabel(TileEditDlg);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        fCharacter = new QLineEdit(TileEditDlg);
        fCharacter->setObjectName(QStringLiteral("fCharacter"));
        fCharacter->setMaxLength(1);

        verticalLayout->addWidget(fCharacter);

        label_4 = new QLabel(TileEditDlg);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        fColor = new QLineEdit(TileEditDlg);
        fColor->setObjectName(QStringLiteral("fColor"));
        fColor->setMaxLength(6);

        verticalLayout->addWidget(fColor);

        label_5 = new QLabel(TileEditDlg);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        fWalkable = new QComboBox(TileEditDlg);
        fWalkable->setObjectName(QStringLiteral("fWalkable"));

        verticalLayout->addWidget(fWalkable);

        label_6 = new QLabel(TileEditDlg);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

        fTransparent = new QComboBox(TileEditDlg);
        fTransparent->setObjectName(QStringLiteral("fTransparent"));

        verticalLayout->addWidget(fTransparent);

        buttonBox = new QDialogButtonBox(TileEditDlg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(TileEditDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), TileEditDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TileEditDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(TileEditDlg);
    } // setupUi

    void retranslateUi(QDialog *TileEditDlg)
    {
        TileEditDlg->setWindowTitle(QApplication::translate("TileEditDlg", "Dialog", 0));
        label->setText(QApplication::translate("TileEditDlg", "Name", 0));
        label_2->setText(QApplication::translate("TileEditDlg", "ID", 0));
        label_3->setText(QApplication::translate("TileEditDlg", "Character", 0));
        label_4->setText(QApplication::translate("TileEditDlg", "Color", 0));
        label_5->setText(QApplication::translate("TileEditDlg", "Walkable", 0));
        fWalkable->clear();
        fWalkable->insertItems(0, QStringList()
         << QApplication::translate("TileEditDlg", "False", 0)
         << QApplication::translate("TileEditDlg", "True", 0)
        );
        label_6->setText(QApplication::translate("TileEditDlg", "Transparent", 0));
        fTransparent->clear();
        fTransparent->insertItems(0, QStringList()
         << QApplication::translate("TileEditDlg", "False", 0)
         << QApplication::translate("TileEditDlg", "True", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class TileEditDlg: public Ui_TileEditDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TILEEDITDLG_H
