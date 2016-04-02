#ifndef AI_EDIT_DLG_H
#define AI_EDIT_DLG_H

#include <QDialog>
#include <actor.pb.h>

namespace Ui {
class AiEditDlg;
}

class AiEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit AiEditDlg(QWidget *parent = 0);
  ~AiEditDlg();

  void setAi(amarlon::AiData* ai);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::AiEditDlg *ui;
  amarlon::AiData* _ai;

  void fillAi();
  void fillForm();

};

#endif // AI_EDIT_DLG_H
