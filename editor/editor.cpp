#include "editor.h"
#include "ui_editor.h"
#include <QDesktopWidget>

editor::editor(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::editor)
{
  ui->setupUi(this);
  move(QApplication::desktop()->screen()->rect().center() - rect().center());
}

editor::~editor()
{
  delete ui;
}

void editor::on_pushButton_clicked()
{
  _spellsEditor.show();
}

void editor::on_pushButton_2_clicked()
{
  _tilesEditor.show();
}

void editor::on_pushButton_3_clicked()
{
  _actorsEditor.show();
}

void editor::on_pushButton_4_clicked()
{
  _skillsEditor.show();
}
