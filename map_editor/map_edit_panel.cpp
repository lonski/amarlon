#include "map_edit_panel.h"
#include <base64.h>
#include <aslot_menu_item.h>
#include "map_editor.h"
#include <actor_descriptions.h>
#include "editor_utils.h"

namespace amarlon { namespace map_editor {

MapEditPanel::MapEditPanel(int w, int h)
  : ::amarlon::gui::APanel(w,h)
  , _tileDb(nullptr)
  , _editor(nullptr)
  , _selectedTile ( TileType::Null )
  , _selectedTile_Right ( TileType::Null )
  , _renderActors(true)
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
    //render tiles
    for(int y = 0; y < _map->height; ++y)
    {
      for(int x = 0; x < _map->width; ++x)
      {
        SerializedTile& tile = _tiles[y][x];

        _panelConsole->setChar( x, y, _tileDb->getChar( (TileType)tile.type ) );
        _panelConsole->setCharForeground( x, y, _tileDb->getColor( (TileType)tile.type ) );
      }
    }

    //render actors
    if ( _renderActors )
    {
      for ( ActorDescriptionPtr a : _map->actors )
      {
        if ( a->x && a->y && a->symbol )
        {
          _panelConsole->setChar( *a->x, *a->y, *a->symbol );
          if ( a->color )
            _panelConsole->setCharForeground( *a->x, *a->y, strToColor(*a->color) );
        }
        else if ( _actorsDb && a->x && a->y && a->id)
        {
          ActorDescriptionPtr dsc = _actorsDb->fetch(*a->id);
          if ( dsc && dsc->symbol )
          {
            _panelConsole->setChar( *a->x, *a->y, *dsc->symbol );
            if ( dsc->color )
              _panelConsole->setCharForeground( *a->x, *a->y, strToColor(*dsc->color) );
          }
        }
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

void MapEditPanel::setActorsDB(ActorsDatabase *db)
{
  _actorsDb = db;
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
  bool anotherPanelOnTop = false;

  for ( auto w : getWidgets() )
  {
    TileInspectPanel* inspect = dynamic_cast<TileInspectPanel*>(w.get());
    if ( inspect )
    {
      processInput(mouse,
                   inspect->getWidgets(),
                   inspect->getX(),
                   inspect->getY());
      anotherPanelOnTop = true;
      break;
    }
  }

  if ( !anotherPanelOnTop )
  {
    processInput(mouse,
                 getSidebar()->getWidgets(),
                 getSidebar()->getX(),
                 getSidebar()->getY());
  }

  if ( mouse.cx < 100 )
  {
    if ( mouse.lbutton )
    {
      tileLButtonHoldAction(mouse.cx, mouse.cy);
    }
    if ( mouse.rbutton )
    {
      tileRButtonHoldAction(mouse.cx, mouse.cy);
    }
    if ( mouse.rbutton_pressed )
    {
      tileRClickAction(mouse.cx, mouse.cy);
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

  _tileInspect.reset( new TileInspectPanel );

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
    _selectedTileLabel->setValue( "Selected L: [" + _tileDb->getName(_selectedTile) + "]" );
    _selectedTileLabel->setColor(TCODColor::cyan);
    _selectedTileLabel->setPosition(2, y++);
    _sidebar->addWidget(_selectedTileLabel);

    _selectedTileLabel_Right.reset( new gui::ALabel );
    _selectedTileLabel_Right->setValue( "Selected R: [" + _tileDb->getName(_selectedTile_Right) + "]" );
    _selectedTileLabel_Right->setColor(TCODColor::cyan);
    _selectedTileLabel_Right->setPosition(2, y++);
    _sidebar->addWidget(_selectedTileLabel_Right);
    y++;

    for ( TileType id : TileType() )
    {
        gui::ALabelMenuItem* tileBtn = new gui::ALabelMenuItem(
              _tileDb->getName(id), [=](){
                _selectedTile = id;
                _selectedTileLabel->setValue( "Selected L: [" + _tileDb->getName(_selectedTile) + "]" );
              });
        tileBtn->setCallback2([=](){
          _selectedTile_Right = id;
          _selectedTileLabel_Right->setValue( "Selected R: [" + _tileDb->getName(_selectedTile_Right) + "]" );
        });
        tileBtn->setPosition(2, y++);
        _sidebar->addWidget(tileBtn);
    }
  }

  ++y;
  gui::ALabel* operationsTitle = new gui::ALabel;
  operationsTitle->setValue("== Operations: ==");
  operationsTitle->setPosition(2, y++);
  operationsTitle->setColor(TCODColor::copper);
  _sidebar->addWidget(operationsTitle);

  ++y;
  gui::ALabelMenuItem* fillBtn = new gui::ALabelMenuItem("Fill whole map");
  fillBtn->setCallback( [=](){
          fillWholeMap();
        });
  fillBtn->setPosition(2, y);
  y += fillBtn->getHeight();
  _sidebar->addWidget(fillBtn);

  ++y;
  gui::ALabelMenuItem* moveUpBtn = new gui::ALabelMenuItem("Move up");
  moveUpBtn->setCallback( [=](){
          moveUp();
        });
  moveUpBtn->setPosition(2, y);
  y += moveUpBtn->getHeight();
  _sidebar->addWidget(moveUpBtn);

  gui::ALabelMenuItem* moveDownBtn = new gui::ALabelMenuItem("Move down");
  moveDownBtn->setCallback( [=](){
          moveDown();
        });
  moveDownBtn->setPosition(2, y);
  y += moveDownBtn->getHeight();
  _sidebar->addWidget(moveDownBtn);

  gui::ALabelMenuItem* moveleftBtn = new gui::ALabelMenuItem("Move left");
  moveleftBtn->setCallback( [=](){
          moveLeft();
        });
  moveleftBtn->setPosition(2, y);
  y += moveleftBtn->getHeight();
  _sidebar->addWidget(moveleftBtn);

  gui::ALabelMenuItem* moveRightBtn = new gui::ALabelMenuItem("Move right");
  moveRightBtn->setCallback( [=](){
          moveRight();
        });
  moveRightBtn->setPosition(2, y);
  y += moveRightBtn->getHeight();
  _sidebar->addWidget(moveRightBtn);

  ++y;
  gui::ALabelMenuItem* showActorsBtn = new gui::ALabelMenuItem("Show actors");
  showActorsBtn->setCallback( [&](){
          _renderActors = true;
        });
  showActorsBtn->setPosition(2, y);
  y += showActorsBtn->getHeight();
  _sidebar->addWidget(showActorsBtn);

  gui::ALabelMenuItem* hideActorsBtn = new gui::ALabelMenuItem("Hide actors");
  hideActorsBtn->setCallback( [&](){
          _renderActors = false;
        });
  hideActorsBtn->setPosition(2, y);
  y += hideActorsBtn->getHeight();
  _sidebar->addWidget(hideActorsBtn);

  ++y;
  gui::ALabelMenuItem* saveBtn = new gui::ALabelMenuItem("[SAVE TO FILE]");
  saveBtn->setPosition(2,y);
  saveBtn->setCallback([=](){
    save();
    _editor->storeMaps();
  });
  y += saveBtn->getHeight();
  _sidebar->addWidget(saveBtn);

  gui::ALabelMenuItem* menuBtn = new gui::ALabelMenuItem("[MAIN MENU]");
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
  if ( _selectedTile == TileType::Null && _map && _actorsDb)
  {
    std::vector<ActorDescriptionPtr> actorsOnTile;
    for(ActorDescriptionPtr a : _map->actors )
      if ( *a->x == x && *a->y == y )
        actorsOnTile.push_back( a );

    _tileInspect->init(x,y,actorsOnTile,_actorsDb, this);
    addWidget(_tileInspect);
  }
}

void MapEditPanel::tileRClickAction(int x, int y)
{

}

void MapEditPanel::tileLButtonHoldAction(int x, int y)
{
  if ( _selectedTile != TileType::Null )
  {
    SerializedTile& tile = _tiles[y][x];
    tile.type = (int)_selectedTile;
  }
}

void MapEditPanel::tileRButtonHoldAction(int x, int y)
{
  if ( _selectedTile_Right != TileType::Null )
  {
    SerializedTile& tile = _tiles[y][x];
    tile.type = (int)_selectedTile_Right;
  }
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

void MapEditPanel::moveUp()
{
  for (int y = 0; y < _map->height; ++y)
  {
    for(int x = 0; x < _map->width; ++x)
    {
      if ( y+1 < _map->height )
        _tiles[y][x].type = _tiles[y+1][x].type;
      else
        _tiles[y][x].type = (int)_selectedTile_Right;
    }
  }

  for ( ActorDescriptionPtr a : _map->actors )
    *a->y = *a->y - 1;
}

void MapEditPanel::moveDown()
{
  for (int y = _map->height - 1; y >=0 ; --y)
  {
    for(int x = 0; x < _map->width; ++x)
    {
      if ( y-1 >= 0 )
        _tiles[y][x].type = _tiles[y-1][x].type;
      else
        _tiles[y][x].type = (int)_selectedTile_Right;
    }
  }

  for ( ActorDescriptionPtr a : _map->actors )
    *a->y = *a->y + 1;
}

void MapEditPanel::moveLeft()
{
  for (int y = 0; y < _map->height; ++y)
  {
    for(int x = 0; x < _map->width; ++x)
    {
      if ( x+1 < _map->width )
        _tiles[y][x].type = _tiles[y][x+1].type;
      else
        _tiles[y][x].type = (int)_selectedTile_Right;
    }
  }

  for ( ActorDescriptionPtr a : _map->actors )
    *a->x = *a->x - 1;
}

void MapEditPanel::moveRight()
{
  for (int y = 0; y < _map->height; ++y)
  {
    for(int x = _map->width - 1; x >=0 ; --x)
    {
      if ( x-1 >= 0 )
        _tiles[y][x].type = _tiles[y][x-1].type;
      else
        _tiles[y][x].type = (int)_selectedTile_Right;
    }
  }

  for ( ActorDescriptionPtr a : _map->actors )
    *a->x = *a->x + 1;
}

}}
