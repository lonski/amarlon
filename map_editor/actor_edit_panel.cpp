#include "actor_edit_panel.h"
#include "editor_utils.h"
#include <alabel_menu_item.h>
#include <alabel.h>
#include "openable_edit_panel.h"
#include "pickable_edit_panel.h"

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
  bool panelActive = false;

  for ( auto& kv : _panels )
    if ( kv.second && kv.second->isActive() )
    {
      panelActive = true;
      kv.second->handleInput(mouse, key);
      break;
    }

  if ( !panelActive )
  {
    processInput(mouse, key,
                 getWidgets(),
                 getX()+ _parent? _parent->getX():0,
                 getY()+ _parent? _parent->getY():0);
  }
}

ActorDescriptionPtr ActorEditPanel::actor() const
{
  return _actor;
}

void ActorEditPanel::setActor(const ActorDescriptionPtr &actor)
{
  _actor = actor;
  init();
  ActorDescriptionPtr proto = _db ? _db->fetch( *_actor->id ) : nullptr;

  _fname->setText( actor->name ? *actor->name
                               : proto && proto->name ? *proto->name : "" );
  _finscription->setText( actor->inscription ? *actor->inscription
                                             : proto && proto->inscription ? *proto->inscription : "" );
  _fcolor->setText( actor->color ? *actor->color
                                 : proto && proto->color ? *proto->color : "" );
  _fpriority->setText( actor->tilePriority ? std::to_string(*actor->tilePriority)
                                 : proto && proto->tilePriority ? std::to_string(*proto->tilePriority) : "" );
  unsigned char c = (actor->symbol ? *actor->symbol
                                   : (proto && proto->symbol ? *proto->symbol : '#'));
  _fsymbol->setText( std::string(1, c) );

  _fprototype->setText( actor->prototype ? std::to_string(*actor->prototype)
                                 : proto && proto->prototype ? std::to_string(*proto->prototype) : "" );
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

  _panels[ ActorFeature::OPENABLE ] = std::shared_ptr<ActorFeatureEditPanel>
      (new OpenableEditPanel(_db));

  _panels[ ActorFeature::PICKABLE ] = std::shared_ptr<ActorFeatureEditPanel>
      (new PickableEditPanel(_db));

  if ( _parent )
  {
    ++y_pos;
    _fname.reset(new gui::ATextEdit(2, y_pos++, 25, "Name"));
    addWidget( _fname );
    ++y_pos;
    _fsymbol.reset(new gui::ATextEdit(2, y_pos++, 25, "Symbol"));
    addWidget( _fsymbol );
    ++y_pos;
    _finscription.reset(new gui::ATextEdit(2, y_pos++, 25, "Inscription"));
    addWidget( _finscription );
    ++y_pos;
    _fcolor.reset(new gui::ATextEdit(2, y_pos++, 25, "Color"));
    addWidget( _fcolor );
    ++y_pos;
    _fpriority.reset(new gui::ATextEdit(2, y_pos++, 25, "Priority"));
    addWidget( _fpriority );
    ++y_pos;
    _fprototype.reset(new gui::ATextEdit(2, y_pos++, 25, "Prototype"));
    addWidget( _fprototype );

    if ( _actor && _db )
    {
      ActorDescriptionPtr proto = _db->fetch(*_actor->id);
      for ( auto ft : ActorFeature::Type() )
      {
        auto f = _actor->features[(int)ft];
        if ( !f ) f = proto->features[(int)ft];

        if ( f )
        {
          ++y_pos;
          addWidget(new gui::ALabelMenuItem(2, y_pos++,
                                            ActorFeatureToStr[ ft ],
                    [this, ft](){
            auto it = _panels.find(ft);
            if ( it != _panels.end() )
            {
              addWidget(it->second);
              it->second->setActive(true);
              it->second->setActor(_actor);
            }
          }));
        }
      }
    }

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
      if ( !proto || !proto->symbol || _fsymbol->getText().front() != *proto->symbol )
        if ( !_fsymbol->getText().empty() ) _actor->symbol = _fsymbol->getText().front();
      if ( !proto || !proto->prototype || _fprototype->getInt() != *proto->prototype )
        if (_fprototype->getInt() != 0) _actor->prototype = _fprototype->getInt();
    }
  }
}

}}
