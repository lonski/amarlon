#ifndef OPENABLE_EDIT_DLG_H
#define OPENABLE_EDIT_DLG_H

#include <QDialog>

namespace Ui {
class OpenableEditDlg;
}

namespace amarlon {
namespace proto {
class ActorData_Openable;
}
}

class OpenableEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit OpenableEditDlg(QWidget *parent = 0);
  ~OpenableEditDlg();

  void setOpenable(amarlon::proto::ActorData_Openable* openable);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::OpenableEditDlg *ui;
  amarlon::proto::ActorData_Openable* _openable;

  void fillForm();
  void fillOpenable();

};

#endif // OPENABLE_EDIT_DLG_H
