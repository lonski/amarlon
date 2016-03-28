#ifndef DESTROYABLE_EDIT_DLG_H
#define DESTROYABLE_EDIT_DLG_H

#include <QDialog>
#include <actors/drop_rule_edit_dlg.h>

namespace Ui {
class DestroyableEditDlg;
}

namespace amarlon {
namespace proto {
class ActorData_Destroyable;
}
}

class DestroyableEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit DestroyableEditDlg(QWidget *parent = 0);
  ~DestroyableEditDlg();

  void setDestroyable(amarlon::proto::ActorData_Destroyable* destroyable);

private slots:
  void on_btnAdd_clicked();

  void on_btnEdit_clicked();

  void on_btnDelete_clicked();

private:
  Ui::DestroyableEditDlg *ui;
  amarlon::proto::ActorData_Destroyable* _destroyable;
  DropRuleEditDlg _dropRulEdit;

  void fillForm();

};

#endif // DESTROYABLE_EDIT_DLG_H
