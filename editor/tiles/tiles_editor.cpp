#include "tiles_editor.h"
#include "ui_tiles_editor.h"
#include <QFileDialog>
#include <fstream>

TilesEditor::TilesEditor(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::TilesEditor)
{
  ui->setupUi(this);
}

TilesEditor::~TilesEditor()
{
  delete ui;
}

void TilesEditor::on_actionOpen_triggered()
{
  QString fn = QFileDialog::getOpenFileName(this, tr("Open Tiles Database"), "", tr("Data Files (*.dat)"));
  if ( !fn.isEmpty() )
  {
    loadDatabase(fn);
  }
}

void TilesEditor::loadDatabase(const QString &fn)
{
  std::ifstream ifs(fn.toStdString().c_str());
  _tilesData.ParseFromIstream(&ifs);
  populate();
}

void TilesEditor::saveDatabase(const QString &fn)
{
  std::ofstream ofs(fn.toStdString().c_str());
  _tilesData.SerializePartialToOstream((&ofs));
}

void TilesEditor::populate()
{
  clear();

  ui->tTable->setRowCount(0);
  ui->tTable->setColumnCount(6);
  ui->tTable->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
  ui->tTable->setHorizontalHeaderItem(1,new QTableWidgetItem("Name"));
  ui->tTable->setHorizontalHeaderItem(2,new QTableWidgetItem("Character"));
  ui->tTable->setHorizontalHeaderItem(3,new QTableWidgetItem("Color"));
  ui->tTable->setHorizontalHeaderItem(4,new QTableWidgetItem("Walkable"));
  ui->tTable->setHorizontalHeaderItem(5,new QTableWidgetItem("Transparent"));

  for( int i=0; i < _tilesData.tile_size(); ++i )
  {
    const amarlon::proto::TileData& tile = _tilesData.tile(i);

    ui->tTable->insertRow( ui->tTable->rowCount() );
    ui->tTable->setItem(ui->tTable->rowCount() - 1, 0, new QTableWidgetItem( QString::number(tile.id()) ));
    ui->tTable->setItem(ui->tTable->rowCount() - 1, 1, new QTableWidgetItem( tile.name().c_str() ));
    ui->tTable->setItem(ui->tTable->rowCount() - 1, 2, new QTableWidgetItem( tile.character().c_str() ));
    ui->tTable->setItem(ui->tTable->rowCount() - 1, 3, new QTableWidgetItem( tile.color().c_str() ));
    ui->tTable->setItem(ui->tTable->rowCount() - 1, 4, new QTableWidgetItem( QString::number(tile.walkable()) ));
    ui->tTable->setItem(ui->tTable->rowCount() - 1, 5, new QTableWidgetItem( QString::number(tile.transparent()) ));
  }
}

void TilesEditor::clear()
{
  ui->tTable->clear();
}

amarlon::proto::TileData* TilesEditor::getTile(std::function<bool (const amarlon::proto::TileData&)> filter)
{
  for( int i=0; i < _tilesData.tile_size(); ++i )
  {
    const amarlon::proto::TileData& tile = _tilesData.tile(i);
    if ( filter(tile) ) return const_cast<amarlon::proto::TileData*>( &tile );
  }
  return nullptr;
}

void TilesEditor::on_actionNew_triggered()
{
  _tilesData = amarlon::proto::TilesData();
  clear();
}

void TilesEditor::on_actionSave_as_triggered()
{
  QString fn = QFileDialog::getSaveFileName(this, tr("Save Tiles Database"), "", tr("Data Files (*.dat)"));
  if ( !fn.isEmpty() )
  {
    saveDatabase(fn);
  }
}

void TilesEditor::on_tTable_cellDoubleClicked(int row, int /*column*/)
{
  auto* item = ui->tTable->item(row, 0);
  if ( item )
  {
    int id = item->text().toInt();
    auto* tile = getTile([&](auto& s){ return s.id() == id; });
    if ( tile )
    {
      _editDlg.setTile( tile );
      _editDlg.exec();
      populate();
    }
  }
}

void TilesEditor::on_actionNew_tile_triggered()
{
  _editDlg.setTile( _tilesData.add_tile() );
  _editDlg.exec();
  populate();
}
