#ifndef TILE_EDIT_DLG_H
#define TILE_EDIT_DLG_H

#include <QDialog>

namespace Ui {
class TileEditDlg;
}

namespace amarlon {
class TileData;
}

class TileEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit TileEditDlg(QWidget *parent = 0);
  ~TileEditDlg();

  void setTile(amarlon::TileData* tile);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::TileEditDlg *ui;
  amarlon::TileData* _tile;

  void fillForm();
  void fillTile();

};

#endif // TILE_EDIT_DLG_H
