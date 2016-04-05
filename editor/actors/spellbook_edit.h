#ifndef SPELLBOOK_EDIT_H
#define SPELLBOOK_EDIT_H

#include <QDialog>
#include <actor.pb.h>

namespace Ui {
class SpellBookEdit;
}

class SpellBookEdit : public QDialog
{
  Q_OBJECT

public:
  explicit SpellBookEdit(QWidget *parent = 0);
  ~SpellBookEdit();

  void setSpellbook(amarlon::SpellBookData* sb);

private slots:
  void on_buttonBox_accepted();

  void on_btnAddKnown_clicked();

  void on_btnEditKnown_clicked();

  void on_btnDeleteKnown_clicked();

  void on_btnAddSlot_clicked();

  void on_btnEditSlot_clicked();

  void on_btnDeleteSlot_clicked();

private:
  Ui::SpellBookEdit *ui;
  amarlon::SpellBookData* _spellbook;

  void fillSpellBook();
  void fillForm();
};

#endif // SPELLBOOK_EDIT_H
