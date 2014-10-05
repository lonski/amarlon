#include "MapEditor.h"
#include "ui_MapEditor.h"
#include "QFile"
#include "QFileDialog"
#include <iostream>
#include <fstream>

MapEditor::MapEditor(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MapEditor)
{
  ui->setupUi(this);

  cols = 100;
  rows = 60;

  ui->map->setColumnCount(cols);
  ui->map->setRowCount(rows);

  for (int i=0; i < cols; ++i)
    ui->map->setColumnWidth(i, 15);

  for (int i=0; i < rows; ++i)
    ui->map->setRowHeight(i, 15);

  for(int col = 0; col < cols; ++col)
  {
    for (int row = 0; row < rows; ++row)
    {
      ui->map->setItem(row, col, new QTableWidgetItem("#"));
    }
  }
}

MapEditor::~MapEditor()
{
  delete ui;
}

void MapEditor::on_actionSave_triggered()
{
  QString mapStr = "";

  for(int row = 0; row < rows; ++row)
  {
    for (int col = 0; col < cols; ++col)
    {
      QTableWidgetItem* item = ui->map->item(row, col);
      mapStr += ( item->text()[0] );
    }
    mapStr += "\n";
  }

  //save
  QString fileName = QFileDialog::getSaveFileName(this, "Save", "", "Amarlon txt map (*.txt);;All Files (*)");
  QFile file(fileName);
  file.open(QIODevice::WriteOnly);
  file.write(mapStr.toStdString().c_str(), mapStr.size());
  file.close();

  fileName += "dsc";
  mapDsc.save(fileName.toStdString());
}

void MapEditor::on_map_itemChanged(QTableWidgetItem *item)
{
  QList<QTableWidgetItem*> sel = ui->map->selectedItems();
  for (QList<QTableWidgetItem*>::iterator it = sel.begin(); it != sel.end(); ++it)
    (*it)->setText(item->text());
}

void MapEditor::on_map_cellClicked(int row, int column)
{
  ui->aType->setCurrentIndex(-1);

  for (auto it = mapDsc.Actors.begin(); it != mapDsc.Actors.end(); ++it)
  {
    ActorDescription& d = *it;
    if (d.x == column && d.y == row)
    {
      ui->aType->setCurrentIndex((int)d.type);
      break;
    }
  }

  ui->posX->setValue(column);
  ui->posY->setValue(row);
}

void MapEditor::on_pushButton_clicked()
{
    bool exist = false;
    for (auto it = mapDsc.Actors.begin(); it != mapDsc.Actors.end(); ++it)
    {
      ActorDescription& d = *it;
      if (d.x == ui->posX->value() && d.y == ui->posY->value())
      {
        d.type = (ActorType)ui->aType->currentIndex();
        d.x = ui->posX->value();
        d.y = ui->posY->value();
        exist = true;
        break;
      }
    }

    if (!exist)
    {
      ActorDescription actor;
      actor.type = (ActorType)ui->aType->currentIndex();
      actor.x = ui->posX->value();
      actor.y = ui->posY->value();
      mapDsc.Actors.push_back(actor);
      ui->map->item(ui->posY->value(), ui->posX->value())->setBackground( QBrush(QColor(0xFF, 0, 0)) );
    }

    ui->map->clearSelection();
}

void MapEditor::on_pushButton_2_clicked()
{
  for (auto it = mapDsc.Actors.begin(); it != mapDsc.Actors.end(); ++it)
  {
    ActorDescription& d = *it;
    if (d.x == ui->posX->value() && d.y == ui->posY->value())
    {
      ui->aType->setCurrentIndex(-1);
      ui->map->item(ui->posY->value(), ui->posX->value())->setBackground( QBrush(QColor(0xFF, 0xFF, 0xFF)) );
      mapDsc.Actors.erase(it);
      break;
    }
  }
}

void MapEditor::on_actionLoad_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Load", "", "Amarlon txt map (*.txt);;All Files (*)");

  //read map
  std::ifstream ifs(fileName.toStdString());
  std::string line;
  int row = 0;
  while(std::getline(ifs, line))
  {
    for (size_t i = 0; i < line.size(); ++i)
    {
      ui->map->setItem(row, i, new QTableWidgetItem( QString(line[i]) ));
    }
    ++row;
  }
  ifs.close();

  //read description
  mapDsc.Actors.clear();
  mapDsc.load(fileName.toStdString() + "dsc");

  for (auto it = mapDsc.Actors.begin(); it != mapDsc.Actors.end(); ++it)
  {
    ActorDescription& d = *it;
    ui->map->item(d.y, d.x)->setBackground( QBrush(QColor(0xFF, 0x0, 0x0)) );
  }

}
