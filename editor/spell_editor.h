#ifndef SPELL_EDITOR_H
#define SPELL_EDITOR_H

#include <QMainWindow>
#include <spells.pb.h>
#include <QListWidgetItem>
#include <spell_edit.h>
#include <QTableWidgetItem>
#include <functional>

namespace Ui {
class spell_editor;
}

class SpellEditor : public QMainWindow
{
  Q_OBJECT

public:
  explicit SpellEditor(QWidget *parent = 0);
  ~SpellEditor();

private slots:
  void on_actionOpen_triggered();
  void on_actionNew_triggered();
  void on_actionSpellNew_triggered();
  void on_sTable_cellDoubleClicked(int row, int column);
  void on_actionSave_triggered();

private:
  Ui::spell_editor *ui;
  amarlon::proto::SpellsData _spellsData;
  SpellEdit _editDlg;

  void loadDatabase(const QString& fn);
  void saveDatabase(const QString& fn);
  void clear();
  void populate();
  amarlon::proto::SpellData* getSpellByName(const QString& name);
  amarlon::proto::SpellData* getSpell(std::function<bool(const amarlon::proto::SpellData&)> filter );

};

#endif // SPELL_EDITOR_H
