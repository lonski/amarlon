#ifndef ACTOREDITPANEL_H
#define ACTOREDITPANEL_H

#include <apanel.h>
#include <actor_descriptions.h>
#include <atext_edit.h>
#include "actors_database.h"

namespace amarlon { namespace map_editor {

class ActorEditPanel : public gui::APanel
{
public:
  ActorEditPanel(ActorsDatabase* db, APanel* parent);
  void handleInput(TCOD_mouse_t mouse, TCOD_key_t key);

  ActorDescriptionPtr actor() const;
  void setActor(const ActorDescriptionPtr &actor);
  void init();

private:
  ActorDescriptionPtr _actor;
  APanel* _parent;
  ActorsDatabase* _db;

  gui::ATextEditPtr _fname;
  gui::ATextEditPtr _finscription;
  gui::ATextEditPtr _fcolor;
  gui::ATextEditPtr _fpriority;

  void saveActor();

};

}}

#endif // ACTOREDITPANEL_H
