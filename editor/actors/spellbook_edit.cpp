#include "spellbook_edit.h"
#include "ui_spellbook_edit.h"
#include <enum_mappings.h>
#include <spell_select_dialog.h>
#include <spell_slot_dialog.h>

SpellBookEdit::SpellBookEdit(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SpellBookEdit),
  _spellbook(nullptr)
{
  ui->setupUi(this);
}

SpellBookEdit::~SpellBookEdit()
{
  delete ui;
}

void SpellBookEdit::setSpellbook(amarlon::SpellBookData *sb)
{
  _spellbook = sb;
  fillForm();
}

void SpellBookEdit::on_buttonBox_accepted()
{
  fillSpellBook();
}

void SpellBookEdit::fillSpellBook()
{
  if ( _spellbook )
  {
    _spellbook->mutable_knownspells()->Clear();
    for ( int i=0; i < ui->fKnownSpells->rowCount(); ++i )
    {
      _spellbook->mutable_knownspells()->Add(
            ui->fKnownSpells->item(i,0)->text().toInt() );
    }

    _spellbook->mutable_spellslots()->Clear();
    for ( int i=0; i < ui->fSpellSlots->rowCount(); ++i )
    {
      amarlon::SpellBookData_SlotData* slot = _spellbook->mutable_spellslots()->Add();
      slot->set_level( ui->fSpellSlots->item(i, 0)->text().toInt() );
      slot->set_isprepared( ui->fSpellSlots->item(i, 1)->text() == "True" ? true : false );
      slot->set_spell_id( ui->fSpellSlots->item(i, 2)->text().toInt() );
    }
  }
}

void SpellBookEdit::fillForm()
{
  ui->fKnownSpells->clear();
  ui->fKnownSpells->setRowCount(0);
  ui->fKnownSpells->setColumnCount(2);
  ui->fKnownSpells->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
  ui->fKnownSpells->setHorizontalHeaderItem(1,new QTableWidgetItem("Name"));

  ui->fSpellSlots->clear();
  ui->fSpellSlots->setRowCount(0);
  ui->fSpellSlots->setColumnCount(4);
  ui->fSpellSlots->setHorizontalHeaderItem(0,new QTableWidgetItem("Level"));
  ui->fSpellSlots->setHorizontalHeaderItem(1,new QTableWidgetItem("isPrepared"));
  ui->fSpellSlots->setHorizontalHeaderItem(2,new QTableWidgetItem("Spell ID"));
  ui->fSpellSlots->setHorizontalHeaderItem(3,new QTableWidgetItem("Spell Name"));

  if ( _spellbook )
  {
    for( auto it = _spellbook->knownspells().begin(); it != _spellbook->knownspells().end(); ++it)
    {
      ui->fKnownSpells->insertRow( ui->fKnownSpells->rowCount() );
      ui->fKnownSpells->setItem(ui->fKnownSpells->rowCount() - 1, 0,
                           new QTableWidgetItem( QString::number(*it) ));
      ui->fKnownSpells->setItem(ui->fKnownSpells->rowCount() - 1, 1,
                           new QTableWidgetItem( spells.size() > *it ? spells[*it] : "!Error!" ));
    }

    for( auto it = _spellbook->spellslots().begin(); it != _spellbook->spellslots().end(); ++it)
    {
      const amarlon::SpellBookData_SlotData& slot = *it;

      ui->fSpellSlots->insertRow( ui->fSpellSlots->rowCount() );

      ui->fSpellSlots->setItem(ui->fSpellSlots->rowCount() - 1, 0,
                           new QTableWidgetItem( QString::number(slot.level()) ));
      ui->fSpellSlots->setItem(ui->fSpellSlots->rowCount() - 1, 1,
                           new QTableWidgetItem( slot.isprepared() ? "True" : "False" ));
      ui->fSpellSlots->setItem(ui->fSpellSlots->rowCount() - 1, 2,
                           new QTableWidgetItem( QString::number(slot.spell_id()) ));
      ui->fSpellSlots->setItem(ui->fSpellSlots->rowCount() - 1, 3,
                           new QTableWidgetItem(
                                 spells.size() > slot.spell_id() ? spells[slot.spell_id()] : "!Error!" ));
    }
  }
}

