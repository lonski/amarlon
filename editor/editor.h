#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include <spell_editor.h>

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

private:
  Ui::editor *ui;
  SpellEditor _spellsEditor;
};

#endif // EDITOR_H
