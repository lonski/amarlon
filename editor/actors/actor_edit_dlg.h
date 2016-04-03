#ifndef ACTOR_EDIT_DLG_H
#define ACTOR_EDIT_DLG_H

#include <QDialog>
#include <QListWidgetItem>
#include <actors/pickable_edit_dlg.h>
#include <actors/openable_edit_dlg.h>
#include <actors/ai_edit_dlg.h>
#include <actors/wearer_edit_dlg.h>
#include <actors/destroyable_edit_dlg.h>
#include <actors/inventory_edit_dlg.h>
#include <actors/character_edit_dlg.h>

namespace Ui {
class ActorEditDlg;
}

namespace amarlon {
namespace proto {
class ActorData;
}
}

class ActorEditDlg : public QDialog
{
  Q_OBJECT

public:
  explicit ActorEditDlg(QWidget *parent = 0);
  ~ActorEditDlg();

  void setActor(amarlon::ActorData* actor);

private:
  Ui::ActorEditDlg *ui;
  amarlon::ActorData* _actor;
  PickableEditDlg _pickableEdit;
  OpenableEditDlg _openableEdit;
  AiEditDlg _aiEdit;
  WearerEditDlg _wearerEdit;
  DestroyableEditDlg _destroyableEdit;
  InventoryEditDlg _inventoryEdit;
  CharacterEditDlg _characterEdit;

private slots:
  void new_pickable();
  void new_inventory();
  void new_character();
  void new_destroyable();
  void new_wearer();
  void new_ai();
  void new_openable();

  void fillForm();
  void fillActor();

  void on_pushButton_2_clicked();
  void on_pushButton_clicked();
  void on_lFeatures_itemDoubleClicked(QListWidgetItem *item);
  void on_pushButton_4_clicked();
  void on_cancelBtn_clicked();
};

#endif // ACTOR_EDIT_DLG_H
