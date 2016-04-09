#include "maps_editor.h"
#include "ui_mapseditor.h"
#include <enum_mappings.h>
#include <fstream>
#include <QFileDialog>

MapsEditor::MapsEditor(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MapsEditor)
{
  ui->setupUi(this);
}

MapsEditor::~MapsEditor()
{
  delete ui;
}

void MapsEditor::on_actionNew_triggered()
{
  _maps = amarlon::MapsData();
  clear();
}

void MapsEditor::clear()
{
  ui->tMaps->clear();
}

void MapsEditor::populate()
{
  clear();

  ui->tMaps->setRowCount(0);
  ui->tMaps->setColumnCount(2);
  ui->tMaps->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
  ui->tMaps->setHorizontalHeaderItem(1,new QTableWidgetItem("Name"));

  for( int i=0; i < _maps.map_size(); ++i )
  {
    const amarlon::MapData& map = _maps.map(i);

    ui->tMaps->insertRow( ui->tMaps->rowCount() );
    ui->tMaps->setItem(ui->tMaps->rowCount() - 1, 0, new QTableWidgetItem( QString::number(map.id()) ));
    ui->tMaps->setItem(ui->tMaps->rowCount() - 1, 1, new QTableWidgetItem( maps[map.id()] ));
  }
}

void MapsEditor::on_actionLoad_triggered()
{
  QString fn = QFileDialog::getOpenFileName(this, tr("Open Maps Database"), "", tr("Data Files (*.dat)"));
  if ( !fn.isEmpty() )
  {
    std::ifstream ifs(fn.toStdString().c_str());
    _maps.ParseFromIstream(&ifs);
    populate();
  }
}

void MapsEditor::on_actionSave_triggered()
{
  QString fn = QFileDialog::getSaveFileName(this, tr("Save Maps Database"), "", tr("Data Files (*.dat)"));
  if ( !fn.isEmpty() )
  {
    std::ofstream ofs(fn.toStdString().c_str());
    _maps.SerializePartialToOstream((&ofs));
  }
}

void MapsEditor::on_actionDelete_map_triggered()
{
  auto* item = ui->tMaps->item(ui->tMaps->currentRow(), 0);
  if ( item )
  {
    int id = item->text().toInt();
    int i = 0;
    for( auto it = _maps.map().begin(); it != _maps.map().end(); ++it, ++i )
    {
      if ( it->id() == id )
      {
        _maps.mutable_map()->DeleteSubrange(i,1);
        populate();
        break;
      }
    }
  }
}

void MapsEditor::on_actionNew_map_triggered()
{
  auto* map = _maps.add_map();

  map->set_width(100);
  map->set_height(60);
  map->set_id(1);

  for ( int y = 0; y < map->height(); ++y )
  {
    for ( int x = 0; x < map->width(); ++x )
    {
      auto* tile = map->mutable_tiles()->Add();
      tile->set_type( 4 );
    }
  }

  _editDlg.setMap( map );
  _editDlg.show();
  populate();
}

void MapsEditor::on_tMaps_cellDoubleClicked(int row, int column)
{
  auto* item = ui->tMaps->item(row, 0);
  if ( item )
  {
    int id = item->text().toInt();

    amarlon::MapData* map = nullptr;
    for (auto it = _maps.map().begin(); it != _maps.map().end(); ++it )
    {
      if ( it->id() == id )
      {
        map = const_cast<amarlon::MapData*>(&(*it));
        break;
      }
    }

    if ( map )
    {
      _editDlg.setMap( map );
      _editDlg.show();
      populate();
    }
  }
}
