#include "character_skill_edit.h"
#include "ui_character_skill_edit.h"
#include <enum_mappings.h>

CharacterSkillEdit::CharacterSkillEdit(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::CharacterSkillEdit)
  , _id(0)
  , _level(0)
{
  ui->setupUi(this);
  ui->fID->clear();
  ui->fID->addItems( skills );
}

CharacterSkillEdit::~CharacterSkillEdit()
{
  delete ui;
}

void CharacterSkillEdit::setId(int id)
{
  _id = id;
  ui->fID->setCurrentIndex( _id );
}

void CharacterSkillEdit::setLevel(int level)
{
  _level = level;
  ui->fLevel->setValue(_level);
}

void CharacterSkillEdit::on_buttonBox_accepted()
{
  _id = ui->fID->currentIndex();
  _level = ui->fLevel->value();
}

void CharacterSkillEdit::on_buttonBox_rejected()
{
    _id = 0;
    _level = 0;
}
