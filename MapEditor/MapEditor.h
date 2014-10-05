#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QMainWindow>
#include <World/mapdescription.h>

namespace Ui {
class MapEditor;
}
class QTableWidgetItem;

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
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_actionLoad_triggered();

private:
  Ui::MapEditor *ui;
  int cols;
  int rows;
  MapDescription mapDsc;

};

#endif // MAPEDITOR_H
