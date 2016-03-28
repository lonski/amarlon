#ifndef AI_EDIT_DLG_H
#define AI_EDIT_DLG_H

#include <QDialog>

namespace Ui {
class AiEditDlg;
}

namespace amarlon {
namespace proto {
class ActorData_Ai;
}
}

class AiEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit AiEditDlg(QWidget *parent = 0);
  ~AiEditDlg();

  void setAi(amarlon::proto::ActorData_Ai* ai);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::AiEditDlg *ui;
  amarlon::proto::ActorData_Ai* _ai;

  void fillAi();
  void fillForm();

};

#endif // AI_EDIT_DLG_H
