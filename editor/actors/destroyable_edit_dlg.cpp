#include "destroyable_edit_dlg.h"
#include "ui_destroyable_edit_dlg.h"
#include <actors/actors.pb.h>

DestroyableEditDlg::DestroyableEditDlg(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DestroyableEditDlg),
  _destroyable(nullptr)
{
  ui->setupUi(this);
}

DestroyableEditDlg::~DestroyableEditDlg()
{
  delete ui;
}

void DestroyableEditDlg::setDestroyable(amarlon::proto::ActorData_Destroyable *destroyable)
{
  _destroyable = destroyable;
  fillForm();
}

void DestroyableEditDlg::fillForm()
{
  if ( _destroyable )
  {
    ui->sTable->clear();
    ui->sTable->setRowCount(0);
    ui->sTable->setColumnCount(4);
    ui->sTable->setHorizontalHeaderItem(0,new QTableWidgetItem("Item ID"));
    ui->sTable->setHorizontalHeaderItem(1,new QTableWidgetItem("Amount Min"));
    ui->sTable->setHorizontalHeaderItem(1,new QTableWidgetItem("Amount Max"));
    ui->sTable->setHorizontalHeaderItem(1,new QTableWidgetItem("Chance"));

    for( int i=0; i < _destroyable->droprules_size(); ++i )
    {
      const auto& rule = _destroyable->droprules(i);

      ui->sTable->insertRow( ui->sTable->rowCount() );
      ui->sTable->setItem(ui->sTable->rowCount() - 1, 0, new QTableWidgetItem( QString::number(rule.itemid()) ));
      ui->sTable->setItem(ui->sTable->rowCount() - 1, 1, new QTableWidgetItem( QString::number(rule.min()) ));
      ui->sTable->setItem(ui->sTable->rowCount() - 1, 2, new QTableWidgetItem( QString::number(rule.max()) ));
      ui->sTable->setItem(ui->sTable->rowCount() - 1, 3, new QTableWidgetItem( QString::number(rule.chance(),'g',2) ));
    }
  }
}

void DestroyableEditDlg::on_btnAdd_clicked()
{
  if ( _destroyable )
  {
    _dropRulEdit.setRule( _destroyable->add_droprules() );
    _dropRulEdit.exec();
    fillForm();
  }
}

void DestroyableEditDlg::on_btnEdit_clicked()
{
  if ( _destroyable )
  {
    auto* item = ui->sTable->item( ui->sTable->currentRow(), 0);
    if ( item )
    {
      int id = item->text().toInt();
      for( int i=0; i < _destroyable->droprules_size(); ++i )
      {
        const auto& rule = _destroyable->droprules(i);
        if ( rule.itemid() == id )
        {
          _dropRulEdit.setRule( _destroyable->mutable_droprules(i) );
          _dropRulEdit.exec();
          fillForm();
        }
      }
    }
  }
}

void DestroyableEditDlg::on_btnDelete_clicked()
{
  if ( _destroyable )
  {
    auto* item = ui->sTable->item( ui->sTable->currentRow(), 0);
    if ( item )
    {
      int id = item->text().toInt();
      for( auto it = _destroyable->droprules().begin(); it != _destroyable->droprules().end(); ++it )
      {
        if ( it->itemid() == id )
        {
          _destroyable->mutable_droprules()->erase(it);
          fillForm();
          break;
        }
      }
    }
  }
}
