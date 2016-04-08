#include "ai_edit_dlg.h"
#include "ui_ai_edit_dlg.h"
#include <actor.pb.h>
#include <enum_mappings.h>

AiEditDlg::AiEditDlg(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AiEditDlg),
  _ai(nullptr)
{
  ui->setupUi(this);
  ui->fType->addItems(ai_types);
}

AiEditDlg::~AiEditDlg()
{
  delete ui;
}

void AiEditDlg::setAi(amarlon::AiData *ai)
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
    _ai->set_type( ui->fType->currentIndex() );
    _ai->set_script( ui->fScript->value() );
  }
}

void AiEditDlg::fillForm()
{
  if ( _ai )
  {
    ui->fType->setCurrentIndex( _ai->type() );
    ui->fScript->setValue( _ai->script() );
  }
}
