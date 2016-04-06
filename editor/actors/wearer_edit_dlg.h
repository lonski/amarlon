#ifndef WEARER_EDIT_DLG_H
#define WEARER_EDIT_DLG_H

#include <QDialog>
#include <actor.pb.h>

namespace Ui {
class WearerEditDlg;
}

class WearerEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit WearerEditDlg(QWidget *parent = 0);
  ~WearerEditDlg();

  void setWearer(amarlon::WearerData* wearer);

private slots:
  void on_buttonBox_accepted();
  void on_btnAdd_clicked();
  void on_btnEdit_clicked();
  void on_btnDelete_clicked();
  void on_btnAddItem_clicked();
  void on_btnEditItem_clicked();
  void on_btnDeleteItem_clicked();

private:
  Ui::WearerEditDlg *ui;
  amarlon::WearerData* _wearer;
  ::google::protobuf::RepeatedPtrField< ::amarlon::ActorData > _items;

  void fillWearer();
  void fillForm();

};

#endif // WEARER_EDIT_DLG_H
