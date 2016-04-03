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

  ui->fWeaponType->clear();
  ui->fWeaponType->addItems( weapon_types );

  ui->fArmorType->clear();
  ui->fArmorType->addItems( armor_types );

  ui->fAmunitionType->clear();
  ui->fAmunitionType->addItems( amunition_types );

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
    ui->fDamage->setText( _pickable->damage().c_str() );
    ui->fItemSlot->setCurrentIndex( _pickable->item_slot() );
    ui->fPrice->setValue( _pickable->price() );
    ui->fScript->setValue( _pickable->script_id() );
    ui->fStackable->setCurrentIndex( (int)_pickable->stackable() );
    ui->fTarget->setCurrentIndex( _pickable->target_type() );
    ui->fUses->setValue( _pickable->uses_count() );
    ui->fWeight->setValue( _pickable->weight() );
    ui->fSpell->setValue( _pickable->spell_id() );
    ui->fRadius->setValue( _pickable->radius() );
    ui->fRange->setValue( _pickable->range() );

    const amarlon::ItemTypeData& type = _pickable->item_type();
    ui->fCategory->setCurrentIndex( type.category() );
    ui->fWeaponType->setCurrentIndex( type.weapon_type() );
    ui->fArmorType->setCurrentIndex( type.armor_type() );
    ui->fAmunitionType->setCurrentIndex( type.amunition_type() );
  }
}

void PickableEditDlg::fillPickable()
{
  if ( _pickable )
  {
    _pickable->set_amount( ui->fAmount->value() );
    _pickable->set_armor_class( ui->fArmor->value() );
    _pickable->set_damage( ui->fDamage->text().toStdString() );
    _pickable->set_item_slot( ui->fItemSlot->currentIndex() );
    _pickable->set_price( ui->fPrice->value() );
    _pickable->set_script_id( ui->fScript->value() );
    _pickable->set_stackable( (bool)ui->fStackable->currentIndex() );
    _pickable->set_target_type( ui->fTarget->currentIndex() );
    _pickable->set_uses_count( ui->fUses->value() );
    _pickable->set_weight( ui->fWeight->value() );
    _pickable->set_spell_id( ui->fSpell->value() );
    _pickable->set_radius( ui->fRadius->value() );
    _pickable->set_range( ui->fRange->value() );

    amarlon::ItemTypeData* type = _pickable->mutable_item_type();
    type->set_category( ui->fCategory->currentIndex() );
    type->set_weapon_type( ui->fWeaponType->currentIndex() );
    type->set_armor_type( ui->fArmorType->currentIndex() );
    type->set_amunition_type( ui->fAmunitionType->currentIndex() );
  }
}

void PickableEditDlg::on_buttonBox_accepted()
{
  fillPickable();
}
