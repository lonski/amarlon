#ifndef MAPS_EDITOR_H
#define MAPS_EDITOR_H

#include <QMainWindow>
#include <map.pb.h>
#include <maps/map_edit_dialog.h>

namespace Ui {
class MapsEditor;
}

class MapsEditor : public QMainWindow
{
  Q_OBJECT

public:
  explicit MapsEditor(QWidget *parent = 0);
  ~MapsEditor();

private slots:
  void on_actionNew_triggered();
  void on_actionLoad_triggered();
  void on_actionSave_triggered();
  void on_actionDelete_map_triggered();
  void on_actionNew_map_triggered();

  void on_tMaps_cellDoubleClicked(int row, int column);

private:
  Ui::MapsEditor *ui;
  amarlon::MapsData _maps;
  MapEditDialog _editDlg;

  void clear();
  void populate();

};

#endif // MAPS_EDITOR_H
