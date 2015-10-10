#ifndef INVENTORY_EDIT_DLG_H
#define INVENTORY_EDIT_DLG_H

#include <QDialog>

namespace Ui {
class InventoryEditDlg;
}

namespace amarlon {
namespace proto {
class ActorData_Inventory;
}
}

class InventoryEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit InventoryEditDlg(QWidget *parent = 0);
  ~InventoryEditDlg();

  void setInventory(amarlon::proto::ActorData_Inventory* inventory);

private slots:
  void on_buttonBox_accepted();

  void on_btnAdd_clicked();

  void on_btnEdit_clicked();

  void on_btnDelete_clicked();

private:
  Ui::InventoryEditDlg *ui;
  amarlon::proto::ActorData_Inventory* _inventory;

  void fillInventory();
  void fillForm();
};

#endif // INVENTORY_EDIT_DLG_H
