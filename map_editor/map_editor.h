#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <libtcod.hpp>
#include <stdint.h>
#include <configuration.h>
#include <widgets/apanel.h>
#include <widgets/amenu_item.h>
#include <widgets/alabel.h>
#include <widgets/amenu.h>
#include <tile_db.h>
#include "maps_database.h"
#include "map_edit_panel.h"
#include "actors_database.h"

namespace amarlon { namespace map_editor {

class MapEditor
{
public:
  MapEditor();

  void handleInput(TCOD_mouse_t mouse);
  void render();
  void init();
  bool isQuitting();
  void storeMaps();

  int screenWidth() const;
  int screenHeight() const;

  void renderMainMenu();
  void renderMapEditPanel();

  void setIsMapOpened(bool isOpened);

private:
  enum class Panel {
    MainMenu,
    MapEdit
  };
  amarlon::Configuration config;
  int _screenHeight;
  int _screenWidth;
  int _panelWidth;
  TCOD_mouse_t _lastInput;
  bool _quit;
  MapsDatabase _db;
  TileDB _tileDB;
  gui::ALabelPtr _statusMsg;
  bool _mapOpened;
  Panel _activePanel;
  ActorsDatabase _actorsDB;

  gui::APanelPtr _panel;
  gui::APanelPtr _mainMenuPanel;
  gui::APanelPtr _mapChoosePanel;
  std::shared_ptr<MapEditPanel> _mapEditPanel;

  void setStatusMessage(const std::string& msg);
  void configureMapEditPanel();
  void configureStatusMessage();
  void configureMainMenu();
  void configureMapChoosePanel();
  void loadMaps();
  void listMaps();
  void loadMap(int id);
  void highlightCell(uint32_t x, uint32_t y);

};

}}

#endif // MAPEDITOR_H
