#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QMainWindow>
#include "Actor/ActorType.h"
#include "DataGateways/MapGateway.h"
#include <QListWidgetItem>
#include <QKeyEvent>

namespace Ui {
class MapEditor;
}

class QTableWidgetItem;

struct ActorData
{
  amarlon::ActorType id;
  int x;
  int y;

  ActorData(amarlon::ActorType id = amarlon::ActorType::Null, int x = 0, int y = 0)
    : id(id)
    , x(x)
    , y(y)
  {}
};

class MapEditor : public QMainWindow
{
  Q_OBJECT

public:
  explicit MapEditor(QWidget *parent = 0);
  ~MapEditor();

  void dumpActorsToList(int row, int column);
private slots:
  void on_actionSave_triggered();
  void on_map_itemChanged(QTableWidgetItem *item);
  void on_map_cellClicked(int row, int column);
  void on_actionLoad_triggered();
  void on_saveActor_clicked();
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_aList_itemClicked(QListWidgetItem *item);

private:
  std::shared_ptr<amarlon::Map> currentMap;
  std::vector< ActorData > _actors;
  Ui::MapEditor *ui;
  int cols;
  int rows;

  QString dumpTilesToString();

};

#endif // MAPEDITOR_H
