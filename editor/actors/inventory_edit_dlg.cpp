#include "inventory_edit_dlg.h"
#include "ui_inventory_edit_dlg.h"
#include <actor.pb.h>
#include <QInputDialog>
#include <actors_editor.h>
#include <actor_choose.h>
#include <QDebug>

InventoryEditDlg::InventoryEditDlg(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::InventoryEditDlg),
  _inventory(nullptr)
{
  ui->setupUi(this);
}

InventoryEditDlg::~InventoryEditDlg()
{
  delete ui;
}

void InventoryEditDlg::setInventory(amarlon::InventoryData *inventory)
{
  _inventory = inventory;
  fillForm();
}

void InventoryEditDlg::on_buttonBox_accepted()
{
  fillInventory();
}

void InventoryEditDlg::fillInventory()
{
  if ( _inventory )
  {
    _inventory->set_slotcount(ui->fSlotAmount->value());
    _inventory->clear_items();
    _inventory->mutable_items()->CopyFrom(_items);
  }
}

void InventoryEditDlg::fillForm()
{
  if ( _inventory )
  {
    ui->fSlotAmount->setValue( _inventory->slotcount() );
    ui->fItems->clear();

    _items.Clear();
    _items.CopyFrom(_inventory->items());

    for ( int i=0; i < _items.size(); ++i )
    {
      const amarlon::ActorData& actor = _items.Get(i);
      ui->fItems->addItem( QString::number( actor.actor_type() ) + " : " + QString(actor.name().c_str()) );
    }
  }
}

void InventoryEditDlg::on_btnAdd_clicked()
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

void InventoryEditDlg::on_btnEdit_clicked()
{
  int i = ui->fItems->currentRow();
  if ( i >= 0 )
  {
    ActorEditDlg dlg(this);
    dlg.setActor( const_cast<amarlon::ActorData*>(&_items.Get(i)) );
    dlg.exec();
  }
}

void InventoryEditDlg::on_btnDelete_clicked()
{
  auto items = ui->fItems->selectedItems();
  if ( !items.isEmpty() )
  {
    int i = ui->fItems->currentRow();
    _items.DeleteSubrange(i, 1);

    delete items.first();
  }
}
