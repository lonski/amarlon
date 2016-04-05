#include "spell_select_dialog.h"
#include "ui_spell_select_dialog.h"
#include <enum_mappings.h>

SpellSelectDialog::SpellSelectDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SpellSelectDialog)
{
  ui->setupUi(this);
  ui->comboBox->clear();
  ui->comboBox->addItems( spells );
}

SpellSelectDialog::~SpellSelectDialog()
{
  delete ui;
}

void SpellSelectDialog::on_buttonBox_accepted()
{
  _spellId = ui->comboBox->currentIndex();
}

int SpellSelectDialog::spellId() const
{
  return _spellId;
}

void SpellSelectDialog::setSpellId(int spellId)
{
  _spellId = spellId;
  ui->comboBox->setCurrentIndex(_spellId);
}

void SpellSelectDialog::on_buttonBox_rejected()
{
  _spellId = 0;
}
