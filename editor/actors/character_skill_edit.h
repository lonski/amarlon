#ifndef CHARACTER_SKILL_EDIT_H
#define CHARACTER_SKILL_EDIT_H

#include <QDialog>

namespace Ui {
class CharacterSkillEdit;
}

class CharacterSkillEdit : public QDialog
{
  Q_OBJECT

public:
  explicit CharacterSkillEdit(QWidget *parent = 0);
  ~CharacterSkillEdit();

  int getId() const
  {
    return _id;
  }

  void setId(int id);

  int getLevel() const
  {
    return _level;
  }

  void setLevel(int level);

private slots:
  void on_buttonBox_accepted();
  void on_buttonBox_rejected();

private:
  Ui::CharacterSkillEdit *ui;
  int _id;
  int _level;

};

#endif // CHARACTER_SKILL_EDIT_H
