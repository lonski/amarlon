#include "inventory_edit_dlg.h"
#include "ui_inventory_edit_dlg.h"
#include <actors/actors.pb.h>
#include <QInputDialog>

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

void InventoryEditDlg::setInventory(amarlon::proto::ActorData_Inventory *inventory)
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
    _inventory->set_slotamount(ui->fSlotAmount->value());
    _inventory->clear_item();

    for ( int i = 0; i < ui->fItems->count(); ++i )
      _inventory->add_item( ui->fItems->item(i)->text().toInt() );
  }
}

void InventoryEditDlg::fillForm()
{
  if ( _inventory )
  {
    ui->fSlotAmount->setValue( _inventory->slotamount() );
    ui->fItems->clear();
    for ( int i=0; i < _inventory->item_size(); ++i )
    {
      ui->fItems->addItem( QString::number( _inventory->item(i) ) );
    }
  }
}

void InventoryEditDlg::on_btnAdd_clicked()
{
  QString id = QInputDialog::getText(this, "Enter Actor ID", "Enter Item ID:");
  if ( ui->fItems->findItems(id, Qt::MatchExactly).isEmpty() )
  {
    ui->fItems->addItem(id);
  }
}

void InventoryEditDlg::on_btnEdit_clicked()
{
  auto items = ui->fItems->selectedItems();
  if ( !items.isEmpty() )
  {
    auto* item = items.first();
    QString id = QInputDialog::getText(this, "Enter Actor ID", "Enter Item ID:", QLineEdit::Normal, item->text() );
    item->setText( id );
  }
}

void InventoryEditDlg::on_btnDelete_clicked()
{
  auto items = ui->fItems->selectedItems();
  if ( !items.isEmpty() )
  {
    delete items.first();
  }
}
