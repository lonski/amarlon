#ifndef TILES_EDITOR_H
#define TILES_EDITOR_H

#include <QMainWindow>
#include <tile_edit_dlg.h>
#include <tile.pb.h>

namespace Ui {
class TilesEditor;
}

namespace amarlon {
  class TilesData;
}

class TilesEditor : public QMainWindow
{
  Q_OBJECT

public:
  explicit TilesEditor(QWidget *parent = 0);
  ~TilesEditor();

private slots:
  void on_actionOpen_triggered();

  void on_actionNew_triggered();

  void on_actionSave_as_triggered();

  void on_tTable_cellDoubleClicked(int row, int column);

  void on_actionNew_tile_triggered();

  void on_actionDelete_tile_triggered();

private:
  Ui::TilesEditor *ui;
  amarlon::TilesData _tilesData;
  TileEditDlg _editDlg;

  amarlon::TileData* getTile(std::function<bool (const amarlon::TileData&)> filter);
  void loadDatabase(const QString &fn);
  void saveDatabase(const QString &fn);
  void populate();
  void clear();

};

#endif // TILES_EDITOR_H
