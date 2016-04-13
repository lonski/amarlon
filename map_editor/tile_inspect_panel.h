#ifndef TILEINSPECTPANEL_H
#define TILEINSPECTPANEL_H

#include <vector>
#include <actor_descriptions.h>
#include <apanel.h>
#include "actors_database.h"
#include "actor_choose_panel.h"
#include <map_description.h>
#include "actor_menu.h"
#include "actor_edit_panel.h"

namespace amarlon { namespace map_editor {

class TileInspectPanel : public gui::APanel
{
public:
  enum EPanel {
    EPanel_None,
    EPanel_ActorChoose,
    EPanel_ActorMenu,
    EPanel_ActorEdit
  };

  TileInspectPanel();
  void handleInput(TCOD_mouse_t mouse, TCOD_key_t key);
  virtual void render(TCODConsole& console);

  void init(int x, int y,
            const std::vector<ActorDescriptionPtr>&actors,
            ActorsDatabase* actorDb,
            gui::APanel* parent,
            MapDescriptionPtr map);

private:
  std::map<EPanel, gui::APanelPtr> _panels;

  std::shared_ptr<ActorChoosePanel> _actorChoose;
  std::shared_ptr<ActorMenuPanel> _actorMenu;
  std::shared_ptr<ActorEditPanel> _actorEdit;

  int _x;
  int _y;
  std::vector<ActorDescriptionPtr> _actors;
  ActorsDatabase* _db;
  gui::APanel* _parent;
  MapDescriptionPtr _map;
  ActorDescriptionPtr _actorUnderManage;

  void addActor(ActorDescriptionPtr a);


};

}}

#endif // TILEINSPECTPANEL_H
