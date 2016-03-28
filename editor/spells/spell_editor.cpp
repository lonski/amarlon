#include "spell_editor.h"
#include "ui_spell_editor.h"
#include <QFileDialog>
#include <QInputDialog>
#include <fstream>
#include <QDebug>
#include <enum_mappings.h>
#include <QDesktopWidget>

SpellEditor::SpellEditor(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::spell_editor),
  _editDlg(this)
{
  ui->setupUi(this);
  move(QApplication::desktop()->screen()->rect().center() - rect().center());
  populate();
}

SpellEditor::~SpellEditor()
{
  delete ui;
}

void SpellEditor::on_actionOpen_triggered()
{
  QString fn = QFileDialog::getOpenFileName(this, tr("Open Spells Database"), "", tr("Data Files (*.dat)"));
  if ( !fn.isEmpty() )
  {
    loadDatabase(fn);
  }
}

void SpellEditor::loadDatabase(const QString &fn)
{
  std::ifstream ifs(fn.toStdString().c_str());
  _spellsData.ParseFromIstream(&ifs);
  populate();
}

void SpellEditor::saveDatabase(const QString &fn)
{
  std::ofstream ofs(fn.toStdString().c_str());
  _spellsData.SerializePartialToOstream((&ofs));
}

void SpellEditor::clear()
{
  ui->sTable->clear();
}

void SpellEditor::populate()
{
  clear();

  ui->sTable->setRowCount(0);
  ui->sTable->setColumnCount(8);
  ui->sTable->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
  ui->sTable->setHorizontalHeaderItem(1,new QTableWidgetItem("Name"));
  ui->sTable->setHorizontalHeaderItem(2,new QTableWidgetItem("Level"));
  ui->sTable->setHorizontalHeaderItem(3,new QTableWidgetItem("Class"));
  ui->sTable->setHorizontalHeaderItem(4,new QTableWidgetItem("Target"));
  ui->sTable->setHorizontalHeaderItem(5,new QTableWidgetItem("Range"));
  ui->sTable->setHorizontalHeaderItem(6,new QTableWidgetItem("Radius"));
  ui->sTable->setHorizontalHeaderItem(7,new QTableWidgetItem("Description"));

  for( int i=0; i < _spellsData.spell_size(); ++i )
  {
    const amarlon::SpellData& spell = _spellsData.spell(i);

    ui->sTable->insertRow( ui->sTable->rowCount() );
    ui->sTable->setItem(ui->sTable->rowCount() - 1, 0, new QTableWidgetItem( QString::number(spell.id()) ));
    ui->sTable->setItem(ui->sTable->rowCount() - 1, 1, new QTableWidgetItem( spell.name().c_str() ));
    ui->sTable->setItem(ui->sTable->rowCount() - 1, 2, new QTableWidgetItem( QString::number(spell.level()) ));
    ui->sTable->setItem(ui->sTable->rowCount() - 1, 3, new QTableWidgetItem( char_classes.at( spell.char_class())));
    ui->sTable->setItem(ui->sTable->rowCount() - 1, 4, new QTableWidgetItem( target_types.at(spell.target_type()) ));
    ui->sTable->setItem(ui->sTable->rowCount() - 1, 5, new QTableWidgetItem( QString::number(spell.range()) ));
    ui->sTable->setItem(ui->sTable->rowCount() - 1, 6, new QTableWidgetItem( QString::number(spell.radius()) ));
    ui->sTable->setItem(ui->sTable->rowCount() - 1, 7, new QTableWidgetItem( spell.description().c_str() ));
  }
}

amarlon::SpellData *SpellEditor::getSpell(std::function<bool (const amarlon::SpellData&)> filter)
{
  for( int i=0; i < _spellsData.spell_size(); ++i )
  {
    const amarlon::SpellData& spell = _spellsData.spell(i);
    if ( filter(spell) ) return const_cast<amarlon::SpellData*>( &spell );
  }
  return nullptr;
}

void SpellEditor::on_actionNew_triggered()
{
  _spellsData = amarlon::SpellsData();
  clear();
}

void SpellEditor::on_actionSpellNew_triggered()
{
  amarlon::SpellData* spell = new amarlon::SpellData;
  _editDlg.setSpell( spell );
  if ( _editDlg.exec() == QDialog::Accepted )
  {
    _spellsData.mutable_spell()->AddAllocated(spell);
    populate();
  }
  else
  {
    delete spell;
  }
}

void SpellEditor::on_sTable_cellDoubleClicked(int row, int /*column*/)
{
  auto* item = ui->sTable->item(row, 0);
  if ( item )
  {
    int id = item->text().toInt();
    auto* spell = getSpell([&](const amarlon::SpellData& s){ return s.id() == id; });
    if ( spell )
    {
      _editDlg.setSpell( spell );
      _editDlg.exec();
      populate();
    }
  }
}

void SpellEditor::on_actionSave_triggered()
{
  QString fn = QFileDialog::getSaveFileName(this, tr("Save Spells Database"), "", tr("Data Files (*.dat)"));
  if ( !fn.isEmpty() )
  {
    saveDatabase(fn);
  }
}

void SpellEditor::on_actionDelete_spell_triggered()
{
  auto* item = ui->sTable->item(ui->sTable->currentRow(), 0);
  if ( item )
  {
    int id = item->text().toInt();
    for( auto it = _spellsData.spell().begin(); it != _spellsData.spell().end(); ++it )
    {
      if ( it->id() == id )
      {
        _spellsData.mutable_spell()->erase(it);
        populate();
        break;
      }
    }
  }
}
