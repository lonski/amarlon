#include "actor_menu.h"
#include <alabel.h>
#include <alabel_menu_item.h>
#include "editor_utils.h"

namespace amarlon { namespace map_editor {

ActorMenuPanel::ActorMenuPanel(APanel *parent)
  : APanel( 30, 60 )
  , _parent(parent)
{
  setPosition(0,0);
  init();
}

void ActorMenuPanel::handleInput(TCOD_mouse_t mouse)
{
  processInput(mouse,
               getWidgets(),
               getX()+ _parent? _parent->getX():0,
               getY()+ _parent? _parent->getY():0);
}

void ActorMenuPanel::init()
{
  _choosen = ANoAction;
  removeAllWidgets();

  setPosition( 0, 0 );
  setFrame(true);

  int y_pos = 2;
  gui::ALabel* title = new gui::ALabel;
  title->setValue("== Manage actor ==");
  title->setPosition(2, y_pos++);
  title->setColor(TCODColor::copper);
  addWidget(title);

  ++y_pos;
  addWidget( new gui::ALabelMenuItem(2, y_pos++,
                                     "Remove",
                                     [this](){
    _choosen = ARemove;
    if ( _parent) _parent->removeWidget(this);
    setProperty<bool>("panel_active", false);
  } ));

  y_pos += 2;
  addWidget( new gui::ALabelMenuItem(2, y_pos++,
                                     "[CLOSE]", [=](){
    _choosen = ANoAction;
    setProperty<bool>("panel_active", false);
    if (_parent) _parent->removeWidget(this);
  } ));
}

ActorMenuPanel::Action ActorMenuPanel::choosen() const
{
  return _choosen;
}

void ActorMenuPanel::setChoosen(const Action &choosen)
{
  _choosen = choosen;
}

}}
