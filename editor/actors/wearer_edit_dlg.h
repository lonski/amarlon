#ifndef WEARER_EDIT_DLG_H
#define WEARER_EDIT_DLG_H

#include <QDialog>
#include <actors/item_slot_edit_dlg.h>

namespace Ui {
class WearerEditDlg;
}

namespace amarlon {
namespace proto {
class ActorData_Wearer;
}
}

class WearerEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit WearerEditDlg(QWidget *parent = 0);
  ~WearerEditDlg();

  void setWearer(amarlon::proto::ActorData_Wearer* wearer);

private slots:
  void on_buttonBox_accepted();
  void on_btnAdd_clicked();

  void on_btnEdit_clicked();

  void on_btnDelete_clicked();

private:
  Ui::WearerEditDlg *ui;
  amarlon::proto::ActorData_Wearer* _wearer;
  ItemSlotEditDlg _slotEdit;

  void fillWearer();
  void fillForm();

};

#endif // WEARER_EDIT_DLG_H
