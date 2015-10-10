#ifndef PICKABLE_EDIT_DLG_H
#define PICKABLE_EDIT_DLG_H

#include <QDialog>

namespace Ui {
class PickableEditDlg;
}

namespace amarlon {
namespace proto {
class ActorData_Pickable;
}
}

class PickableEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit PickableEditDlg(QWidget *parent = 0);
  ~PickableEditDlg();

  void setPickable(amarlon::proto::ActorData_Pickable* pickable);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::PickableEditDlg *ui;
  amarlon::proto::ActorData_Pickable* _pickable;

  void fillForm();
  void fillPickable();

};

#endif // PICKABLE_EDIT_DLG_H
