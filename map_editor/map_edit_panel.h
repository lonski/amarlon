#ifndef MAPEDITPANEL_H
#define MAPEDITPANEL_H

#include <widgets/apanel.h>
#include <map_description.h>
#include <serialized_tile.h>
#include <widgets/alabel.h>
#include "actors_database.h"
#include "tile_inspect_panel.h"
#include <tile_db.h>

namespace amarlon { namespace map_editor {

class MapEditor;

class MapEditPanel : public ::amarlon::gui::APanel
{
public:
  typedef std::vector<SerializedTile> TileRow;
  typedef std::vector< TileRow > TileMatrix;

  MapEditPanel(int w = 130, int h = 60);

  virtual void render(TCODConsole& console);

  void setMap(MapDescriptionPtr map);
  void setTileDB(TileDB* db);
  void setActorsDB(ActorsDatabase* db);
  void setMapEditor(MapEditor* editor);

  gui::APanelPtr getSidebar() const;
  void handleInput(TCOD_mouse_t mouse, TCOD_key_t key);

private:
  MapDescriptionPtr _map;
  gui::APanelPtr _sidebar;
  TileDB* _tileDb;
  MapEditor* _editor;
  TileMatrix _tiles;
  TileType _selectedTile;
  TileType _selectedTile_Right;
  gui::ALabelPtr _selectedTileLabel;
  gui::ALabelPtr _selectedTileFlagLabel;
  gui::ALabelPtr _selectedTileLabel_Right;
  gui::ALabelPtr _xCoord;
  gui::ALabelPtr _yCoord;
  bool _renderActors;
  ActorsDatabase* _actorsDb;
  std::shared_ptr<TileInspectPanel> _tileInspect;
  int _selectedFlagBit;

  void init();
  void allocateTiles();
  void tileClickAction(int x, int y);
  void tileRClickAction(int x, int y);
  void tileLButtonHoldAction(int x, int y);
  void tileRButtonHoldAction(int x, int y);
  void tileMoveAction(int x, int y);
  void save();
  void fillWholeMap();
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
};

}}

#endif // MAPEDITPANEL_H
