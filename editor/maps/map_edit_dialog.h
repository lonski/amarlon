#ifndef MAP_EDIT_DIALOG_H
#define MAP_EDIT_DIALOG_H

#include <QDialog>
#include <map.pb.h>
#include <QTableWidgetItem>

namespace Ui {
class MapEditDialog;
}

class MapEditDialog : public QDialog
{
  Q_OBJECT

public:
  explicit MapEditDialog(QWidget *parent = 0);
  ~MapEditDialog();

  amarlon::MapData *map() const;
  void setMap(amarlon::MapData *map);

private slots:
  void on_buttonBox_accepted();

  void on_map_itemChanged(QTableWidgetItem *item);

  void on_map_cellDoubleClicked(int row, int column);

  void on_map_cellClicked(int row, int column);

  void on_pushButton_2_clicked();

  void on_pushButton_4_clicked();

private:
  Ui::MapEditDialog *ui;
  amarlon::MapData* _map;
  amarlon::ActorsData _actorsData;

  void fillForm();
  void fillMap();
  void fillTableWithActors();
};

#endif // MAP_EDIT_DIALOG_H
