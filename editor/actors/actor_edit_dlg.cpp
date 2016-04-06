#include "actor_edit_dlg.h"
#include "ui_actor_edit_dlg.h"
#include <QDesktopWidget>
#include <QMenu>
#include <QDebug>
#include <QMessageBox>
#include <actor.pb.h>
#include <enum_mappings.h>

ActorEditDlg::ActorEditDlg(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::ActorEditDlg)
  , _actor(nullptr)
  , _pickableEdit(this)
  , _openableEdit(this)
  , _aiEdit(this)
  , _wearerEdit(this)
  , _destroyableEdit(this)
  , _inventoryEdit(this)
  , _characterEdit(this)
{
  ui->setupUi(this);
  move(QApplication::desktop()->screen()->rect().center() - rect().center());

  QMenu* feature_menu = new QMenu;

  QAction* pickable = new QAction("Pickable", this);
  connect(pickable, SIGNAL(triggered()), this, SLOT(new_pickable()));
  feature_menu->addAction(pickable);

  QAction* inventory = new QAction("Inventory", this);
  connect(inventory, SIGNAL(triggered()), this, SLOT(new_inventory()));
  feature_menu->addAction(inventory);

  QAction* character = new QAction("Character", this);
  connect(character, SIGNAL(triggered()), this, SLOT(new_character()));
  feature_menu->addAction(character);

  QAction* destroyable = new QAction("Destroyable", this);
  connect(destroyable, SIGNAL(triggered()), this, SLOT(new_destroyable()));
  feature_menu->addAction(destroyable);

  QAction* wearer = new QAction("Wearer", this);
  connect(wearer, SIGNAL(triggered()), this, SLOT(new_wearer()));
  feature_menu->addAction(wearer);

  QAction* ai = new QAction("Ai", this);
  connect(ai, SIGNAL(triggered()), this, SLOT(new_ai()));
  feature_menu->addAction(ai);

  QAction* openable = new QAction("Openable", this);
  connect(openable, SIGNAL(triggered()), this, SLOT(new_openable()));
  feature_menu->addAction(openable);

  ui->btnAddFeature->setMenu(feature_menu);
  ui->fID->addItems(actors);
}

ActorEditDlg::~ActorEditDlg()
{
  delete ui;
}

void ActorEditDlg::setActor(amarlon::ActorData *actor)
{
  _actor = actor;
  fillForm();
}

void ActorEditDlg::new_pickable()
{
  if ( ui->lFeatures->findItems("Pickable", Qt::MatchExactly).isEmpty() )
  {
    ui->lFeatures->addItem("Pickable");

    _actor->set_allocated_pickable( new amarlon::PickableData );
    _pickableEdit.setPickable( _actor->mutable_pickable()  );
    _pickableEdit.exec();
  }
  else
  {
    QMessageBox::critical(this, "Error","Actor already has Pickable feature.");
  }
}

void ActorEditDlg::new_inventory()
{
  if ( ui->lFeatures->findItems("Inventory", Qt::MatchExactly).isEmpty() )
  {
    ui->lFeatures->addItem("Inventory");

    _actor->set_allocated_inventory( new amarlon::InventoryData );
    _inventoryEdit.setInventory( _actor->mutable_inventory() );
    _inventoryEdit.exec();
  }
  else
  {
    QMessageBox::critical(this, "Error","Actor already has Inventory feature.");
  }
}

void ActorEditDlg::new_character()
{
  if ( ui->lFeatures->findItems("Character", Qt::MatchExactly).isEmpty() )
  {
    ui->lFeatures->addItem("Character");

    _actor->set_allocated_character( new amarlon::CharacterData );
    _characterEdit.setCharacter( _actor->mutable_character() );
    _characterEdit.exec();
  }
  else
  {
    QMessageBox::critical(this, "Error","Actor already has Character feature.");
  }
}

void ActorEditDlg::new_destroyable()
{
  if ( ui->lFeatures->findItems("Destroyable", Qt::MatchExactly).isEmpty() )
  {
    ui->lFeatures->addItem("Destroyable");

    _actor->set_allocated_destroyable( new amarlon::DestroyableData );
    _destroyableEdit.setDestroyable( _actor->mutable_destroyable() );
    _destroyableEdit.exec();
  }
  else
  {
    QMessageBox::critical(this, "Error","Actor already has Destroyable feature.");
  }
}

void ActorEditDlg::new_wearer()
{
  if ( ui->lFeatures->findItems("Wearer", Qt::MatchExactly).isEmpty() )
  {
    ui->lFeatures->addItem("Wearer");

    _actor->set_allocated_wearer( new amarlon::WearerData );
    _wearerEdit.setWearer( _actor->mutable_wearer() );
    _wearerEdit.exec();
  }
  else
  {
    QMessageBox::critical(this, "Error","Actor already has Wearer feature.");
  }
}

void ActorEditDlg::new_ai()
{
  if ( ui->lFeatures->findItems("Ai", Qt::MatchExactly).isEmpty() )
  {
    ui->lFeatures->addItem("Ai");

    _actor->set_allocated_ai( new amarlon::AiData );
    _aiEdit.setAi( _actor->mutable_ai() );
    _aiEdit.exec();
  }
  else
  {
    QMessageBox::critical(this, "Error","Actor already has Openable feature.");
  }
}

