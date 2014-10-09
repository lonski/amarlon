#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QMainWindow>
#include "Actor/ActorType.h"
#include "DataGateways/MapGateway.h"

namespace Ui {
class MapEditor;
}
class QTableWidgetItem;

struct ActorData
{
  ActorType id;
  int x;
  int y;
};

class MapEditor : public QMainWindow
{
  Q_OBJECT

public:
  explicit MapEditor(QWidget *parent = 0);
  ~MapEditor();

private slots:
  void on_actionSave_triggered();
  void on_map_itemChanged(QTableWidgetItem *item);
  void on_map_cellClicked(int row, int column);
  void on_actionLoad_triggered();

  void on_saveActor_clicked();

  void on_pushButton_clicked();

private:
  Map* currentMap;
  std::vector< ActorData > _actors;
  Ui::MapEditor *ui;
  int cols;
  int rows;

  QString dumpTilesToString();

};

#endif // MAPEDITOR_H
