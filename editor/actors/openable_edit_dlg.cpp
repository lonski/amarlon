#include "openable_edit_dlg.h"
#include "ui_openable_edit_dlg.h"
#include <actors/actors.pb.h>

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

void OpenableEditDlg::setOpenable(amarlon::proto::ActorData_Openable *openable)
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
    ui->fScriptID->setValue( _openable->scriptid() );
  }
}

void OpenableEditDlg::fillOpenable()
{
  if ( _openable )
  {
    _openable->set_scriptid( ui->fScriptID->value() );
  }
}
