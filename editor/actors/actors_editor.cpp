#include "actors_editor.h"
#include "ui_actors_editor.h"
#include <QFileDialog>
#include <fstream>
#include <QDesktopWidget>

ActorsEditor::ActorsEditor(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ActorsEditor)
{
  ui->setupUi(this);
  move(QApplication::desktop()->screen()->rect().center() - rect().center());
  populate();
}

ActorsEditor::~ActorsEditor()
{
  delete ui;
}

void ActorsEditor::clear()
{
  ui->aTable->clear();
}

void ActorsEditor::populate()
{
  clear();

  ui->aTable->setRowCount(0);
  ui->aTable->setColumnCount(8);
  ui->aTable->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
  ui->aTable->setHorizontalHeaderItem(1,new QTableWidgetItem("Name"));
  ui->aTable->setHorizontalHeaderItem(2,new QTableWidgetItem("Symbol"));
  ui->aTable->setHorizontalHeaderItem(3,new QTableWidgetItem("Color"));
  ui->aTable->setHorizontalHeaderItem(4,new QTableWidgetItem("Blocks"));
  ui->aTable->setHorizontalHeaderItem(5,new QTableWidgetItem("FoV Only"));
  ui->aTable->setHorizontalHeaderItem(6,new QTableWidgetItem("Transparent"));
  ui->aTable->setHorizontalHeaderItem(7,new QTableWidgetItem("Description"));

  for( int i=0; i < _actorsData.actor_size(); ++i )
  {
    const amarlon::proto::ActorData& actor = _actorsData.actor(i);

    ui->aTable->insertRow( ui->aTable->rowCount() );
    ui->aTable->setItem(ui->aTable->rowCount() - 1, 0, new QTableWidgetItem( QString::number(actor.id()) ));
    ui->aTable->setItem(ui->aTable->rowCount() - 1, 1, new QTableWidgetItem( actor.name().c_str() ));
    ui->aTable->setItem(ui->aTable->rowCount() - 1, 2, new QTableWidgetItem( actor.symbol().c_str() ));
    ui->aTable->setItem(ui->aTable->rowCount() - 1, 3, new QTableWidgetItem( actor.color().c_str() ));
    ui->aTable->setItem(ui->aTable->rowCount() - 1, 4, new QTableWidgetItem( actor.blocks() ? "Yes" : "No" ));
    ui->aTable->setItem(ui->aTable->rowCount() - 1, 5, new QTableWidgetItem( actor.fovonly() ? "Yes" : "No" ));
    ui->aTable->setItem(ui->aTable->rowCount() - 1, 6, new QTableWidgetItem( actor.transparent() ? "Yes" : "No" ));
    ui->aTable->setItem(ui->aTable->rowCount() - 1, 7, new QTableWidgetItem( actor.description().c_str() ));
  }
}

void ActorsEditor::on_actionNew_triggered()
{
  _actorsData = amarlon::proto::ActorsData();
  clear();
}

void ActorsEditor::loadDatabase(const QString &fn)
{
  std::ifstream ifs(fn.toStdString().c_str());
  _actorsData.ParseFromIstream(&ifs);
  populate();
}

void ActorsEditor::saveDatabase(const QString &fn)
{
  std::ofstream ofs(fn.toStdString().c_str());
  _actorsData.SerializePartialToOstream((&ofs));
}

void ActorsEditor::on_actionOpen_triggered()
{
  QString fn = QFileDialog::getOpenFileName(this, tr("Open Actors Database"), "", tr("Data Files (*.dat)"));
  if ( !fn.isEmpty() )
  {
    loadDatabase(fn);
  }
}

void ActorsEditor::on_actionSave_as_triggered()
{
  QString fn = QFileDialog::getSaveFileName(this, tr("Save Actors Database"), "", tr("Data Files (*.dat)"));
  if ( !fn.isEmpty() )
  {
    saveDatabase(fn);
  }
}

void ActorsEditor::on_actionNew_actor_triggered()
{
  _editDlg.setActor( _actorsData.add_actor() );
  _editDlg.exec();
  populate();
}

amarlon::proto::ActorData* ActorsEditor::getActor(std::function<bool (const amarlon::proto::ActorData&)> filter)
{
  for( int i=0; i < _actorsData.actor_size(); ++i )
  {
    const amarlon::proto::ActorData& actor = _actorsData.actor(i);
    if ( filter(actor) ) return const_cast<amarlon::proto::ActorData*>( &actor );
  }
  return nullptr;
}

void ActorsEditor::on_aTable_cellDoubleClicked(int row, int /*column*/)
{
  auto* item = ui->aTable->item(row, 0);
  if ( item )
  {
    int id = item->text().toInt();
    auto* actor = getActor([&](auto& s){ return s.id() == id; });
    if ( actor )
    {
      _editDlg.setActor( actor );
      _editDlg.exec();
      populate();
    }
  }
}

void ActorsEditor::on_actionDelete_actor_triggered()
{
  auto* item = ui->aTable->item(ui->aTable->currentRow(), 0);
  if ( item )
  {
    int id = item->text().toInt();
    for( auto it = _actorsData.actor().begin(); it != _actorsData.actor().end(); ++it )
    {
      if ( it->id() == id )
      {
        _actorsData.mutable_actor()->erase(it);
        populate();
        break;
      }
    }
  }
}
