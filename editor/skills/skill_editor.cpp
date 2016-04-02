#include "skill_editor.h"
#include "ui_skill_editor.h"
#include "enum_mappings.h"
#include <QFileDialog>
#include <QDesktopWidget>
#include <fstream>

SkillEditor::SkillEditor(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SkillEditor),
  _editDlg(this)
{
  ui->setupUi(this);
  move(QApplication::desktop()->screen()->rect().center() - rect().center());
  populate();
}

SkillEditor::~SkillEditor()
{
  delete ui;
}

void SkillEditor::loadDatabase(const QString &fn)
{
  std::ifstream ifs(fn.toStdString().c_str());
  _skillsData.ParseFromIstream(&ifs);
  populate();
}

void SkillEditor::saveDatabase(const QString &fn)
{
  std::ofstream ofs(fn.toStdString().c_str());
  _skillsData.SerializePartialToOstream((&ofs));
}

amarlon::SkillData *SkillEditor::getSkill(std::function<bool (const amarlon::SkillData &)> filter)
{
  for( int i=0; i < _skillsData.skill_size(); ++i )
  {
    amarlon::SkillData* skill = _skillsData.mutable_skill(i);
    if ( skill && filter(*skill) ) return skill;
  }
  return nullptr;
}

void SkillEditor::on_actionOpen_triggered()
{
  QString fn = QFileDialog::getOpenFileName(this, tr("Open Skills Database"), "", tr("Data Files (*.dat)"));
  if ( !fn.isEmpty() )
  {
    loadDatabase(fn);
  }
}

void SkillEditor::on_actionSave_as_triggered()
{
  QString fn = QFileDialog::getSaveFileName(this, tr("Save Skills Database"), "", tr("Data Files (*.dat)"));
  if ( !fn.isEmpty() )
  {
    saveDatabase(fn);
  }
}

void SkillEditor::on_actionNew_file_triggered()
{
  _skillsData = amarlon::SkillsData();
  ui->sTable->clear();
}

void SkillEditor::populate()
{
  ui->sTable->clear();

  ui->sTable->setRowCount(0);
  ui->sTable->setColumnCount(8);
  ui->sTable->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
  ui->sTable->setHorizontalHeaderItem(1,new QTableWidgetItem("Name"));
  ui->sTable->setHorizontalHeaderItem(2,new QTableWidgetItem("Level"));
  ui->sTable->setHorizontalHeaderItem(3,new QTableWidgetItem("Passive"));
  ui->sTable->setHorizontalHeaderItem(4,new QTableWidgetItem("Target type"));
  ui->sTable->setHorizontalHeaderItem(5,new QTableWidgetItem("Range"));
  ui->sTable->setHorizontalHeaderItem(6,new QTableWidgetItem("Radius"));
  ui->sTable->setHorizontalHeaderItem(7,new QTableWidgetItem("Description"));

  for( int i=0; i < _skillsData.skill_size(); ++i )
  {
    const amarlon::SkillData& skill = _skillsData.skill(i);

    ui->sTable->insertRow( ui->sTable->rowCount() );
    ui->sTable->setItem(ui->sTable->rowCount() - 1, 0, new QTableWidgetItem( QString::number(skill.id()) ));
    ui->sTable->setItem(ui->sTable->rowCount() - 1, 1, new QTableWidgetItem( skill.name().c_str() ));
    ui->sTable->setItem(ui->sTable->rowCount() - 1, 2, new QTableWidgetItem( QString::number(skill.level()) ));
    ui->sTable->setItem(ui->sTable->rowCount() - 1, 3, new QTableWidgetItem( skill.passive() ? "True" : "False" ) );
    ui->sTable->setItem(ui->sTable->rowCount() - 1, 4, new QTableWidgetItem( target_types.at(skill.target_type()) ));
    ui->sTable->setItem(ui->sTable->rowCount() - 1, 5, new QTableWidgetItem( QString::number(skill.range()) ));
    ui->sTable->setItem(ui->sTable->rowCount() - 1, 6, new QTableWidgetItem( QString::number(skill.radius()) ));
    ui->sTable->setItem(ui->sTable->rowCount() - 1, 7, new QTableWidgetItem( skill.description().c_str() ));
  }
}

void SkillEditor::on_actionDelete_Skill_triggered()
{
  auto* item = ui->sTable->item(ui->sTable->currentRow(), 0);
  if ( item )
  {
    int id = item->text().toInt();
    int i = 0;
    for( auto it = _skillsData.skill().begin(); it != _skillsData.skill().end(); ++it, ++i )
    {
      if ( it->id() == id )
      {
        _skillsData.mutable_skill()->DeleteSubrange(i, 1);
        populate();
        break;
      }
    }
  }
}

void SkillEditor::on_actionNew_Skill_triggered()
{
  amarlon::SkillData* skill = new amarlon::SkillData;
  _editDlg.setSkill( skill );
  if ( _editDlg.exec() == QDialog::Accepted )
  {
    _skillsData.mutable_skill()->AddAllocated(skill);
    populate();
  }
  else
  {
    delete skill;
  }
}

void SkillEditor::on_sTable_cellDoubleClicked(int row, int)
{
  auto* item = ui->sTable->item(row, 0);
  if ( item )
  {
    int id = item->text().toInt();
    auto* skill = getSkill([&](const amarlon::SkillData& s){ return s.id() == id; });
    if ( skill )
    {
      _editDlg.setSkill( skill );
      _editDlg.exec();
      populate();
    }
  }
}
