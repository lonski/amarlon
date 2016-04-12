#include "map_editor.h"
#include <widgets/aslot_menu_item.h>
#include <widgets/alabel_menu_item.h>
#include "editor_utils.h"

namespace amarlon { namespace map_editor {

MapEditor::MapEditor()
  : _screenHeight(0)
  , _screenWidth(0)
  , _panelWidth(30)
  , _quit(false)
  , _mapOpened(false)
  , _activePanel(Panel::MainMenu)
{

}

void MapEditor::handleInput(TCOD_mouse_t mouse, TCOD_key_t key)
{
  _lastInput = mouse;
  _lastInputKey = key;

  processInput(_lastInput, _lastInputKey,
               _panel->getWidgets(),
               _panel->getX(),
               _panel->getY());

  if ( _activePanel == Panel::MapEdit )
  {
    _mapEditPanel->handleInput(_lastInput, _lastInputKey);
  }
  else
  {
    processInput(_lastInput, _lastInputKey,
                 _mapChoosePanel->getWidgets(),
                 _mapChoosePanel->getX(),
                 _mapChoosePanel->getY());

    processInput(_lastInput, _lastInputKey,
                 _mainMenuPanel->getWidgets(),
                 _mainMenuPanel->getX(),
                 _mainMenuPanel->getY());
  }
}

void MapEditor::render()
{
  _panel->render(*TCODConsole::root);

  if ( _activePanel == Panel::MapEdit )
  {
    if ( _lastInput.cx < 100 )
    {
      highlightCell(_lastInput.cx, _lastInput.cy);
    }
  }


}

void MapEditor::init()
{
  config.load("config.cfg");

  TCODConsole::root->setCustomFont(config.getFont(),TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE);

  _screenWidth = std::stol( config.get("console_width") ) + _panelWidth;
  _screenHeight = std::stol( config.get("console_height") );

  TCODConsole::initRoot(_screenWidth,
                        _screenHeight,
                        "Amarlon Map Editor", false, TCOD_RENDERER_SDL);

  TCODConsole::root->setFullscreen( std::stol(config.get("fullscreen")) );
  TCODMouse::showCursor(true);

  _tileDB.load( config.get("tiles_file") );
  _actorsDB.load( config.get("actors_file") );

  _panel.reset( new gui::APanel(_screenWidth, _screenHeight) );
  _panel->setFrame(false);
  _panel->setPosition(0,0);

  configureStatusMessage();
  configureMainMenu();
  configureMapChoosePanel();
  configureMapEditPanel();

  renderMainMenu();
}

void MapEditor::configureMapEditPanel()
{
  _mapEditPanel.reset( new MapEditPanel );
  _mapEditPanel->setPosition(0, 0);
  _mapEditPanel->setMapEditor(this);
}

void MapEditor::configureStatusMessage()
{
  _statusMsg.reset( new gui::ALabel );
  _statusMsg->setPosition(2, 2);
  _statusMsg->setAutosize(false);
  _statusMsg->setWidth( 90 );
}

void MapEditor::configureMainMenu()
{
  _mainMenuPanel.reset( new gui::APanel(20,20) );
  _mainMenuPanel->setPosition(2,5);
  _mainMenuPanel->setFrame(false);

  int y = 0;

  gui::ASlotMenuItem* loadMapBtn = new gui::ASlotMenuItem(20,"","Load maps","");
  y += 0;
  loadMapBtn->setPosition( 0, y );
  loadMapBtn->setCallback([&](){
    if ( _db.load( config.get("maps_file") ) )
    {
      setStatusMessage("Success, loaded " + std::to_string(_db.getMapCount()) + " maps.");
      listMaps();
    }
    else
    {
      setStatusMessage("ERROR: Load map failed!");
    }
  });

  gui::ASlotMenuItem* quitBtn = new gui::ASlotMenuItem(20,"","Quit","");
  y += 5;
  quitBtn->setPosition( 0, y );
  quitBtn->setCallback([&](){
    _quit = true;
  });

  _mainMenuPanel->addWidget(loadMapBtn);
  _mainMenuPanel->addWidget(quitBtn);
}

void MapEditor::configureMapChoosePanel()
{
  _mapChoosePanel.reset( new gui::APanel(30, 50) );
  _mapChoosePanel->setPosition(26, 5);
  _mapChoosePanel->setFrame(false);
}

void MapEditor::listMaps()
{
  int x(1), y(2);

  _mapChoosePanel->removeAllWidgets();

  gui::ALabel* title = new gui::ALabel;
  title->setValue( "Choose map to edit:" );
  title->setPosition(x,y - 1);
  _mapChoosePanel->addWidget(title);

  for ( auto& kv : _db.getMaps() )
  {
    gui::ALabelMenuItem* i = new gui::ALabelMenuItem( kv.second->name, [=](){
      loadMap(kv.first);
    });
    i->setPosition(x, ++y);

    _mapChoosePanel->addWidget(i);
  }
}

void MapEditor::loadMap(int id)
{
  _mapEditPanel->setMap( _db.getMap(id) );
  _mapEditPanel->setTileDB(&_tileDB);
  _mapEditPanel->setActorsDB(&_actorsDB);
  renderMapEditPanel();
}

bool MapEditor::isQuitting()
{
  return _quit;
}

void MapEditor::storeMaps()
{
  _db.store( config.get("maps_file") );
}

int MapEditor::screenWidth() const
{
  return _screenWidth;
}

int MapEditor::screenHeight() const
{
  return _screenHeight;
}

void MapEditor::renderMainMenu()
{
  _panel->removeAllWidgets();

  _panel->addWidget(_statusMsg);
  _panel->addWidget(_mainMenuPanel);
  _panel->addWidget(_mapChoosePanel);

  if ( _mapOpened )
  {
    gui::ASlotMenuItem* backBtn = new gui::ASlotMenuItem(20,"","Back","");
    backBtn->setPosition( 108, 5 );
    backBtn->setCallback([&](){
      renderMapEditPanel();
    });
    _panel->addWidget(backBtn);
  }

  _activePanel = Panel::MainMenu;
}

void MapEditor::renderMapEditPanel()
{
  _panel->removeAllWidgets();
  _panel->addWidget(_statusMsg);
  _panel->addWidget(_mapEditPanel);
  setIsMapOpened(true);
  _activePanel = Panel::MapEdit;
}

void MapEditor::setIsMapOpened(bool isOpened)
{
  _mapOpened = isOpened;
}

void MapEditor::setStatusMessage(const std::string &msg)
{
  _statusMsg->setValue(msg);
}

void MapEditor::highlightCell(uint32_t x, uint32_t y)
{
  TCODColor fgcol = TCODConsole::root->getCharForeground(x, y);
  TCODColor bgcol = TCODConsole::root->getCharBackground(x, y);
  TCODConsole::root->setCharForeground(x, y, TCODColor::lerp(fgcol, TCODColor::yellow, 0.6));
  TCODConsole::root->setCharBackground(x, y, TCODColor::lerp(bgcol, TCODColor::yellow, 0.1));
}

}}
