#include "skill_edit.h"
#include "ui_skill_edit.h"
#include <QDesktopWidget>
#include <enum_mappings.h>

SkillEdit::SkillEdit(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SkillEdit)
{
  ui->setupUi(this);
  move(QApplication::desktop()->screen()->rect().center() - rect().center());
  ui->fTarget->clear();
  ui->fTarget->addItems( target_types );
}

void SkillEdit::setSkill(amarlon::SkillData *skill)
{
  _skill = skill;
  fillForm();
}

SkillEdit::~SkillEdit()
{
  delete ui;
}

void SkillEdit::fillForm()
{
  if ( _skill )
  {
    ui->fID->setValue( _skill->id() );
    ui->fName->setText( _skill->name().c_str() );
    ui->fPassive->setCurrentIndex( (int)_skill->passive() );
    ui->fLevel->setValue( _skill->level() );
    ui->fRadius->setValue( _skill->radius() );
    ui->fRange->setValue( _skill->range() );
    ui->fTarget->setCurrentIndex( _skill->target_type() );
    ui->fDescription->setText( _skill->description().c_str() );
  }
}

void SkillEdit::fillSkill()
{
  if ( _skill )
  {
    _skill->set_id( ui->fID->value() );
    _skill->set_name( ui->fName->text().toStdString() );
    _skill->set_passive( (bool)ui->fPassive->currentIndex() );
    _skill->set_level( ui->fLevel->value() );
    _skill->set_radius( ui->fRadius->value() );
    _skill->set_range( ui->fRange->value() );
    _skill->set_target_type( ui->fTarget->currentIndex() );
    _skill->set_description( ui->fDescription->toPlainText().toStdString() );
  }
}

void SkillEdit::on_buttonBox_accepted()
{
  fillSkill();
  setResult( QDialog::Accepted );
  hide();
}

void SkillEdit::on_buttonBox_rejected()
{
  setResult( QDialog::Rejected );
  hide();
}
