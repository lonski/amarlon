#include "trap_edit_dialog.h"
#include "ui_trap_edit_dialog.h"
#include <enum_mappings.h>

TrapEditDialog::TrapEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrapEditDialog)
{
    ui->setupUi(this);
    ui->fTypeId->addItems(trap_id);
}

TrapEditDialog::~TrapEditDialog()
{
    delete ui;
}

void TrapEditDialog::on_buttonBox_accepted()
{
    fillTrap();
}

void TrapEditDialog::fillForm()
{
    if ( _trap )
    {
        ui->fArmed->setCurrentIndex( _trap->is_armed() );
        ui->fDetected->setCurrentIndex( _trap->is_detected() );
        ui->fDifficulty->setValue( _trap->difficulty() );
        ui->fTypeId->setCurrentIndex( _trap->id() );
    }
}

void TrapEditDialog::fillTrap()
{
    if ( _trap )
    {
        _trap->set_is_armed( ui->fArmed->currentIndex() );
        _trap->set_is_detected( ui->fDetected->currentIndex() );
        _trap->set_difficulty( ui->fDifficulty->value() );
        _trap->set_id( ui->fTypeId->currentIndex() );
    }
}

amarlon::TrapData *TrapEditDialog::trap() const
{
    return _trap;
}

void TrapEditDialog::setTrap(amarlon::TrapData *trap)
{
    _trap = trap;
    fillForm();
}
