#include "character_edit_dlg.h"
#include "ui_character_edit_dlg.h"
#include <actor.pb.h>
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

void CharacterEditDlg::setCharacter(amarlon::CharacterData *character)
{
  _character = character;
  fillForm();
}

void CharacterEditDlg::fillForm()
{
  if ( _character )
  {
    ui->fArmor->setValue( _character->baseac() );
    ui->fClass->setCurrentIndex( _character->classtype() );
    ui->fDamage->setText( _character->damage().c_str() );
    ui->fExperience->setValue( _character->experience() );
    ui->fHP->setValue( _character->hp() );
    ui->fLevel->setValue( _character->level() );
    ui->fMaxHP->setValue( _character->maxhp() );
    ui->fMorale->setValue( _character->morale() );
    ui->fRace->setCurrentIndex( _character->racetype() );
    ui->fSpeed->setValue( _character->speed() );

    ui->fWIS->setValue( 0 );
    ui->fSTR->setValue( 0 );
    ui->fINT->setValue( 0 );
    ui->fDEX->setValue( 0 );
    ui->fCON->setValue( 0 );
    ui->fCHA->setValue( 0 );

    for ( auto it = _character->abilityscores().begin(); it != _character->abilityscores().end(); ++it )
    {
      /*
        STR = 0,
        INT = 1,
        WIS = 2,
        DEX = 3,
        CON = 4,
        CHA = 5,
        END = 6
        */
      switch(it->first())
      {
        case 0: ui->fSTR->setValue( it->second() ); break;
        case 1: ui->fINT->setValue( it->second() ); break;
        case 2: ui->fWIS->setValue( it->second() ); break;
        case 3: ui->fDEX->setValue( it->second() ); break;
        case 4: ui->fWIS->setValue( it->second() ); break;
        case 5: ui->fCON->setValue( it->second() ); break;
        case 6: ui->fCHA->setValue( it->second() ); break;
        default :;
      }
    }



    ui->fSpells->clear();
    for ( int i=0; i < _character->spellbook().knownspells_size(); ++i )
    {
      ui->fSpells->addItem( QString::number( _character->spellbook().knownspells(i) ) );
    }
  }
}

void CharacterEditDlg::fillCharacter()
{
  if ( _character )
  {
    _character->set_baseac( ui->fArmor->value() );
    _character->set_classtype( ui->fClass->currentIndex() );
    _character->set_damage( ui->fDamage->text().toStdString() );
    _character->set_experience( ui->fExperience->value() );
    _character->set_hp( ui->fHP->value() );
    _character->set_level( ui->fLevel->value() );
    _character->set_maxhp( ui->fMaxHP->value() );
    _character->set_morale( ui->fMorale->value() );
    _character->set_racetype( ui->fRace->currentIndex() );
    _character->set_speed( ui->fSpeed->value() );

    _character->mutable_abilityscores()->Clear();

    /*
      STR = 0,
      INT = 1,
      WIS = 2,
      DEX = 3,
      CON = 4,
      CHA = 5,
      END = 6
      */
    for ( int i =0; i <= 6; ++i)
    {
      auto* p = _character->mutable_abilityscores()->Add();
      p->set_first(i);

      switch(i)
      {
        case 0: p->set_second(ui->fSTR->value()); break;
        case 1: p->set_second(ui->fINT->value()); break;
        case 2: p->set_second(ui->fWIS->value()); break;
        case 3: p->set_second(ui->fDEX->value()); break;
        case 4: p->set_second(ui->fWIS->value()); break;
        case 5: p->set_second(ui->fCON->value()); break;
        case 6: p->set_second(ui->fCHA->value()); break;
        default :;
      }
    }

    _character->mutable_spellbook()->mutable_knownspells()->Clear();
    for ( int i=0; i < ui->fSpells->count(); ++i )
    {
      _character->mutable_spellbook()->mutable_knownspells()->Add( ui->fSpells->item(i)->text().toInt() );
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
