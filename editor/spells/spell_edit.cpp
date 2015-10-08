#include "spell_edit.h"
#include "ui_spell_edit.h"
#include <spells.pb.h>
#include <enum_mappings.h>

SpellEdit::SpellEdit(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::Spell_Edit)
  , _spell(nullptr)
{
  ui->setupUi(this);
  ui->fClass->clear();
  ui->fTarget->clear();
  ui->fClass->addItems( char_classes );
  ui->fTarget->addItems( target_types );
}

void SpellEdit::setSpell(amarlon::proto::SpellData* spell)
{
  _spell = spell;
  fillForm();
}

SpellEdit::~SpellEdit()
{
  delete ui;
}

void SpellEdit::fillForm()
{
  if ( _spell )
  {
    ui->fID->setValue( _spell->id() );
    ui->fName->setText( _spell->name().c_str() );
    ui->fClass->setCurrentIndex( _spell->class_() );
    ui->fLevel->setValue( _spell->level() );
    ui->fRadius->setValue( _spell->radius() );
    ui->fRange->setValue( _spell->range() );
    ui->fTarget->setCurrentIndex( _spell->target() );
  }
}

void SpellEdit::fillSpell()
{
  if ( _spell )
  {
    _spell->set_id( ui->fID->value() );
    _spell->set_name( ui->fName->text().toStdString() );
    _spell->set_class_( ui->fClass->currentIndex() );
    _spell->set_level( ui->fLevel->value() );
    _spell->set_radius( ui->fRadius->value() );
    _spell->set_range( ui->fRange->value() );
    _spell->set_target( ui->fTarget->currentIndex() );
  }
}

void SpellEdit::on_buttonBox_accepted()
{
    fillSpell();
}
