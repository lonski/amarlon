#include "talker_edit_dialog.h"
#include "ui_talkereditdialog.h"

TalkerEditDialog::TalkerEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TalkerEditDialog)
{
    ui->setupUi(this);
}

TalkerEditDialog::~TalkerEditDialog()
{
    delete ui;
}

void TalkerEditDialog::on_buttonBox_accepted()
{
    fillTalker();
}

void TalkerEditDialog::fillForm()
{
    if ( _talker )
    {
        ui->fId->setValue( _talker->id() );
    }
}

void TalkerEditDialog::fillTalker()
{
    if ( _talker )
    {
        _talker->set_id( ui->fId->value() );
    }
}

amarlon::TalkerData *TalkerEditDialog::talker() const
{
    return _talker;
}

void TalkerEditDialog::setTalker(amarlon::TalkerData *talker)
{
    _talker = talker;
    fillForm();
}
