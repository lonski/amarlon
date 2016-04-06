#include "wearer_edit_dlg.h"
#include "ui_wearer_edit_dlg.h"
#include <QInputDialog>
#include <enum_mappings.h>
#include <item_slot_dialog.h>
#include <actors_editor.h>
#include <actor_choose.h>

WearerEditDlg::WearerEditDlg(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::WearerEditDlg),
  _wearer(nullptr)
{
  ui->setupUi(this);
}

WearerEditDlg::~WearerEditDlg()
{
  delete ui;
}

void WearerEditDlg::setWearer(amarlon::WearerData *wearer)
{
  _wearer = wearer;
  fillForm();
}

void WearerEditDlg::on_buttonBox_accepted()
{
  fillWearer();
}

void WearerEditDlg::fillWearer()
{
  if ( _wearer )
  {
    _wearer->mutable_item_slots()->Clear();
    for ( int i=0; i < ui->fItemSlots->rowCount(); ++i )
    {
      _wearer->mutable_item_slots()->Add(
            ui->fItemSlots->item(i,0)->text().toInt() );
    }

    _wearer->mutable_equipped_items()->CopyFrom(_items);
  }
}

void WearerEditDlg::fillForm()
{
  if ( _wearer )
  {
    ui->fItemSlots->clear();
    ui->fItemSlots->setRowCount(0);
    ui->fItemSlots->setColumnCount(2);
    ui->fItemSlots->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
    ui->fItemSlots->setHorizontalHeaderItem(1,new QTableWidgetItem("Name"));

    for( int i=0; i < _wearer->item_slots_size(); ++i )
    {
      const auto& slot = _wearer->item_slots(i);

      ui->fItemSlots->insertRow( ui->fItemSlots->rowCount() );
      ui->fItemSlots->setItem(ui->fItemSlots->rowCount() - 1, 0,
                              new QTableWidgetItem( QString::number(slot) ));
      ui->fItemSlots->setItem(ui->fItemSlots->rowCount() - 1, 1,
                              new QTableWidgetItem(
                                slot < item_slots.size() ? item_slots[slot] : "!ERROR!" ));
    }

    _items.Clear();
    _items.CopyFrom(_wearer->equipped_items());
    ui->fItems->clear();
    for ( int i=0; i < _items.size(); ++i )
    {
      const amarlon::ActorData& actor = _items.Get(i);
      ui->fItems->addItem( QString::number( actor.actor_type() ) + " : " + QString(actor.name().c_str()) );
    }
  }
}


void WearerEditDlg::on_btnAdd_clicked()
{
  if ( _wearer )
  {
    ItemSlotDialog dlg;
    dlg.exec();
    if ( dlg.result() == QDialog::Accepted )
    {
      ui->fItemSlots->insertRow( ui->fItemSlots->rowCount() );
      ui->fItemSlots->setItem(ui->fItemSlots->rowCount() - 1, 0,
                              new QTableWidgetItem( QString::number(dlg.getSlot()) ));
      ui->fItemSlots->setItem(ui->fItemSlots->rowCount() - 1, 1,
                              new QTableWidgetItem(
                                dlg.getSlot() < item_slots.size() ? item_slots[dlg.getSlot()] : "!ERROR!" ));
    }
  }
}

void WearerEditDlg::on_btnEdit_clicked()
{
  auto items = ui->fItemSlots->selectedItems();
  if ( !items.isEmpty() )
  {
    auto* item = items.first();
    ItemSlotDialog dlg(this);
    dlg.setSlot( item->text().toInt() );
    dlg.exec();

    if ( dlg.result() == QDialog::Accepted )
    {
      item->setText( QString::number(dlg.getSlot()) );
      items.at(1)->setText( item_slots.size() > dlg.getSlot() ? item_slots[dlg.getSlot()] : "!Error!" );
    }
  }
}

void WearerEditDlg::on_btnDelete_clicked()
{
  if ( ui->fItemSlots->currentRow() >= 0 )
  {
    ui->fItemSlots->removeRow( ui->fItemSlots->currentRow() );
  }
}

void WearerEditDlg::on_btnAddItem_clicked()
{
  ActorsEditor* actor_editor = dynamic_cast<ActorsEditor*>(parent()->parent());
  if ( actor_editor )
  {
    const amarlon::ActorsData& actors = actor_editor->getActorsData();

    ActorChoose dlg;
    dlg.setActorsData(const_cast<amarlon::ActorsData*>(&actors));
    dlg.exec();

    amarlon::ActorData* actor = dlg.getSelected();
    if ( actor )
    {
      ui->fItems->addItem( QString::number( actor->actor_type() ) + " : " + QString(actor->name().c_str()) );
      _items.Add()->CopyFrom(*actor);
    }
  }
}

void WearerEditDlg::on_btnEditItem_clicked()
{
  int i = ui->fItems->currentRow();
  if ( i >= 0 )
  {
    ActorEditDlg dlg(this);
    dlg.setActor( const_cast<amarlon::ActorData*>(&_items.Get(i)) );
    dlg.exec();
  }
}

void WearerEditDlg::on_btnDeleteItem_clicked()
{
  auto items = ui->fItems->selectedItems();
  if ( !items.isEmpty() )
  {
    int i = ui->fItems->currentRow();
    _items.DeleteSubrange(i, 1);

    delete items.first();
  }
}
