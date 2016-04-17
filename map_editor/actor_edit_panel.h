#ifndef ACTOREDITPANEL_H
#define ACTOREDITPANEL_H

#include <apanel.h>
#include <actor_descriptions.h>
#include <atext_edit.h>
#include "actors_database.h"
#include "actor_feature_edit_panel.h"
#include <actor_feature.h>

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
  gui::ATextEditPtr _fsymbol;
  gui::ATextEditPtr _fprototype;

  std::map<ActorFeature::Type, std::shared_ptr<ActorFeatureEditPanel> > _panels;

  void saveActor();

};

}}

#endif // ACTOREDITPANEL_H
