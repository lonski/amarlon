#include "actor_choose.h"
#include "ui_actor_choose.h"

ActorChoose::ActorChoose(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::ActorChoose)
  , _data(nullptr)
  , _selected(nullptr)
{
  ui->setupUi(this);
}

ActorChoose::~ActorChoose()
{
  delete ui;
}

void ActorChoose::setActorsData(amarlon::ActorsData *data)
{
  _data = data;
  ui->table->clear();

  ui->table->setRowCount(0);
  ui->table->setColumnCount(2);
  ui->table->setHorizontalHeaderItem(0,new QTableWidgetItem("ID"));
  ui->table->setHorizontalHeaderItem(1,new QTableWidgetItem("Name"));

  for( int i=0; i < _data->actor_size(); ++i )
  {
    const amarlon::ActorData& actor = _data->actor(i);

    ui->table->insertRow( ui->table->rowCount() );
    ui->table->setItem(ui->table->rowCount() - 1, 0, new QTableWidgetItem( QString::number(actor.actor_type()) ));
    ui->table->setItem(ui->table->rowCount() - 1, 1, new QTableWidgetItem( actor.name().c_str() ));
  }

}

amarlon::ActorData *ActorChoose::getSelected() const
{
  return _selected;
}

void ActorChoose::on_table_cellDoubleClicked(int row, int)
{
  auto* item = ui->table->item(row, 0);
  if ( item )
  {
    int id = item->text().toInt();

    for( int i=0; i < _data->actor_size(); ++i )
    {
      const amarlon::ActorData& actor = _data->actor(i);
      if ( actor.actor_type() == id )
      {
        _selected = const_cast<amarlon::ActorData*>( &actor );
        break;
      }
    }

    accept();
  }
}