void SpellBookEdit::on_btnAddKnown_clicked()
{
  SpellSelectDialog dlg(this);
  dlg.exec();
  if ( dlg.result() == QDialog::Accepted )
  {
    ui->fKnownSpells->insertRow( ui->fKnownSpells->rowCount() );
    ui->fKnownSpells->setItem(ui->fKnownSpells->rowCount() - 1, 0,
                         new QTableWidgetItem( QString::number(dlg.spellId()) ));
    ui->fKnownSpells->setItem(ui->fKnownSpells->rowCount() - 1, 1,
                         new QTableWidgetItem( spells.size() > dlg.spellId() ? spells[dlg.spellId()] : "!Error!" ));
  }
}

void SpellBookEdit::on_btnEditKnown_clicked()
{
  auto items = ui->fKnownSpells->selectedItems();
  if ( !items.isEmpty() )
  {
    auto* item = items.first();
    SpellSelectDialog dlg(this);
    dlg.setSpellId( item->text().toInt() );
    dlg.exec();

    if ( dlg.result() == QDialog::Accepted )
    {
      item->setText( QString::number(dlg.spellId()) );
      items.at(1)->setText( spells.size() > dlg.spellId() ? spells[dlg.spellId()] : "!Error!" );
    }
  }
}

void SpellBookEdit::on_btnDeleteKnown_clicked()
{
  if ( ui->fKnownSpells->currentRow() >= 0 )
  {
    ui->fKnownSpells->removeRow( ui->fKnownSpells->currentRow() );
  }
}

void SpellBookEdit::on_btnAddSlot_clicked()
{
  SpellSlotDialog dlg(this);
  amarlon::SpellBookData_SlotData slot;
  dlg.setSlot(&slot);
  dlg.exec();

  if ( dlg.result() == QDialog::Accepted )
  {
    ui->fSpellSlots->insertRow( ui->fSpellSlots->rowCount() );

    ui->fSpellSlots->setItem(ui->fSpellSlots->rowCount() - 1, 0,
                         new QTableWidgetItem( QString::number(slot.level()) ));
    ui->fSpellSlots->setItem(ui->fSpellSlots->rowCount() - 1, 1,
                         new QTableWidgetItem( slot.isprepared() ? "True" : "False" ));
    ui->fSpellSlots->setItem(ui->fSpellSlots->rowCount() - 1, 2,
                         new QTableWidgetItem( QString::number(slot.spell_id()) ));
    ui->fSpellSlots->setItem(ui->fSpellSlots->rowCount() - 1, 3,
                         new QTableWidgetItem(
                               spells.size() > slot.spell_id() ? spells[slot.spell_id()] : "!Error!" ));
  }
}

void SpellBookEdit::on_btnEditSlot_clicked()
{
  auto items = ui->fSpellSlots->selectedItems();
  if ( !items.isEmpty() )
  {
    SpellSlotDialog dlg(this);

    amarlon::SpellBookData_SlotData slot;
    slot.set_level( items[0]->text().toInt() );
    slot.set_isprepared( items[1]->text() == "True" ? true : false );
    slot.set_spell_id( items[2]->text().toInt() );

    dlg.setSlot( &slot );

    dlg.exec();

    if ( dlg.result() == QDialog::Accepted )
    {
      items[0]->setText( QString::number(slot.level() ) );
      items[1]->setText( slot.isprepared() ? "True" : "False" );
      items[2]->setText( QString::number(slot.spell_id() ) );
      items[3]->setText( spells.size() > slot.spell_id() ? spells[slot.spell_id()] : "!Error!" );
    }
  }
}

void SpellBookEdit::on_btnDeleteSlot_clicked()
{
  if ( ui->fSpellSlots->currentRow() >= 0 )
  {
    ui->fSpellSlots->removeRow( ui->fSpellSlots->currentRow() );
  }
}
