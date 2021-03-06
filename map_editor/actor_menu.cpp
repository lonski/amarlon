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

void ActorMenuPanel::handleInput(TCOD_mouse_t mouse, TCOD_key_t key)
{
  processInput(mouse, key,
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
    setActive(false);
  } ));

  ++y_pos;
  addWidget( new gui::ALabelMenuItem(2, y_pos++,
                                     "Edit",
                                     [this](){
    _choosen = AEdit;
    setActive(false);
  } ));

  y_pos += 2;
  addWidget( new gui::ALabelMenuItem(2, y_pos++,
                                     "[CLOSE]", [=](){
    _choosen = ANoAction;
    setActive(false);
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
