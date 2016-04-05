#ifndef SPELL_SLOT_DIALOG_H
#define SPELL_SLOT_DIALOG_H

#include <QDialog>
#include <actor.pb.h>

namespace Ui {
class SpellSlotDialog;
}

class SpellSlotDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SpellSlotDialog(QWidget *parent = 0);
  ~SpellSlotDialog();

  amarlon::SpellBookData_SlotData *getSlot() const;
  void setSlot(amarlon::SpellBookData_SlotData *slot);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::SpellSlotDialog *ui;
  amarlon::SpellBookData_SlotData* _slot;

  void fillForm();
  void fillSlot();
};

#endif // SPELL_SLOT_DIALOG_H
