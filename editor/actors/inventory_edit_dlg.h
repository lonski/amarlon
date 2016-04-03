#ifndef INVENTORY_EDIT_DLG_H
#define INVENTORY_EDIT_DLG_H

#include <QDialog>
#include <actor.pb.h>

namespace Ui {
class InventoryEditDlg;
}

class InventoryEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit InventoryEditDlg(QWidget *parent = 0);
  ~InventoryEditDlg();

  void setInventory(amarlon::InventoryData* inventory);

private slots:
  void on_buttonBox_accepted();

  void on_btnAdd_clicked();

  void on_btnEdit_clicked();

  void on_btnDelete_clicked();

private:
  Ui::InventoryEditDlg *ui;
  amarlon::InventoryData* _inventory;
  ::google::protobuf::RepeatedPtrField< ::amarlon::ActorData > _items;

  void fillInventory();
  void fillForm();
};

#endif // INVENTORY_EDIT_DLG_H
