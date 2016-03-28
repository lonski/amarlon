#ifndef ACTORS_EDITOR_H
#define ACTORS_EDITOR_H

#include <QMainWindow>
#include <actors/actors.pb.h>
#include <actors/actor_edit_dlg.h>

namespace Ui {
class ActorsEditor;
}

class ActorsEditor : public QMainWindow
{
  Q_OBJECT

public:
  explicit ActorsEditor(QWidget *parent = 0);
  ~ActorsEditor();

private slots:
  void on_actionNew_triggered();
  void on_actionOpen_triggered();
  void on_actionSave_as_triggered();
  void on_actionNew_actor_triggered();

  void on_aTable_cellDoubleClicked(int row, int column);

  void on_actionDelete_actor_triggered();

private:
  Ui::ActorsEditor *ui;
  amarlon::proto::ActorsData _actorsData;
  ActorEditDlg _editDlg;

  void clear();
  void populate();
  void loadDatabase(const QString &fn);
  void saveDatabase(const QString &fn);
  amarlon::proto::ActorData* getActor(std::function<bool (const amarlon::proto::ActorData&)> filter);

};

#endif // ACTORS_EDITOR_H
