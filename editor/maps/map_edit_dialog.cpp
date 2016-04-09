#include "map_edit_dialog.h"
#include "ui_mapeditdialog.h"
#include <enum_mappings.h>
#include <actor_choose.h>
#include <QFileDialog>
#include <fstream>

MapEditDialog::MapEditDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::MapEditDialog)
{
  ui->setupUi(this);
  ui->tType->addItems(tiles);
}

MapEditDialog::~MapEditDialog()
{
  delete ui;
}

void MapEditDialog::on_buttonBox_accepted()
{
  fillMap();
}

void MapEditDialog::fillForm()
{
  ui->map->setColumnCount( _map->width() );
  ui->map->setRowCount( _map->height() );

  for (int i=0; i < _map->width(); ++i)
    ui->map->setColumnWidth(i, 15);

  for (int i=0; i < _map->height(); ++i)
    ui->map->setRowHeight(i, 15);

  int y(0), x(0);
  for( auto it = _map->tiles().begin(); it != _map->tiles().end(); ++it )
  {
    const amarlon::TileState& tile = *it;
    ui->map->setItem(y, x, new QTableWidgetItem( tiles[tile.type()] ));

    if ( x == _map->width() - 1 )
    {
      x = 0;
      ++y;
    }
    else
    {
      ++x;
    }
  }
}

void MapEditDialog::fillMap()
{
  for ( int y = 0; y < _map->height(); ++y )
  {
    for ( int x = 0; x < _map->width(); ++x )
    {
      QTableWidgetItem* item = ui->map->item(y+1,x+1);
      auto* tile = _map->mutable_tiles(y*_map->width() + x);
      if ( item )
        tile->set_type( tiles.indexOf(QRegExp("["+ item->text() +"]")) );
      else
        tile->set_type( 0 );
    }
  }
}

void MapEditDialog::fillTableWithActors()
{
  int x = ui->tX->text().toInt();
  int y = ui->tY->text().toInt();

  if ( y*_map->width() + x < _map->tiles_size() )
  {
    ui->tActors->clear();
    ui->tActors->setRowCount(0);
    ui->tActors->setColumnCount(2);
    ui->tActors->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
    ui->tActors->setHorizontalHeaderItem(1,new QTableWidgetItem("Name"));

    for( int i=0; i < _map->actors_size(); ++i )
    {
      const amarlon::ActorData& actor = _map->actors(i);
      if ( actor.x() == x && actor.y() == y )
      {
        ui->tActors->insertRow( ui->tActors->rowCount() );
        ui->tActors->setItem(ui->tActors->rowCount() - 1, 0, new QTableWidgetItem( QString::number(actor.actor_type()) ));
        ui->tActors->setItem(ui->tActors->rowCount() - 1, 1, new QTableWidgetItem( actors[actor.actor_type()] ));
      }
    }
  }
}

amarlon::MapData *MapEditDialog::map() const
{
  return _map;
}

void MapEditDialog::setMap(amarlon::MapData *map)
{
  _map = map;
  fillForm();
}

void MapEditDialog::on_map_itemChanged(QTableWidgetItem *item)
{
  QList<QTableWidgetItem*> sel = ui->map->selectedItems();
  for (QList<QTableWidgetItem*>::iterator it = sel.begin(); it != sel.end(); ++it)
    (*it)->setText(item->text());

}

void MapEditDialog::on_map_cellDoubleClicked(int row, int column)
{

}

void MapEditDialog::on_map_cellClicked(int row, int column)
{
    const amarlon::TileState& tile = _map->tiles(row*_map->width() + column);
    ui->tType->setCurrentIndex(tile.type());

    ui->tX->setText( QString::number(column - 1) );
    ui->tY->setText( QString::number(row - 1) );

    fillTableWithActors();
}

void MapEditDialog::on_pushButton_2_clicked()
{
  ActorChoose dlg;
  dlg.setActorsData(&_actorsData);
  dlg.exec();

  amarlon::ActorData* actor = dlg.getSelected();
  if ( actor )
  {
    amarlon::ActorData* added = _map->mutable_actors()->Add();
    added->CopyFrom(*actor);
    added->set_x( ui->tX->text().toInt() );
    added->set_y( ui->tY->text().toInt() );

    ui->tActors->insertRow( ui->tActors->rowCount() );
    ui->tActors->setItem(ui->tActors->rowCount() - 1, 0, new QTableWidgetItem( QString::number(actor->actor_type()) ));
    ui->tActors->setItem(ui->tActors->rowCount() - 1, 1, new QTableWidgetItem( actors[actor->actor_type()] ));
  }
}

void MapEditDialog::on_pushButton_4_clicked()
{
  QString fn = QFileDialog::getOpenFileName(this, tr("Open Actors Database"), "", tr("Data Files (*.dat)"));
  if ( !fn.isEmpty() )
  {
    std::ifstream ifs(fn.toStdString().c_str());
    _actorsData.ParseFromIstream(&ifs);
  }
}
