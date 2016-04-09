#ifndef TALKER_EDIT_DIALOG_H
#define TALKER_EDIT_DIALOG_H

#include <QDialog>
#include <actor.pb.h>

namespace Ui {
class TalkerEditDialog;
}

class TalkerEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TalkerEditDialog(QWidget *parent = 0);
    ~TalkerEditDialog();

    amarlon::TalkerData *talker() const;
    void setTalker(amarlon::TalkerData *talker);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::TalkerEditDialog *ui;
    amarlon::TalkerData* _talker;

    void fillForm();
    void fillTalker();
};

#endif // TALKER_EDIT_DIALOG_H
