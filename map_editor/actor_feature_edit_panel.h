#ifndef ACTORFEATUREEDITPANEL_H
#define ACTORFEATUREEDITPANEL_H

#include <apanel.h>
#include <actor_descriptions.h>
#include "actors_database.h"

namespace amarlon { namespace map_editor {

class ActorFeatureEditPanel : public gui::APanel
{
public:
  ActorFeatureEditPanel(ActorsDatabase* db);
  virtual void handleInput(TCOD_mouse_t mouse, TCOD_key_t key);

  virtual ActorDescriptionPtr actor() const;
  virtual void setActor(const ActorDescriptionPtr &actor);

protected:
  ActorsDatabase* _db;
  ActorDescriptionPtr _actor;

  virtual void init();

};

}}

#endif // ACTORFEATUREEDITPANEL_H
