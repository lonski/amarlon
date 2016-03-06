#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include <spell_editor.h>
#include <tiles_editor.h>
#include <skill_editor.h>
//#include <actors/actors_editor.h>

namespace Ui {
class editor;
}

class editor : public QMainWindow
{
  Q_OBJECT

public:
  explicit editor(QWidget *parent = 0);
  ~editor();

private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();

  void on_pushButton_4_clicked();

private:
  Ui::editor *ui;
  SpellEditor _spellsEditor;
  SkillEditor _skillsEditor;
  TilesEditor _tilesEditor;
  //ActorsEditor _actorsEditor;
};

#endif // EDITOR_H
