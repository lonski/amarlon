#include "map_edit_panel.h"
#include <base64.h>
#include <aslot_menu_item.h>
#include "map_editor.h"

namespace amarlon { namespace map_editor {

MapEditPanel::MapEditPanel(int w, int h)
  : ::amarlon::gui::APanel(w,h)
  , _tileDb(nullptr)
  , _editor(nullptr)
  , _selectedTile ( TileType::Null )
{
  init();
}

void MapEditPanel::render(TCODConsole &console)
{
  initPanelConsole();
  renderFrame();
  renderWidgets();

  if (_map && _tileDb)
  {
    for(int y = 0; y < _map->height; ++y)
    {
      for(int x = 0; x < _map->width; ++x)
      {
        SerializedTile& tile = _tiles[y][x];

        _panelConsole->setChar( x, y, _tileDb->getChar( (TileType)tile.type ) );
        _panelConsole->setCharForeground( x, y, _tileDb->getColor( (TileType)tile.type ) );
      }
    }
  }

  TCODConsole::blit(_panelConsole.get(), 0, 0, _panelConsole->getWidth(), _panelConsole->getHeight(), &console, getX(), getY() );
}

void MapEditPanel::setMap(MapDescriptionPtr map)
{
  _map = map;

  if ( _map )
  {
    allocateTiles();

    std::string s_tiles = base64_decode( _map->binaryTiles );
    std::vector<unsigned char> tiles{s_tiles.begin(), s_tiles.end()};

    uint32 y(0), x(0);
    for (int pos = 0; pos + sizeof(SerializedTile) <= tiles.size(); pos += sizeof(SerializedTile) )
    {
      SerializedTile* serialized = reinterpret_cast<SerializedTile*>(&tiles[pos]);

      _tiles[y][x] =  *serialized;

      if ( x == _map->width - 1 )
      {
        x = 0;
        ++y;
      }
      else
      {
        ++x;
      }
    }
  }
}

void MapEditPanel::setTileDB(TileDB *db)
{
  _tileDb = db;
  init();
}

void MapEditPanel::setMapEditor(MapEditor *editor)
{
  _editor = editor;
}

gui::APanelPtr MapEditPanel::getSidebar() const
{
  return _sidebar;
}

void MapEditPanel::handleInput(TCOD_mouse_t mouse)
{
  if ( mouse.cx < 100 )
  {
    if ( mouse.lbutton )
    {
      tileLButtonHoldAction(mouse.cx, mouse.cy);
    }
    if ( mouse.lbutton_pressed ) {
      tileClickAction(mouse.cx, mouse.cy);
    }
    tileMoveAction(mouse.cx, mouse.cy);
  }
}

void MapEditPanel::init()
{
  int y = 2;

  setFrame(false);
  _sidebar.reset( new gui::APanel(30,60));
  _sidebar->setPosition(100,0);

  gui::ALabel* coordsTitle = new gui::ALabel;
  coordsTitle->setValue("== Coordinates: ==");
  coordsTitle->setPosition(2, y++);
  coordsTitle->setColor(TCODColor::copper);
  _sidebar->addWidget(coordsTitle);
  ++y;

  _xCoord.reset( new gui::ALabel );
  _xCoord->setValue("X: ");
  _xCoord->setPosition(2, y++);
  _xCoord->setColor(TCODColor::violet);
  _sidebar->addWidget(_xCoord);
  ++y;

  _yCoord.reset( new gui::ALabel );
  _yCoord->setValue("Y: ");
  _yCoord->setPosition(2, y++);
  _yCoord->setColor(TCODColor::violet);
  _sidebar->addWidget(_yCoord);
  ++y;

  if ( _tileDb )
  {
    gui::ALabel* tilesTitle = new gui::ALabel;
    tilesTitle->setValue("== Tiles: ==");
    tilesTitle->setPosition(2, y++);
    tilesTitle->setColor(TCODColor::copper);
    _sidebar->addWidget(tilesTitle);
    ++y;

    _selectedTileLabel.reset( new gui::ALabel );
    _selectedTileLabel->setValue( "Selected: [" + _tileDb->getName(_selectedTile) + "]" );
    _selectedTileLabel->setColor(TCODColor::cyan);
    _selectedTileLabel->setPosition(2, y++);
    _sidebar->addWidget(_selectedTileLabel);
    y++;

    for ( TileType id : TileType() )
    {
      if ( id != TileType::END && id != TileType::Null )
      {
        gui::ALabelMenuItem* tileBtn = new gui::ALabelMenuItem(
              _tileDb->getName(id), [=](){
                _selectedTile = id;
                _selectedTileLabel->setValue( "Selected: [" + _tileDb->getName(_selectedTile) + "]" );
              });
        tileBtn->setPosition(2, y++);
        _sidebar->addWidget(tileBtn);
      }
    }
  }

  ++y;
  gui::ALabel* operationsTitle = new gui::ALabel;
  operationsTitle->setValue("== Operations: ==");
  operationsTitle->setPosition(2, y++);
  operationsTitle->setColor(TCODColor::copper);
  _sidebar->addWidget(operationsTitle);

  ++y;
  gui::ASlotMenuItem* fillBtn = new gui::ASlotMenuItem(26,"","Fill whole map","");
  fillBtn->setCallback( [=](){
          fillWholeMap();
        });
  fillBtn->setPosition(2, y);
  y += fillBtn->getHeight();
  _sidebar->addWidget(fillBtn);

  gui::ASlotMenuItem* saveBtn = new gui::ASlotMenuItem(26,"","Save","");
  saveBtn->setPosition(2,y);
  saveBtn->setCallback([=](){
    save();
    _editor->storeMaps();
  });
  y += saveBtn->getHeight();
  _sidebar->addWidget(saveBtn);

  gui::ASlotMenuItem* menuBtn = new gui::ASlotMenuItem(26,"","Main menu","");
  menuBtn->setPosition(2,y);
  menuBtn->setCallback([=](){
    _editor->renderMainMenu();
    _editor->setIsMapOpened(true);
  });
  y += menuBtn->getHeight();
  _sidebar->addWidget(menuBtn);

  removeAllWidgets();
  addWidget(_sidebar);
}

void MapEditPanel::allocateTiles()
{
  _tiles.clear();
  for (int y = 0; y < _map->height; ++y)
  {
    TileRow row;
    for(int x = 0; x < _map->width; ++x)
    {
      row.push_back(SerializedTile());
    }
    _tiles.push_back(row);
  }
}

void MapEditPanel::tileClickAction(int x, int y)
{

}

void MapEditPanel::tileLButtonHoldAction(int x, int y)
{
  SerializedTile& tile = _tiles[y][x];
  tile.type = (int)_selectedTile;
}

void MapEditPanel::tileMoveAction(int x, int y)
{
  if ( _xCoord ) _xCoord->setValue( "X: " + std::to_string(x));
  if ( _yCoord ) _yCoord->setValue( "Y: " + std::to_string(y));
}

void MapEditPanel::save()
{
  if ( _map )
  {
    std::vector<unsigned char> v;

    for (auto t = _tiles.begin(); t != _tiles.end(); ++t)
    {
      TileRow& trow = *t;
      for (auto ct = trow.begin(); ct != trow.end(); ++ct)
      {
        SerializedTile& t = *ct;
        unsigned char* arr = reinterpret_cast<unsigned char*>(&t);
        std::vector<unsigned char> serialized{ arr, arr + sizeof(t) };
        v.insert( v.end(), serialized.begin(), serialized.end() );
      }
    }

    _map->binaryTiles = base64_encode(reinterpret_cast<const unsigned char*>(&v[0]), v.size());
  }
}

void MapEditPanel::fillWholeMap()
{
  for (int y = 0; y < _map->height; ++y)
  {
    for(int x = 0; x < _map->width; ++x)
    {
      _tiles[y][x].type = (int)_selectedTile;
    }
  }
}

}}
