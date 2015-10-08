#ifndef TILE_EDIT_DLG_H
#define TILE_EDIT_DLG_H

#include <QDialog>

namespace Ui {
class TileEditDlg;
}

namespace amarlon {
namespace proto {
class TileData;
}
}

class TileEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit TileEditDlg(QWidget *parent = 0);
  ~TileEditDlg();

  void setTile(amarlon::proto::TileData* tile);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::TileEditDlg *ui;
  amarlon::proto::TileData* _tile;

  void fillForm();
  void fillTile();

};

#endif // TILE_EDIT_DLG_H
