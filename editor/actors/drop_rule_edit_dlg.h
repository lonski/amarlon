#ifndef DROP_RULE_EDIT_DLG_H
#define DROP_RULE_EDIT_DLG_H

#include <QDialog>

namespace Ui {
class DropRuleEditDlg;
}

namespace amarlon {
namespace proto {
class ActorData_Destroyable_DropRule;
}
}

class DropRuleEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit DropRuleEditDlg(QWidget *parent = 0);
  ~DropRuleEditDlg();

  void setRule(amarlon::proto::ActorData_Destroyable_DropRule* rule);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::DropRuleEditDlg *ui;
  amarlon::proto::ActorData_Destroyable_DropRule* _rule;

  void fillForm();
  void fillRule();

};

#endif // DROP_RULE_EDIT_DLG_H
