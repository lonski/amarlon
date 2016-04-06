#ifndef ITEM_SLOT_DIALOG_H
#define ITEM_SLOT_DIALOG_H

#include <QDialog>

namespace Ui {
class ItemSlotDialog;
}

class ItemSlotDialog : public QDialog
{
  Q_OBJECT

public:
  explicit ItemSlotDialog(QWidget *parent = 0);
  ~ItemSlotDialog();

  int getSlot() const;
  void setSlot(int slot);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::ItemSlotDialog *ui;
  int _slot;
};

#endif // ITEM_SLOT_DIALOG_H
