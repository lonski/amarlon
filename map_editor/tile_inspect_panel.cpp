#include "tile_inspect_panel.h"
#include <alabel.h>
#include <alabel_menu_item.h>
#include "editor_utils.h"

namespace amarlon { namespace map_editor {

TileInspectPanel::TileInspectPanel()
  : APanel( 30, 60 )
{

}

void TileInspectPanel::handleInput(TCOD_mouse_t mouse, TCOD_key_t key)
{
  if ( _actorMenu->getProperty<bool>("panel_active") )
  {
    _actorMenu->handleInput(mouse, key);
  }
  else if ( _actorChoose->getProperty<bool>("panel_active") )
  {
    _actorChoose->handleInput(mouse, key);
  }
  else if ( _actorEdit->getProperty<bool>("panel_active") )
  {
    _actorEdit->handleInput(mouse, key );
  }
  else
  {
    processInput(mouse, key,
                 getWidgets(),
                 getX(),
                 getY());
    if ( _actorChoose->getSelected() )
    {
      addActor(_actorChoose->getSelected());
      _actorChoose->setSelected(nullptr);

      _actors.clear();
      for(ActorDescriptionPtr a : _map->actors )
        if ( *a->x == _x && *a->y == _y )
          _actors.push_back( a );

      init(_x,_y, _actors, _db, _parent, _map);
    }
    else if ( _actorUnderManage && _map )
    {
      if ( _actorMenu->choosen() == ActorMenuPanel::ARemove )
      {
          _actorMenu->setChoosen(ActorMenuPanel::ANoAction);
          for ( auto it = _map->actors.begin(); it != _map->actors.end(); ++it)
            if ( it->get() == _actorUnderManage.get() ) {
              _map->actors.erase(it);

              _actors.clear();
              for(ActorDescriptionPtr a : _map->actors )
                if ( *a->x == _x && *a->y == _y )
                  _actors.push_back( a );

              init(_x,_y, _actors, _db, _parent, _map);

              break;
            }
      }
      else if ( _actorMenu->choosen() == ActorMenuPanel::AEdit )
      {
        _actorMenu->setChoosen(ActorMenuPanel::ANoAction);
        _actorEdit->setProperty<bool>("panel_active", true);
        _actorEdit->setActor(_actorUnderManage);
        addWidget(_actorEdit);
        removeWidget(_actorMenu.get());
        _actorMenu->setProperty<bool>("panel_active", false);
        removeWidget(_actorChoose.get());
        _actorChoose->setProperty<bool>("panel_active", false);
      }
    }
  }
}

void TileInspectPanel::init(int x, int y, const std::vector<ActorDescriptionPtr> &actors,
                            ActorsDatabase *actorDb, gui::APanel *parent,
                            MapDescriptionPtr map)
{
  _x = x;
  _y = y;
  _actors = actors;
  _db = actorDb;
  _parent = parent;
  _map = map;
  _actorChoose.reset( new ActorChoosePanel(_db,this) );
  _actorChoose->setProperty<bool>("panel_active", false);
  _actorMenu.reset( new ActorMenuPanel(this) );
  _actorMenu->setProperty<bool>("panel_active", false);
  _actorEdit.reset( new ActorEditPanel(_db, this) );
  _actorEdit->setProperty<bool>("panel_active", false);

  removeAllWidgets();

  setPosition( 100, 0 );
  setFrame(true);

  int y_pos = 2;
  gui::ALabel* title = new gui::ALabel;
  title->setValue("== Tile inspect: ==");
  title->setPosition(2, y_pos++);
  title->setColor(TCODColor::copper);
  addWidget(title);

  ++y_pos;
  addWidget( new gui::ALabel("X: "+std::to_string(_x), 2, y_pos++) );
  addWidget( new gui::ALabel("Y: "+std::to_string(_y), 2, y_pos++) );

  ++y_pos;
  gui::ALabel* title2 = new gui::ALabel;
  title2->setValue("== Actors: ==");
  title2->setPosition(2, y_pos++);
  title2->setColor(TCODColor::copper);
  addWidget(title2);

  ++y_pos;
  for ( ActorDescriptionPtr a : _actors )
  {
    ActorDescriptionPtr def = _db->fetch(*a->id);
    addWidget( new gui::ALabelMenuItem(2, y_pos++,
                                       *def->name + " [ID"+std::to_string(*a->id)+"]", [this, a](){
      _actorMenu->setProperty<bool>("panel_active", true);
      _actorUnderManage = a;
      addWidget(_actorMenu);
    } ));
  }

  ++y_pos;
  gui::ALabel* title3 = new gui::ALabel;
  title3->setValue("== Operations: ==");
  title3->setPosition(2, y_pos++);
  title3->setColor(TCODColor::copper);
  addWidget(title3);

  y_pos+=2;
  addWidget( new gui::ALabelMenuItem(2, y_pos++,
                                     "Add actor", [=](){
    _actorChoose->setProperty<bool>("panel_active", true);
    addWidget(_actorChoose);
  } ));

  y_pos += 2;
  addWidget( new gui::ALabelMenuItem(2, y_pos++,
                                     "[CLOSE]", [=](){
    _parent->removeWidget(this);
  } ));
}

void TileInspectPanel::addActor(ActorDescriptionPtr a)
{
  if ( _map )
  {
    ActorDescriptionPtr dsc(new ActorDescription );
    dsc->id = *a->id;
    dsc->x = _x;
    dsc->y = _y;
    _map->actors.push_back(dsc);
  }
}

}}
