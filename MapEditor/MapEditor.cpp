#include "MapEditor.h"
#include "ui_MapEditor.h"
#include "QFile"
#include "QFileDialog"
#include <iostream>
#include <fstream>
#include "xml/rapidxml_print.hpp"
#include "World/map.h"
#include <QDebug>
#include "Actor/actor.h"

using namespace rapidxml;

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

QString MapEditor::dumpTilesToString()
{
  QString mapStr;

  for(int row = 0; row < rows; ++row)
  {
    for (int col = 0; col < cols; ++col)
    {
      QTableWidgetItem* item = ui->map->item(row, col);
      mapStr += ( item->text()[0] );
    }
    mapStr += "\n";
  }

  if (mapStr.size())
    mapStr.remove(mapStr.size()-1, 1);

  return mapStr;
}

void MapEditor::on_actionSave_triggered()
{
  QString fileName = QFileDialog::getSaveFileName(this, "Save", "", "XML (*.xml);;All Files (*)");


  xml_document<> doc;
  xml_node<>* mapsRoot = doc.allocate_node(node_element,"Maps");
  doc.append_node(mapsRoot);

  //map node
  xml_node<>* mapNode = doc.allocate_node(node_element,"Map");
  mapsRoot->append_node(mapNode);

  std::string mapId = std::to_string((int)ui->mapId->currentIndex());
  xml_attribute<>* atrMapId = doc.allocate_attribute("id", doc.allocate_string(mapId.c_str(), mapId.size()));
  mapNode->append_attribute( atrMapId );

  std::string mapWidth = "100";
  xml_attribute<>* atrMapW = doc.allocate_attribute("width", doc.allocate_string(mapWidth.c_str(), mapWidth.size()));
  mapNode->append_attribute( atrMapW );

  std::string mapHeight = "60";
  xml_attribute<>* atrMapH = doc.allocate_attribute("height", doc.allocate_string(mapHeight.c_str(), mapHeight.size()));
  mapNode->append_attribute( atrMapH );

  //tiles
  QString mapStr = dumpTilesToString();
  xml_node<>* tilesNode = doc.allocate_node(node_element, "Tiles", doc.allocate_string(mapStr.toStdString().c_str(), mapStr.size()) );
  mapNode->append_node(tilesNode);

  //actors
  xml_node<>* actorsRoot = doc.allocate_node(node_element, "Actors");
  mapNode->append_node(actorsRoot);

  for (auto aIter = _actors.begin(); aIter != _actors.end(); ++aIter)
  {
    ActorData& data = *aIter;

    xml_node<>* actorNode = doc.allocate_node(node_element,"Actor");
    actorsRoot->append_node(actorNode);

    //id
    std::string aIdStr = std::to_string((int)data.id);
    xml_attribute<>* atrId = doc.allocate_attribute("id", doc.allocate_string(aIdStr.c_str(), aIdStr.size()));
    actorNode->append_attribute( atrId );

    //pos
    std::string posX = std::to_string(data.x);
    std::string posY = std::to_string(data.y);

    xml_attribute<>* atrX = doc.allocate_attribute("x", doc.allocate_string(posX.c_str(), posX.size()));
    xml_attribute<>* atrY = doc.allocate_attribute("y", doc.allocate_string(posY.c_str(), posY.size()));

    actorNode->append_attribute( atrX );
    actorNode->append_attribute( atrY );
  }

  std::ofstream file(fileName.toStdString());
  file << doc;
  file.close();
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
  ui->posX->setValue(column);
  ui->posY->setValue(row);

  for (auto a = _actors.begin(); a != _actors.end(); ++a)
  {
    if (a->x == column && a->y == row)
    {
      ui->aType->setCurrentIndex((int)a->id);
      break;
    }
  }
}

void MapEditor::on_actionLoad_triggered()
{
  //QString fileName = QFileDialog::getOpenFileName(this, "Load", "", "All Files (*)");

  Map::Tiles.loadTiles("d:/tiles.xml");
  Map::Gateway.loadMaps("d:/maps.xml");
  Actor::DB.loadActors("d:/actors.xml");

  currentMap = Map::Gateway.fetch(MapId::GameStart);

  std::string mapStr = currentMap->tilesToStr();

  qDebug() << mapStr.c_str();

//  std::string line;
//  int row = 0;
//  while(std::getline(ifs, line))
//  {
//    for (size_t i = 0; i < line.size(); ++i)
//    {
//      ui->map->setItem(row, i, new QTableWidgetItem( QString(line[i]) ));
//    }
//    ++row;
//  }

  int y = 0;
  int x = 0;
  for (auto it = mapStr.begin(); it != mapStr.end(); ++it)
  {
    if (*it == '\n')
    {
      ++y;
      x = 0;
    }
    else
    {
      ui->map->setItem(y, x, new QTableWidgetItem( QString( *it ) ));
      ++x;
    }
  }

}

void MapEditor::on_saveActor_clicked()
{
  if (ui->aType->currentIndex() > 0)
  {
    ActorData data;
    data.x = ui->posX->value();
    data.y = ui->posY->value();
    data.id = (ActorType)ui->aType->currentIndex();

    _actors.push_back(data);

    ui->map->item(data.y, data.x)->setBackgroundColor(Qt::red);
    ui->map->clearSelection();
  }
}

//remove actor
void MapEditor::on_pushButton_clicked()
{
  int column = ui->posX->value();
  int row = ui->posY->value();

  for (auto a = _actors.begin(); a != _actors.end(); ++a)
  {
    if (a->x == column && a->y == row)
    {
      _actors.erase(a);
      ui->map->item(row, column)->setBackgroundColor(Qt::white);
      break;
    }
  }
}
