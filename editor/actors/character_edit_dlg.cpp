#include "character_edit_dlg.h"
#include "ui_character_edit_dlg.h"
#include <actors/actors.pb.h>
#include <QInputDialog>
#include <enum_mappings.h>

CharacterEditDlg::CharacterEditDlg(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::CharacterEditDlg),
  _character(nullptr)
{
  ui->setupUi(this);

  ui->fClass->clear();
  ui->fClass->addItems( char_classes );

  ui->fRace->clear();
  ui->fRace->addItems( races );
}

CharacterEditDlg::~CharacterEditDlg()
{
  delete ui;
}

void CharacterEditDlg::setCharacter(amarlon::proto::ActorData_Character *character)
{
  _character = character;
  fillForm();
}

void CharacterEditDlg::fillForm()
{
  if ( _character )
  {
    ui->fArmor->setValue( _character->armor() );
    ui->fClass->setCurrentIndex( _character->class_() );
    ui->fDamage->setText( _character->damage().c_str() );
    ui->fExperience->setValue( _character->experience() );
    ui->fHP->setValue( _character->hp() );
    ui->fHPBonus->setValue( _character->hpbonus() );
    ui->fLevel->setValue( _character->level() );
    ui->fMaxHP->setValue( _character->maxhp() );
    ui->fMorale->setValue( _character->morale() );
    ui->fRace->setCurrentIndex( _character->race() );
    ui->fSpeed->setValue( _character->speed() );

    if ( _character->has_abilityscores() )
    {
      ui->fWIS->setValue( _character->abilityscores().wis() );
      ui->fSTR->setValue( _character->abilityscores().str() );
      ui->fINT->setValue( _character->abilityscores().int_() );
      ui->fDEX->setValue( _character->abilityscores().dex() );
      ui->fCON->setValue( _character->abilityscores().con() );
      ui->fCHA->setValue( _character->abilityscores().cha() );
    }
    else
    {
      ui->fWIS->setValue( 0 );
      ui->fSTR->setValue( 0 );
      ui->fINT->setValue( 0 );
      ui->fDEX->setValue( 0 );
      ui->fCON->setValue( 0 );
      ui->fCHA->setValue( 0 );
    }

    ui->fSpells->clear();
    for ( int i=0; i < _character->spells_size(); ++i )
    {
      ui->fSpells->addItem( QString::number( _character->spells(i) ) );
    }
  }
}

void CharacterEditDlg::fillCharacter()
{
  if ( _character )
  {
    _character->set_armor( ui->fArmor->value() );
    _character->set_class_( ui->fClass->currentIndex() );
    _character->set_damage( ui->fDamage->text().toStdString() );
    _character->set_experience( ui->fExperience->value() );
    _character->set_hp( ui->fHP->value() );
    _character->set_hpbonus( ui->fHPBonus->value() );
    _character->set_level( ui->fLevel->value() );
    _character->set_maxhp( ui->fMaxHP->value() );
    _character->set_morale( ui->fMorale->value() );
    _character->set_race( ui->fRace->currentIndex() );
    _character->set_speed( ui->fSpeed->value() );

    if ( !_character->has_abilityscores() )
    {
      _character->set_allocated_abilityscores( new amarlon::proto::ActorData_Character_AbilityScores );
    }

    _character->mutable_abilityscores()->set_wis( ui->fWIS->value() );
    _character->mutable_abilityscores()->set_str( ui->fSTR->value() );
    _character->mutable_abilityscores()->set_int_( ui->fINT->value() );
    _character->mutable_abilityscores()->set_dex( ui->fDEX->value() );
    _character->mutable_abilityscores()->set_con( ui->fCON->value() );
    _character->mutable_abilityscores()->set_cha( ui->fCHA->value() );

    _character->clear_spells();
    for ( int i=0; i < ui->fSpells->count(); ++i )
    {
      _character->add_spells( ui->fSpells->item(i)->text().toInt() );
    }
  }
}

void CharacterEditDlg::on_pushButton_clicked()
{
  QString id = QInputDialog::getText(this, "Enter Spell ID", "Enter Spell ID:");
  if ( ui->fSpells->findItems(id, Qt::MatchExactly).isEmpty() )
  {
    ui->fSpells->addItem(id);
  }
}

void CharacterEditDlg::on_pushButton_2_clicked()
{
  auto items = ui->fSpells->selectedItems();
  if ( !items.isEmpty() )
  {
    auto* item = items.first();
    QString id = QInputDialog::getText(this, "Enter Spell ID", "Enter new Spell ID:", QLineEdit::Normal, item->text() );
    item->setText( id );
  }
}

void CharacterEditDlg::on_pushButton_3_clicked()
{
  auto items = ui->fSpells->selectedItems();
  if ( !items.isEmpty() )
  {
    delete items.first();
  }
}

void CharacterEditDlg::on_buttonBox_accepted()
{
  fillCharacter();
}
