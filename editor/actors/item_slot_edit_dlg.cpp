#include "item_slot_edit_dlg.h"
#include "ui_item_slot_edit_dlg.h"
#include <actors/actors.pb.h>
#include <enum_mappings.h>

ItemSlotEditDlg::ItemSlotEditDlg(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ItemSlotEditDlg),
  _slot(nullptr)
{
  ui->setupUi(this);

  ui->fSlotType->clear();
  ui->fSlotType->addItems( item_slots );
}

ItemSlotEditDlg::~ItemSlotEditDlg()
{
  delete ui;
}

void ItemSlotEditDlg::setSlot(amarlon::proto::ActorData_Wearer_ItemSlot* slot)
{
  _slot = slot;
  fillForm();
}

void ItemSlotEditDlg::on_buttonBox_accepted()
{
  fillSlot();
}

void ItemSlotEditDlg::fillSlot()
{
  if ( _slot )
  {
    _slot->set_id( ui->fSlotType->currentIndex() );
    _slot->set_item( ui->fItem->value() );
  }
}

void ItemSlotEditDlg::fillForm()
{
  if ( _slot )
  {
    ui->fSlotType->setCurrentIndex( _slot->id() );
    ui->fItem->setValue( _slot->item() );
  }
}
