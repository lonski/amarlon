#ifndef ACTORCHOOSEPANEL_H
#define ACTORCHOOSEPANEL_H

#include <actor_descriptions.h>
#include <apanel.h>
#include "actors_database.h"

namespace amarlon { namespace map_editor {

class ActorChoosePanel : public gui::APanel
{
public:
  ActorChoosePanel(ActorsDatabase* db, gui::APanel* parent);
  ActorDescriptionPtr getSelected() const;
  void setSelected(ActorDescriptionPtr dsc);
  virtual void render(TCODConsole& console);
  void handleInput(TCOD_mouse_t mouse, TCOD_key_t key);
  void init();

private:
  ActorDescriptionPtr _selectedActor;
  ActorsDatabase* _db;
  gui::APanel* _parent;

};

}}

#endif // ACTORCHOOSEPANEL_H
