#ifndef CHARACTER_EDIT_DLG_H
#define CHARACTER_EDIT_DLG_H

#include <QDialog>
#include <actor.pb.h>

namespace Ui {
class CharacterEditDlg;
}

namespace amarlon {
namespace proto {
class CharacterData;
}
}

class CharacterEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit CharacterEditDlg(QWidget *parent = 0);
  ~CharacterEditDlg();
  void setCharacter(amarlon::CharacterData* character);

private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_buttonBox_accepted();

private:
  Ui::CharacterEditDlg *ui;
  amarlon::CharacterData* _character;

  void fillForm();
  void fillCharacter();

};

#endif // CHARACTER_EDIT_DLG_H
