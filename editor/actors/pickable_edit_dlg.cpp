#include "pickable_edit_dlg.h"
#include "ui_pickable_edit_dlg.h"
#include <actors/actors.pb.h>
#include <enum_mappings.h>

PickableEditDlg::PickableEditDlg(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::PickableEditDlg)
{
  ui->setupUi(this);

  ui->fTarget->clear();
  ui->fTarget->addItems( target_types );

  ui->fCategory->clear();
  ui->fCategory->addItems( pickable_categories );

  ui->fItemSlot->clear();
  ui->fItemSlot->addItems( item_slots );
}

PickableEditDlg::~PickableEditDlg()
{
  delete ui;
}

void PickableEditDlg::setPickable(amarlon::proto::ActorData_Pickable *pickable)
{
  _pickable = pickable;
  fillForm();
}

void PickableEditDlg::fillForm()
{
  if ( _pickable )
  {
    ui->fAmount->setValue( _pickable->amount() );
    ui->fArmor->setValue( _pickable->armor() );
    ui->fCategory->setCurrentIndex( _pickable->category() );
    ui->fDamage->setText( _pickable->damage().c_str() );
    ui->fItemSlot->setCurrentIndex( _pickable->itemslot() );
    ui->fPrice->setValue( _pickable->price() );
    ui->fScript->setValue( _pickable->scriptid() );
    ui->fStackable->setCurrentIndex( (int)_pickable->stackable() );
    ui->fTarget->setCurrentIndex( _pickable->target() );
    ui->fUses->setValue( _pickable->uses() );
    ui->fWeight->setValue( _pickable->weight() );
  }
}

void PickableEditDlg::fillPickable()
{
  if ( _pickable )
  {
    _pickable->set_amount( ui->fAmount->value() );
    _pickable->set_armor( ui->fArmor->value() );
    _pickable->set_category( ui->fCategory->currentIndex() );
    _pickable->set_damage( ui->fDamage->text().toStdString() );
    _pickable->set_itemslot( ui->fItemSlot->currentIndex() );
    _pickable->set_price( ui->fPrice->value() );
    _pickable->set_scriptid( ui->fScript->value() );
    _pickable->set_stackable( (bool)ui->fStackable->currentIndex() );
    _pickable->set_target( ui->fTarget->currentIndex() );
    _pickable->set_uses( ui->fUses->value() );
    _pickable->set_weight( ui->fWeight->value() );
  }
}

void PickableEditDlg::on_buttonBox_accepted()
{
  fillPickable();
}
