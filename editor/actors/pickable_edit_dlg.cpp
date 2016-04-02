#include "pickable_edit_dlg.h"
#include "ui_pickable_edit_dlg.h"
#include <actor.pb.h>
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

void PickableEditDlg::setPickable(amarlon::PickableData *pickable)
{
  _pickable = pickable;
  fillForm();
}

void PickableEditDlg::fillForm()
{
  if ( _pickable )
  {
    ui->fAmount->setValue( _pickable->amount() );
    ui->fArmor->setValue( _pickable->armor_class() );
    //XXX ui->fCategory->setCurrentIndex( _pickable->category() );
    ui->fDamage->setText( _pickable->damage().c_str() );
    ui->fItemSlot->setCurrentIndex( _pickable->item_slot() );
    ui->fPrice->setValue( _pickable->price() );
    ui->fScript->setValue( _pickable->script_id() );
    ui->fStackable->setCurrentIndex( (int)_pickable->stackable() );
    ui->fTarget->setCurrentIndex( _pickable->target_type() );
    ui->fUses->setValue( _pickable->uses_count() );
    ui->fWeight->setValue( _pickable->weight() );
  }
}

void PickableEditDlg::fillPickable()
{
  if ( _pickable )
  {
    _pickable->set_amount( ui->fAmount->value() );
    _pickable->set_armor_class( ui->fArmor->value() );
    //XXX _pickable->set_category( ui->fCategory->currentIndex() );
    _pickable->set_damage( ui->fDamage->text().toStdString() );
    _pickable->set_item_slot( ui->fItemSlot->currentIndex() );
    _pickable->set_price( ui->fPrice->value() );
    _pickable->set_script_id( ui->fScript->value() );
    _pickable->set_stackable( (bool)ui->fStackable->currentIndex() );
    _pickable->set_target_type( ui->fTarget->currentIndex() );
    _pickable->set_uses_count( ui->fUses->value() );
    _pickable->set_weight( ui->fWeight->value() );
  }
}

void PickableEditDlg::on_buttonBox_accepted()
{
  fillPickable();
}
