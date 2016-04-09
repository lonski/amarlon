#ifndef TRAP_EDIT_DIALOG_H
#define TRAP_EDIT_DIALOG_H

#include <QDialog>
#include <actor.pb.h>

namespace Ui {
class TrapEditDialog;
}

class TrapEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrapEditDialog(QWidget *parent = 0);
    ~TrapEditDialog();

    amarlon::TrapData *trap() const;
    void setTrap(amarlon::TrapData *trap);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::TrapEditDialog *ui;
    amarlon::TrapData* _trap;

    void fillForm();
    void fillTrap();
};

#endif // TRAP_EDIT_DIALOG_H
