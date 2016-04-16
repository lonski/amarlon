#include "actor_feature_edit_panel.h"
#include "editor_utils.h"

namespace amarlon { namespace map_editor {

ActorFeatureEditPanel::ActorFeatureEditPanel(ActorsDatabase *db)
  : gui::APanel(30,60)
  , _db(db)
{
}

void ActorFeatureEditPanel::handleInput(TCOD_mouse_t mouse, TCOD_key_t key)
{
  processInput(mouse, key,
               getWidgets(),
               getX()+ getParent() && getParent()->getParent() ? getParent()->getParent()->getX() : 0,
               getY()+ getParent() && getParent()->getParent() ? getParent()->getParent()->getY() : 0);
}

ActorDescriptionPtr ActorFeatureEditPanel::actor() const
{
  return _actor;
}

void ActorFeatureEditPanel::setActor(const ActorDescriptionPtr &actor)
{
  _actor = actor;
  init();
}

void ActorFeatureEditPanel::init()
{

}

}}
