#include "openable_edit_dlg.h"
#include "ui_openable_edit_dlg.h"
#include <actor.pb.h>

OpenableEditDlg::OpenableEditDlg(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::OpenableEditDlg),
  _openable(nullptr)
{
  ui->setupUi(this);
}

OpenableEditDlg::~OpenableEditDlg()
{
  delete ui;
}

void OpenableEditDlg::setOpenable(amarlon::OpenableData *openable)
{
  _openable = openable;
  fillForm();
}

void OpenableEditDlg::on_buttonBox_accepted()
{
  fillOpenable();
}

void OpenableEditDlg::fillForm()
{
  if ( _openable )
  {
    ui->fScriptID->setValue( _openable->script_id() );
    ui->fIsLocked->setCurrentIndex( (int)_openable->locked() );
    ui->fIsClosed->setCurrentIndex( (int)_openable->closed() );
    ui->fLockId->setValue( _openable->lock_id() );
    ui->fLockLevel->setValue( _openable->lock_level() );
  }
}

void OpenableEditDlg::fillOpenable()
{
  if ( _openable )
  {
    _openable->set_script_id( ui->fScriptID->value() );
    _openable->set_locked( ui->fIsLocked->currentText() == "True" ? true : false );
    _openable->set_closed( ui->fIsClosed->currentText() == "True" ? true : false );
    _openable->set_lock_id( ui->fLockId->value() );
    _openable->set_lock_level( ui->fLockLevel->value() );
  }
}
