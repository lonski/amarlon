#include "actor_choose_panel.h"
#include <alabel.h>
#include <alabel_menu_item.h>
#include "editor_utils.h"

namespace amarlon { namespace map_editor {

ActorChoosePanel::ActorChoosePanel(ActorsDatabase *db, APanel *parent)
  : APanel( 30, 60 )
  , _db(db)
  , _parent(parent)
{
  setPosition( 0, 0 );
  init();
}

ActorDescriptionPtr ActorChoosePanel::getSelected() const
{
  return _selectedActor;
}

void ActorChoosePanel::setSelected(ActorDescriptionPtr dsc)
{
  _selectedActor = dsc;
}

void ActorChoosePanel::render(TCODConsole &console)
{
  APanel::render(console);
}

void ActorChoosePanel::handleInput(TCOD_mouse_t mouse)
{
  processInput(mouse,
               getWidgets(),
               getX()+ _parent? _parent->getX():0,
               getY()+ _parent? _parent->getY():0);
}

void ActorChoosePanel::init()
{
  removeAllWidgets();

  setPosition( 0, 0 );
  setFrame(true);

  int y_pos = 2;
  gui::ALabel* title = new gui::ALabel;
  title->setValue("== Choose actor: ==");
  title->setPosition(2, y_pos++);
  title->setColor(TCODColor::copper);
  addWidget(title);

  if ( _db && _parent )
  {
    ++y_pos;
    for ( auto& kv : _db->getActors() )
    {
      ActorDescriptionPtr def = kv.second;
      addWidget( new gui::ALabelMenuItem(2, y_pos++,
                                         "["+std::to_string(*def->id)+"] "
                                         + *def->name,
                                         [def, this](){
        _selectedActor = def;
        _parent->removeWidget(this);
        setProperty<bool>("panel_active", false);
      } ));
    }

    y_pos += 2;
    addWidget( new gui::ALabelMenuItem(2, y_pos++,
                                       "[CLOSE]", [=](){
      _selectedActor = nullptr;
      setProperty<bool>("panel_active", false);
      _parent->removeWidget(this);
    } ));
  }
}

}}
