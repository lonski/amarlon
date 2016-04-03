#ifndef ACTOR_CHOOSE_H
#define ACTOR_CHOOSE_H

#include <QDialog>
#include <actor.pb.h>

namespace Ui {
class ActorChoose;
}

class ActorChoose : public QDialog
{
  Q_OBJECT

public:
  explicit ActorChoose(QWidget *parent = 0);
  ~ActorChoose();

  void setActorsData(amarlon::ActorsData* data);
  amarlon::ActorData* getSelected() const;

private slots:
  void on_table_cellDoubleClicked(int row, int column);

private:
  Ui::ActorChoose *ui;
  amarlon::ActorsData* _data;
  amarlon::ActorData* _selected;
};

#endif // ACTOR_CHOOSE_H
