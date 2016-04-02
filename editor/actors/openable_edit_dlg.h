#ifndef OPENABLE_EDIT_DLG_H
#define OPENABLE_EDIT_DLG_H

#include <QDialog>
#include <actor.pb.h>

namespace Ui {
class OpenableEditDlg;
}

class OpenableEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit OpenableEditDlg(QWidget *parent = 0);
  ~OpenableEditDlg();

  void setOpenable(amarlon::OpenableData* openable);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::OpenableEditDlg *ui;
  amarlon::OpenableData* _openable;

  void fillForm();
  void fillOpenable();

};

#endif // OPENABLE_EDIT_DLG_H
