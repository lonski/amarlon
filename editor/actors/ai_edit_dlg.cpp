#include "ai_edit_dlg.h"
#include "ui_ai_edit_dlg.h"
#include <actors/actors.pb.h>

AiEditDlg::AiEditDlg(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AiEditDlg),
  _ai(nullptr)
{
  ui->setupUi(this);
}

AiEditDlg::~AiEditDlg()
{
  delete ui;
}

void AiEditDlg::setAi(amarlon::proto::ActorData_Ai *ai)
{
  _ai = ai;
  fillForm();
}

void AiEditDlg::on_buttonBox_accepted()
{
  fillAi();
}

void AiEditDlg::fillAi()
{
  if ( _ai )
  {
    _ai->set_type( ui->fType->value() );
  }
}

void AiEditDlg::fillForm()
{
  if ( _ai )
  {
    ui->fType->setValue( _ai->type() );
  }
}
