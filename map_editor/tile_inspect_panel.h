#ifndef TILEINSPECTPANEL_H
#define TILEINSPECTPANEL_H

#include <vector>
#include <actor_descriptions.h>
#include <apanel.h>
#include "actors_database.h"

namespace amarlon { namespace map_editor {

class TileInspectPanel : public gui::APanel
{
public:
  TileInspectPanel();

  void init(int x, int y,
            const std::vector<ActorDescriptionPtr>&actors,
            ActorsDatabase* actorDb,
            gui::APanel* parent);


};

}}

#endif // TILEINSPECTPANEL_H
