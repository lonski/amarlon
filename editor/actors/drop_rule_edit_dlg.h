#ifndef DROP_RULE_EDIT_DLG_H
#define DROP_RULE_EDIT_DLG_H

#include <QDialog>
#include <actor.pb.h>

namespace Ui {
class DropRuleEditDlg;
}

class DropRuleEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit DropRuleEditDlg(QWidget *parent = 0);
  ~DropRuleEditDlg();

  void setRule(amarlon::DropRule* rule);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::DropRuleEditDlg *ui;
  amarlon::DropRule* _rule;

  void fillForm();
  void fillRule();

};

#endif // DROP_RULE_EDIT_DLG_H
