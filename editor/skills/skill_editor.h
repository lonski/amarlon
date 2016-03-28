#ifndef SKILL_EDITOR_H
#define SKILL_EDITOR_H

#include <QMainWindow>
#include <skill.pb.h>
#include <QListWidgetItem>
#include <skill_edit.h>
#include <QTableWidgetItem>
#include <functional>

namespace Ui {
class SkillEditor;
}

class SkillEditor : public QMainWindow
{
  Q_OBJECT

public:
  explicit SkillEditor(QWidget *parent = 0);
  ~SkillEditor();

private slots:
  void on_actionOpen_triggered();
  void on_actionSave_as_triggered();
  void on_actionNew_file_triggered();
  void on_actionDelete_Skill_triggered();

  void on_actionNew_Skill_triggered();

  void on_sTable_cellDoubleClicked(int row, int column);

private:
  Ui::SkillEditor *ui;
  amarlon::SkillsData _skillsData;
  SkillEdit _editDlg;

  void populate();
  void loadDatabase(const QString& fn);
  void saveDatabase(const QString& fn);

  amarlon::SkillData* getSkill(std::function<bool(const amarlon::SkillData&)> filter );

};

#endif // SKILL_EDITOR_H
