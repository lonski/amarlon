#include "map.h"
#include <algorithm>
#include <actor.h>
#include <amarlon_except.h>
#include <actor_action.h>
#include <utils.h>
#include <libtcod.hpp>
#include <tile.h>

namespace amarlon {

using namespace std;

Map::Map(u32 width, u32 height, MapId id)
  : _id(id)
  , _width(width)
  , _height(height)
  , _codMap(width, height)
{
  for (u32 y = 0; y < height; ++y)
  {
    TileRow row;
    for(u32 x = 0; x < width; ++x)
    {
      row.push_back(Tile(x, y));
    }
    _tiles.push_back(row);
  }
}

Map::~Map()
{
}

bool Map::isExplored(int x, int y)
{
  return getTile(x,y).isExplored();
}

bool Map::isInFov(int x, int y)
{
  bool inFov = _codMap.isInFov(x,y);

  if (inFov) getTile(x,y).setExplored(true);

  return inFov;
}

bool Map::isBlocked(int x, int y)
{
  return !_codMap.isWalkable(x,y);
}

void Map::addActor(ActorPtr actor)
{
  u32 x( actor->getX() );
  u32 y( actor->getY() );
  Tile& tile = getTile(x, y);

  if ( !tile.actors->add(actor) ) throw amarlon_exeption("Failed to add actor to tile!");
  actor->setMap( shared_from_this() );
}

ActorPtr Map::getFirstActor(int x, int y)
{
  Tile& tile = getTile(x, y);
  return tile.actors->size() > 0 ? tile.actors->content().front() : nullptr;
}

std::vector<ActorPtr > Map::getActors(int x, int y, std::function<bool (amarlon::ActorPtr)>* filterFun)
{
  std::vector<ActorPtr> r;
  Tile& tile = getTile(x, y);

  for ( auto a : tile.actors->content() )
  {
    if ( filterFun == nullptr || (*filterFun)(a))
    {
      r.push_back(a);
    }
  }

  return r;
}

std::vector<ActorPtr > Map::getActors(std::function<bool(ActorPtr)>* filterFun)
{
  std::vector<ActorPtr> r;

  for(auto& tileRow : _tiles)
  {
    for(auto& tile : tileRow)
    {
      for (auto a : tile.actors->content() )
      {
        if ( filterFun == nullptr || (*filterFun)(a))
        {
          r.push_back(a);
        }
      }
    }
  }

  return r;
}

bool Map::removeActor(ActorPtr toRemove)
{  
  Tile& tile = getTile(toRemove->getX(), toRemove->getY());
  return tile.actors->remove( toRemove );
}

void Map::render(TCODConsole *console)
{
  for(u32 y = 0; y < _height; ++y)
  {
    for(u32 x = 0; x < _width; ++x)
    {
      renderTile(x, y, console);
    }
  }
}

void Map::renderTile(u32 x, u32 y, TCODConsole *console)
{
  TCODColor     color      = TCODColor::black;
  unsigned char character  = ' ';

  if ( isInFov(x,y) )         //Tile is in the field of view
  {
    Tile&    tile  = getTile(x, y);
    ActorPtr actor = tile.top();

    color     = actor ? actor->getColor() : tile.getColor();
    character = actor ? actor->getChar()  : tile.getChar();
    updateTile(tile);
  }
  else if ( isExplored(x,y) ) //Tile is beyond the 'fog of war'
  {
    Tile&    tile  = getTile(x, y);
    ActorPtr actor = tile.top([](ActorPtr a){ return !a->isFovOnly(); });

    color     = actor ? actor->getColor() : tile.getColor() * 0.6;
    character = actor ? actor->getChar()  : tile.getChar();
  }

  console->setChar( x, y, character );
  console->setCharForeground( x, y, color );
}

void Map::updateTiles()
{
  for ( auto row : _tiles )
  {
    for ( auto tile : row )
    {
      updateTile(tile);
    }
  }
}

void Map::updateTile(Tile& tile)
{
  ActorPtr actor = tile.top();

  bool walkable    = actor ? tile.isWalkable() && !actor->blocks() : tile.isWalkable();
  bool transparent = actor ? actor->isTransparent()                : tile.isTransparent();

  _codMap.setProperties( tile.x, tile.y, transparent, walkable );
}

void Map::updateTile(u32 x, u32 y)
{
  updateTile( getTile(x, y) );
}

void Map::computeFov(int x, int y, int radius)
{
  _codMap.computeFov(x,y,radius);
}

void Map::deserializeTiles(std::vector<unsigned char> tiles)
{
  for (int pos = 0; pos + sizeof(SerializedTile) <= tiles.size(); pos += sizeof(SerializedTile) )
  {
    SerializedTile* serialized = reinterpret_cast<SerializedTile*>(&tiles[pos]);

    Tile& tile = getTile(serialized->x, serialized->y);
    tile.deserialize( *serialized );
  }

  updateTiles();
}

std::vector<unsigned char> Map::serializeTiles()
{
  std::vector<unsigned char> v;

  for (auto t = _tiles.begin(); t != _tiles.end(); ++t)
  {
    TileRow& trow = *t;
    for (auto ct = trow.begin(); ct != trow.end(); ++ct)
    {
      Tile& tile = *ct;

      auto serialized = tile.serialize();
      v.insert( v.end(), serialized.begin(), serialized.end() );
    }
  }

  return v;
}

TCODColor Map::getColor(u32 x, u32 y)
{
  return getTile(x, y).getColor();
}

char Map::getChar(u32 x, u32 y)
{
  return getTile(x, y).getChar();
}

Tile& Map::getTile(u32 x, u32 y)
{  
  validateMapCoords(x, y);

  TileRow& tRow = _tiles[y];
  return tRow[x];
}

void Map::validateMapCoords(u32 x, u32 y)
{
  if (x >= _width || y >= _height)
    throw amarlon_exeption("Requested map coordinates beyond map borders!\n y=" +
                           std::to_string(y) + ", height="+std::to_string(_height) +
                           " x="+std::to_string(x) + " width=" + std::to_string(_width) + " mapId=" + std::to_string((int)_id)
                           );

  if (y >= _tiles.size())
    throw amarlon_exeption("Tile not initalized!");

  if (x >= _tiles[y].size())
    throw amarlon_exeption("Tile not initalized!");
}

u32 Map::getWidth() const
{
  return _width;
}

void Map::setWidth(const u32 &width)
{
  _width = width;
}
u32 Map::getHeight() const
{
  return _height;
}

void Map::setHeight(const u32 &height)
{
  _height = height;
}
MapId Map::getId() const
{
  return _id;
}

void Map::setId(const MapId &id)
{
  _id = id;
}

void Map::onExit(Direction direction, ActorPtr exiter)
{
  auto dIter = _exitActions.find(direction);
  if ( dIter != _exitActions.end() )
  {
    exiter->performAction( dIter->second );
  }
}

const std::map<Direction, ActorActionPtr> Map::getExitActions() const
{
  return _exitActions;
}

MapPtr Map::clone()
{
  MapPtr cloned = std::make_unique<Map>(_width, _height);
  cloned->_id = _id;
  cloned->_tiles = _tiles;
  cloned->updateTiles();

  cloned->performActionOnActors( [cloned](ActorPtr a)
  {
    a->setMap(cloned);
  });

  for ( auto pair : _exitActions )
  {
    cloned->_exitActions[ pair.first ] = ActorActionPtr{ pair.second->clone() };
  }

  return cloned;
}

ContainerPtr Map::getActorsContainer(u32 x, u32 y)
{
  return getTile(x,y).actors;
}

void Map::performActionOnActors(std::function<void(ActorPtr )> func)
{
  for(auto& tileRow : _tiles)
  {
    for(auto& tile : tileRow)
    {
      tile.actors->performActionOnActors( func );
    }
  }

}

}
