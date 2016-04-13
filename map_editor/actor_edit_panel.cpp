#include "actor_edit_panel.h"
#include "editor_utils.h"
#include <alabel_menu_item.h>
#include <alabel.h>

namespace amarlon { namespace map_editor {

ActorEditPanel::ActorEditPanel(ActorsDatabase *db, APanel *parent)
  : APanel( 30, 60 )
  , _parent(parent)
  , _db(db)
{
  init();
}

void ActorEditPanel::handleInput(TCOD_mouse_t mouse, TCOD_key_t key)
{
  processInput(mouse, key,
               getWidgets(),
               getX()+ _parent? _parent->getX():0,
               getY()+ _parent? _parent->getY():0);
}

ActorDescriptionPtr ActorEditPanel::actor() const
{
  return _actor;
}

void ActorEditPanel::setActor(const ActorDescriptionPtr &actor)
{
  _actor = actor;
  ActorDescriptionPtr proto = _db ? _db->fetch(*_actor->id) : nullptr;

  _fname->setText( actor->name ? *actor->name
                               : proto && proto->name ? *proto->name : "" );
  _finscription->setText( actor->inscription ? *actor->inscription
                                             : proto && proto->inscription ? *proto->inscription : "" );
  _fcolor->setText( actor->color ? *actor->color
                                 : proto && proto->color ? *proto->color : "" );
  _fpriority->setText( actor->tilePriority ? std::to_string(*actor->tilePriority)
                                 : proto && proto->tilePriority ? std::to_string(*proto->tilePriority) : "" );
}

void ActorEditPanel::init()
{
  removeAllWidgets();

  setPosition( 0, 0 );
  setFrame(true);

  int y_pos = 2;
  gui::ALabel* title = new gui::ALabel;
  title->setValue("== Edit actor ==");
  title->setPosition(2, y_pos++);
  title->setColor(TCODColor::copper);
  addWidget(title);

  if ( _parent )
  {
    ++y_pos;
    _fname.reset(new gui::ATextEdit(2, y_pos++, 25, "Name"));
    addWidget( _fname );
    ++y_pos;
    _finscription.reset(new gui::ATextEdit(2, y_pos++, 25, "Inscription"));
    addWidget( _finscription );
    ++y_pos;
    _fcolor.reset(new gui::ATextEdit(2, y_pos++, 25, "Color"));
    addWidget( _fcolor );
    ++y_pos;
    _fpriority.reset(new gui::ATextEdit(2, y_pos++, 25, "Priority"));
    addWidget( _fpriority );

    y_pos += 2;
    addWidget( new gui::ALabelMenuItem(2, y_pos++,
                                       "[SAVE]", [=](){
      saveActor();
      setActive(false);
    } ));
    ++y_pos;
    addWidget( new gui::ALabelMenuItem(2, y_pos++,
                                       "[CLOSE]", [=](){
      setActive(false);
    } ));
  }
}

void ActorEditPanel::saveActor()
{
  if ( _actor )
  {
    if ( ActorDescriptionPtr proto = _db ? _db->fetch(*_actor->id) : nullptr )
    {
      if ( !proto || !proto->name || _fname->getText() != *proto->name )
        if ( !_fname->getText().empty() ) _actor->name = _fname->getText();
      if ( !proto || !proto->inscription || _finscription->getText() != *proto->inscription )
        if ( !_finscription->getText().empty() ) _actor->inscription = _finscription->getText();
      if ( !proto || !proto->color || _fcolor->getText() != *proto->color )
        if ( !_fcolor->getText().empty() ) _actor->color = _fcolor->getText();
      if ( !proto || !proto->tilePriority || _fpriority->getInt() != *proto->tilePriority )
        if (_fpriority->getInt() != 0) _actor->tilePriority = _fpriority->getInt();
    }
  }
}

}}
