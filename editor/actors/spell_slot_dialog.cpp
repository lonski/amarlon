#include "spell_slot_dialog.h"
#include "ui_spell_slot_dialog.h"
#include <enum_mappings.h>

SpellSlotDialog::SpellSlotDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SpellSlotDialog)
{
  ui->setupUi(this);
  ui->fSpell->addItems(spells);
}

SpellSlotDialog::~SpellSlotDialog()
{
  delete ui;
}

void SpellSlotDialog::on_buttonBox_accepted()
{
  fillSlot();
}

void SpellSlotDialog::fillForm()
{
  if ( _slot )
  {
    ui->fLevel->setValue(_slot->level());
    ui->fPrepared->setCurrentIndex( _slot->isprepared() );
    ui->fSpell->setCurrentIndex( _slot->spell_id() );
  }
}

void SpellSlotDialog::fillSlot()
{
  if ( _slot )
  {
    _slot->set_level(ui->fLevel->value());
    _slot->set_isprepared(ui->fPrepared->currentIndex());
    _slot->set_spell_id(ui->fSpell->currentIndex());
  }
}

amarlon::SpellBookData_SlotData *SpellSlotDialog::getSlot() const
{
  return _slot;
}

void SpellSlotDialog::setSlot(amarlon::SpellBookData_SlotData *slot)
{
  _slot = slot;
  fillForm();
}
