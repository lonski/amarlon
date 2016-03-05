#ifndef SPELL_EDIT_H
#define SPELL_EDIT_H

#include <QDialog>

namespace amarlon {
  class SpellData;
}

namespace Ui {
class Spell_Edit;
}

class SpellEdit : public QDialog
{
  Q_OBJECT

public:
  explicit SpellEdit(QWidget *parent = 0);
  void setSpell(amarlon::SpellData* spell);
  ~SpellEdit();

private slots:

  void on_buttonBox_accepted();

private:
  Ui::Spell_Edit *ui;
  amarlon::SpellData* _spell;

  void fillForm();
  void fillSpell();
};

#endif // SPELL_EDIT_H
