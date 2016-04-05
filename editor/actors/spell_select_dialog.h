#ifndef SPELL_SELECT_DIALOG_H
#define SPELL_SELECT_DIALOG_H

#include <QDialog>

namespace Ui {
class SpellSelectDialog;
}

class SpellSelectDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SpellSelectDialog(QWidget *parent = 0);
  ~SpellSelectDialog();

  int spellId() const;
  void setSpellId(int spellId);

private slots:
  void on_buttonBox_accepted();

  void on_buttonBox_rejected();

private:
  Ui::SpellSelectDialog *ui;
  int _spellId;
};

#endif // SPELL_SELECT_DIALOG_H
