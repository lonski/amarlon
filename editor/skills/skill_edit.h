#ifndef SKILL_EDIT_H
#define SKILL_EDIT_H

#include <QDialog>
#include <skill.pb.h>

namespace Ui {
class SkillEdit;
}

class SkillEdit : public QDialog
{
  Q_OBJECT

public:
  explicit SkillEdit(QWidget *parent = 0);
  void setSkill(amarlon::SkillData* skill);
  ~SkillEdit();

private slots:
  void on_buttonBox_accepted();

  void on_buttonBox_rejected();

private:
  Ui::SkillEdit *ui;
  amarlon::SkillData* _skill;

  void fillForm();
  void fillSkill();
};

#endif // SKILL_EDIT_H
