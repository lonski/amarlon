#ifndef ITEM_SLOTEDITDLG_H
#define ITEM_SLOTEDITDLG_H

#include <QDialog>

namespace Ui {
class ItemSlotEditDlg;
}

namespace amarlon {
namespace proto {
class ActorData_Wearer_ItemSlot;
}
}

class ItemSlotEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit ItemSlotEditDlg(QWidget *parent = 0);
  ~ItemSlotEditDlg();

  void setSlot(amarlon::proto::ActorData_Wearer_ItemSlot* slot);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::ItemSlotEditDlg *ui;
  amarlon::proto::ActorData_Wearer_ItemSlot* _slot;

  void fillSlot();
  void fillForm();

};

#endif // ITEM_SLOTEDITDLG_H
