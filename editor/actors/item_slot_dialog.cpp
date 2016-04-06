#include "item_slot_dialog.h"
#include "ui_item_slot_dialog.h"
#include <enum_mappings.h>

ItemSlotDialog::ItemSlotDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ItemSlotDialog)
{
  ui->setupUi(this);
  ui->fSlot->addItems(item_slots);
}

ItemSlotDialog::~ItemSlotDialog()
{
  delete ui;
}

void ItemSlotDialog::on_buttonBox_accepted()
{
  _slot = ui->fSlot->currentIndex();
}

int ItemSlotDialog::getSlot() const
{
  return _slot;
}

void ItemSlotDialog::setSlot(int slot)
{
  _slot = slot;
  ui->fSlot->setCurrentIndex( _slot );
}
