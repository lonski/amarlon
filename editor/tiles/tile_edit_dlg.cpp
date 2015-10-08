#include "tile_edit_dlg.h"
#include "ui_tileeditdlg.h"
#include <tiles.pb.h>

TileEditDlg::TileEditDlg(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::TileEditDlg)
{
  ui->setupUi(this);
}

TileEditDlg::~TileEditDlg()
{
  delete ui;
}

void TileEditDlg::setTile(amarlon::proto::TileData *tile)
{
  _tile = tile;
  fillForm();
}

void TileEditDlg::fillForm()
{
  if ( _tile )
  {
    ui->fID->setValue( _tile->id() );
    ui->fCharacter->setText( _tile->character().c_str() );
    ui->fColor->setText( _tile->color().c_str() );
    ui->fName->setText( _tile->name().c_str() );
    ui->fTransparent->setCurrentIndex( (bool)_tile->transparent() );
    ui->fWalkable->setCurrentIndex( (bool)_tile->walkable() );
  }
}

void TileEditDlg::fillTile()
{
  if ( _tile )
  {
    _tile->set_id( ui->fID->value() );
    _tile->set_character( ui->fCharacter->text().toStdString() );
    _tile->set_color( ui->fColor->text().toStdString() );
    _tile->set_name( ui->fName->text().toStdString() );
    _tile->set_transparent( (bool)ui->fTransparent->currentIndex() );
    _tile->set_walkable( (bool)ui->fWalkable->currentIndex() );
  }
}

void TileEditDlg::on_buttonBox_accepted()
{
    fillTile();
}
