#include "drop_rule_edit_dlg.h"
#include "ui_drop_rule_edit_dlg.h"
#include <actor.pb.h>
#include <enum_mappings.h>

DropRuleEditDlg::DropRuleEditDlg(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DropRuleEditDlg),
  _rule(nullptr)
{
  ui->setupUi(this);
  ui->fItem->addItems(actors);
}

DropRuleEditDlg::~DropRuleEditDlg()
{
  delete ui;
}

void DropRuleEditDlg::setRule(amarlon::DropRule *rule)
{
  _rule = rule;
  fillForm();
}

void DropRuleEditDlg::fillForm()
{
  if ( _rule )
  {
    ui->fChance->setValue( _rule->chance() / 100.f );
    ui->fItem->setCurrentIndex( _rule->actor_id() );
    ui->fMin->setValue( _rule->min() );
    ui->fMax->setValue( _rule->max() );
  }
}

void DropRuleEditDlg::fillRule()
{
  if ( _rule )
  {
    _rule->set_chance( ui->fChance->value() * 100 );
    _rule->set_actor_id( ui->fItem->currentIndex() );
    _rule->set_max( ui->fMax->value() );
    _rule->set_min( ui->fMin->value() );
  }
}

void DropRuleEditDlg::on_buttonBox_accepted()
{
  fillRule();
}
