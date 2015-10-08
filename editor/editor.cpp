#include "editor.h"
#include "ui_editor.h"

editor::editor(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::editor)
{
  ui->setupUi(this);
}

editor::~editor()
{
  delete ui;
}

void editor::on_pushButton_clicked()
{
  _spellsEditor.show();
}