void ActorEditDlg::new_openable()
{
  if ( ui->lFeatures->findItems("Openable", Qt::MatchExactly).isEmpty() )
  {
    ui->lFeatures->addItem("Openable");

    _actor->set_allocated_openable( new amarlon::OpenableData );
    _openableEdit.setOpenable( _actor->mutable_openable() );
    _openableEdit.exec();
  }
  else
  {
    QMessageBox::critical(this, "Error","Actor already has Openable feature.");
  }
}

void ActorEditDlg::fillForm()
{
  if (_actor)
  {
    ui->fBlocks->setCurrentIndex( (int)_actor->is_blocking() );
    ui->fColor->setText( _actor->color().c_str() );
    ui->fDescription->setText( _actor->description().c_str() );
    ui->fFOV->setCurrentIndex( (int)_actor->is_fov_only() );
    ui->fTransparent->setCurrentIndex( (int)_actor->is_transparent() );
    ui->fID->setCurrentIndex( _actor->actor_type() );
    ui->fName->setText( _actor->name().c_str() );
    ui->fSymbol->setText( _actor->symbol().c_str() );
    ui->fPriority->setValue( _actor->render_priority() );

    ui->lFeatures->clear();
    if ( _actor->has_inventory() ) ui->lFeatures->addItem("Inventory");
    if ( _actor->has_character() ) ui->lFeatures->addItem("Character");
    if ( _actor->has_destroyable() ) ui->lFeatures->addItem("Destroyable");
    if ( _actor->has_wearer() ) ui->lFeatures->addItem("Wearer");
    if ( _actor->has_ai() ) ui->lFeatures->addItem("Ai");
    if ( _actor->has_openable() ) ui->lFeatures->addItem("Openable");
    if ( _actor->has_pickable() ) ui->lFeatures->addItem("Pickable");
  }
}

void ActorEditDlg::fillActor()
{
  if (_actor)
  {
    _actor->set_is_blocking( (bool)ui->fBlocks->currentIndex() );
    _actor->set_color( ui->fColor->text().toStdString() );
    _actor->set_description( ui->fDescription->toPlainText().toStdString() );
    _actor->set_is_fov_only( (bool)ui->fFOV->currentIndex() );
    _actor->set_is_transparent( (bool)ui->fTransparent->currentIndex() );
    _actor->set_actor_type( ui->fID->currentIndex() );
    _actor->set_name( ui->fName->text().toStdString() );
    _actor->set_symbol( ui->fSymbol->text().toStdString() );
    _actor->set_render_priority( ui->fPriority->value() );
  }
}

void ActorEditDlg::on_pushButton_2_clicked()
{
  auto items = ui->lFeatures->selectedItems();
  if ( !items.isEmpty() && _actor )
  {
    QString feat = items.first()->text();
    if ( feat == "Inventory" ) _actor->clear_inventory();
    else if ( feat == "Character" ) _actor->clear_character();
    else if ( feat == "Destroyable" ) _actor->clear_destroyable();
    else if ( feat == "Wearer" ) _actor->clear_wearer();
    else if ( feat == "Ai" ) _actor->clear_ai();
    else if ( feat == "Openable" ) _actor->clear_openable();
    else if ( feat == "Pickable" ) _actor->clear_pickable();

    delete items.first();
  }
}

void ActorEditDlg::on_pushButton_clicked()
{
  auto items = ui->lFeatures->selectedItems();
  if ( !items.isEmpty() && _actor )
  {
    QString feat = items.first()->text();

    if ( feat == "Pickable" )
    {
      _pickableEdit.setPickable( _actor->mutable_pickable() );
      _pickableEdit.exec();
    }
    else if ( feat == "Openable" )
    {
      _openableEdit.setOpenable( _actor->mutable_openable() );
      _openableEdit.exec();
    }
    else if ( feat == "Ai" )
    {
      _aiEdit.setAi( _actor->mutable_ai() );
      _aiEdit.exec();
    }
    else if ( feat == "Wearer" )
    {
      _wearerEdit.setWearer( _actor->mutable_wearer() );
      _wearerEdit.exec();
    }
    else if ( feat == "Destroyable" )
    {
      _destroyableEdit.setDestroyable( _actor->mutable_destroyable() );
      _destroyableEdit.exec();
    }
    else if ( feat == "Inventory" )
    {
      _inventoryEdit.setInventory( _actor->mutable_inventory() );
      _inventoryEdit.exec();
    }
    else if ( feat == "Character" )
    {
      _characterEdit.setCharacter( _actor->mutable_character() );
      _characterEdit.exec();
    }
  }
}

void ActorEditDlg::on_lFeatures_itemDoubleClicked(QListWidgetItem *item)
{
    on_pushButton_clicked();
}

void ActorEditDlg::on_pushButton_4_clicked()
{
    fillActor();
    accept();
}


void ActorEditDlg::on_cancelBtn_clicked()
{
    reject();
}
