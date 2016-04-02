#ifndef PICKABLE_EDIT_DLG_H
#define PICKABLE_EDIT_DLG_H

#include <QDialog>
#include <actor.pb.h>

namespace Ui {
class PickableEditDlg;
}

class PickableEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit PickableEditDlg(QWidget *parent = 0);
  ~PickableEditDlg();

  void setPickable(amarlon::PickableData* pickable);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::PickableEditDlg *ui;
  amarlon::PickableData* _pickable;

  void fillForm();
  void fillPickable();

};

#endif // PICKABLE_EDIT_DLG_H
