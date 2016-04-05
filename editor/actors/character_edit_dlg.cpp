#include "character_edit_dlg.h"
#include "ui_character_edit_dlg.h"
#include <actor.pb.h>
#include <QInputDialog>
#include <enum_mappings.h>
#include <character_skill_edit.h>
#include <spellbook_edit.h>

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

  ui->fCharType->clear();
  ui->fCharType->addItems( character_types );

  ui->fTeam->clear();
  ui->fTeam->addItems( relation_teams );
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
    ui->fTeam->setCurrentIndex( _character->team() );
    ui->fCharType->setCurrentIndex( _character->charactertype() );

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



    ui->fModifiers->clear();
    for ( int i=0; i < _character->modifiers_size(); ++i )
    {
      ui->fModifiers->addItem( _character->modifiers(i).c_str() );
    }

    ui->fSkills->clear();
    ui->fSkills->setRowCount(0);
    ui->fSkills->setColumnCount(3);
    ui->fSkills->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
    ui->fSkills->setHorizontalHeaderItem(1,new QTableWidgetItem("Name"));
    ui->fSkills->setHorizontalHeaderItem(2,new QTableWidgetItem("Level"));

    for ( auto sIt = _character->skills().begin(); sIt != _character->skills().end(); ++sIt )
    {
      const amarlon::IntIntPair& skill = *sIt;

      ui->fSkills->insertRow( ui->fSkills->rowCount() );
      ui->fSkills->setItem(ui->fSkills->rowCount() - 1, 0,
                           new QTableWidgetItem( QString::number(skill.first()) ));
      ui->fSkills->setItem(ui->fSkills->rowCount() - 1, 1,
                           new QTableWidgetItem( skills.size() > skill.first() ? skills[skill.first()] : "!Error!" ));
      ui->fSkills->setItem(ui->fSkills->rowCount() - 1, 2,
                           new QTableWidgetItem( QString::number(skill.second()) ));

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
    _character->set_team( ui->fTeam->currentIndex() );
    _character->set_charactertype( ui->fCharType->currentIndex() );

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

    _character->mutable_modifiers()->Clear();
    for ( int i=0; i < ui->fModifiers->count(); ++i )
    {
      *_character->mutable_modifiers()->Add() = ui->fModifiers->item(i)->text().toStdString();
    }

    _character->mutable_skills()->Clear();
    for ( int r = 0; r < ui->fSkills->rowCount(); ++r )
    {
      amarlon::IntIntPair* skill = _character->mutable_skills()->Add();
      skill->set_first( ui->fSkills->item(r,0)->text().toInt() );
      skill->set_second( ui->fSkills->item(r,2)->text().toInt() );
    }
  }
}

void CharacterEditDlg::on_pushButton_clicked()
{
  QString mod = QInputDialog::getText(this, "Enter modifier pattern", "Enter modifier pattern:");
  if ( !mod.isEmpty() )
  {
    ui->fModifiers->addItem(mod);
  }
}

void CharacterEditDlg::on_pushButton_2_clicked()
{
  auto items = ui->fModifiers->selectedItems();
  if ( !items.isEmpty() )
  {
    auto* item = items.first();
    QString id = QInputDialog::getText(this, "Enter modifier pattern", "Enter new modifier pattern:", QLineEdit::Normal, item->text() );
    item->setText( id );
  }
}

void CharacterEditDlg::on_pushButton_3_clicked()
{
  auto items = ui->fModifiers->selectedItems();
  if ( !items.isEmpty() )
  {
    auto* item = items.first();
    for ( int i=0; i < _character->modifiers_size(); ++i )
    {
      if ( _character->modifiers(i) == item->text().toStdString() )
      {
        _character->mutable_modifiers()->DeleteSubrange(i, 1);
        break;
      }
    }
    delete item;
  }
}

void CharacterEditDlg::on_buttonBox_accepted()
{
  fillCharacter();
}

void CharacterEditDlg::on_btnAddSkill_clicked()
{
  CharacterSkillEdit dlg;
  dlg.exec();
  if ( dlg.result() == QDialog::Accepted )
  {
    ui->fSkills->insertRow( ui->fSkills->rowCount() );
    ui->fSkills->setItem(ui->fSkills->rowCount() - 1, 0,
                         new QTableWidgetItem( QString::number( dlg.getId() ) ));
    ui->fSkills->setItem(ui->fSkills->rowCount() - 1, 1,
                         new QTableWidgetItem( skills.size() > dlg.getId() ? skills[dlg.getId()] : "!Error!" ));
    ui->fSkills->setItem(ui->fSkills->rowCount() - 1, 2,
                         new QTableWidgetItem( QString::number(dlg.getLevel()) ));
  }
}

void CharacterEditDlg::on_btnEditSkill_clicked()
{
  auto* item = ui->fSkills->item(ui->fSkills->currentRow(), 0);
  auto* level_item = ui->fSkills->item(ui->fSkills->currentRow(), 2);
  if ( item && level_item)
  {
    int id = item->text().toInt();
    int level = level_item->text().toInt();

    CharacterSkillEdit dlg;
    dlg.setId(id);
    dlg.setLevel(level);
    dlg.exec();

    if ( dlg.result() == QDialog::Accepted )
    {
      item->setText( QString::number(dlg.getId()) );
      level_item->setText( QString::number(dlg.getLevel()) );
    }
  }
}

void CharacterEditDlg::on_btnDeleteSkill_clicked()
{
  if ( ui->fSkills->currentRow() >= 0 )
  {
    ui->fSkills->removeRow( ui->fSkills->currentRow() );
  }
}

void CharacterEditDlg::on_btnEditSpellbook_clicked()
{
  SpellBookEdit dlg(this);
  dlg.setSpellbook( _character->mutable_spellbook() );
  dlg.exec();
}
