#include "spell_edit.h"
#include "ui_spell_edit.h"
#include <spell.pb.h>
#include <enum_mappings.h>
#include <QDesktopWidget>

SpellEdit::SpellEdit(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::Spell_Edit)
  , _spell(nullptr)
{
  ui->setupUi(this);
  move(QApplication::desktop()->screen()->rect().center() - rect().center());
  ui->fClass->clear();
  ui->fTarget->clear();
  ui->fClass->addItems( char_classes );
  ui->fTarget->addItems( target_types );
}

void SpellEdit::setSpell(amarlon::SpellData* spell)
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
    ui->fClass->setCurrentIndex( _spell->char_class() );
    ui->fLevel->setValue( _spell->level() );
    ui->fRadius->setValue( _spell->radius() );
    ui->fRange->setValue( _spell->range() );
    ui->fTarget->setCurrentIndex( _spell->target_type() );
    ui->fDescription->setText( _spell->description().c_str() );
  }
}

void SpellEdit::fillSpell()
{
  if ( _spell )
  {
    _spell->set_id( ui->fID->value() );
    _spell->set_name( ui->fName->text().toStdString() );
    _spell->set_char_class( ui->fClass->currentIndex() );
    _spell->set_level( ui->fLevel->value() );
    _spell->set_radius( ui->fRadius->value() );
    _spell->set_range( ui->fRange->value() );
    _spell->set_target_type( ui->fTarget->currentIndex() );
    _spell->set_description( ui->fDescription->toPlainText().toStdString() );
  }
}

void SpellEdit::on_buttonBox_accepted()
{
    fillSpell();
}
