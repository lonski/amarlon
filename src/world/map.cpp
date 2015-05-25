#include "map.h"
#include <algorithm>
#include <actor.h>
#include <amarlon_except.h>
#include <actor_action.h>

namespace amarlon {

TileDB Map::Tiles;
MapGateway Map::Gateway;

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
      row.push_back(Tile());
    }
    _tiles.push_back(row);
  }
}

Map::~Map()
{
}

bool Map::isExplored(int x, int y)
{
  return getTile(x,y).explored;
}

bool Map::isInFov(int x, int y)
{
  bool inFov = _codMap.isInFov(x,y);

  if (inFov) getTile(x,y).explored = true;

  return inFov;
}

bool Map::isBlocked(int x, int y)
{
  bool terrianBlocks = !_codMap.isWalkable(x,y);
  bool actorBlocks = false;

  Tile& tile = getTile(x, y);
  for(ActorPtr actor : tile.actors->content())
  {
    if ( actor->blocks() )
    {
      actorBlocks = true;
      break;
    }
  }

  return terrianBlocks || actorBlocks;
}

void Map::addActor(ActorPtr actor)
{  
  u32 x( actor->getX() );
  u32 y( actor->getY() );
  Tile& tile = getTile(x, y);

  if ( !tile.actors->add(actor) ) throw amarlon_exeption("Failed to add actor to tile!");

  //update transparency
  if ( _codMap.isTransparent(x,y) && !actor->isTransparent() )
  {
    _codMap.setProperties(x,y, false, _codMap.isWalkable(x,y));
  }

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
  bool r = tile.actors->remove( toRemove );
  return r;
}

void Map::render(TCODConsole *console)
{
  for(u32 y = 0; y < _height; ++y)
  {
    for(u32 x = 0; x < _width; ++x)
    {
      renderTile(x, y, console);
      renderActorsOnTile(x, y, console);
    }
  }
}

void Map::renderTile(u32 x, u32 y, TCODConsole *console)
{
    bool inFov = isInFov(x,y);
    bool explored = isExplored(x,y);

    if (inFov || explored)
    {
      TCODColor col = ( inFov ? getColor(x,y) : (getColor(x,y) * 0.6));
      console->setChar(x, y, getChar(x, y) );
      console->setCharForeground(x,y,col);
    }
}

void Map::renderActorsOnTile(u32 x, u32 y, TCODConsole *console)
{
    Tile& tile = getTile(x, y);

    tile.actors->sort([](ActorPtr a1, ActorPtr a2)
                      {
                        return a1->getTileRenderPriority() > a2->getTileRenderPriority();
                      });

    for (auto actor : tile.actors->content())
    {
      bool inFov = isInFov(actor->getX(), actor->getY());
      bool onlyInFov = actor->isFovOnly();
      bool explored = isExplored(actor->getX(), actor->getY());

      if (inFov || (!onlyInFov && explored) )
      {
        console->putChar(actor->getX(), actor->getY(), actor->getChar());
        console->setCharForeground(actor->getX(), actor->getY(), actor->getColor());
      }
    }
}

void Map::updateActorCell(ActorPtr actor)
{
  _codMap.setProperties(actor->getX(),
                       actor->getY(),
                       actor->isTransparent(),
                       _codMap.isWalkable(actor->getX(), actor->getY()));
}

void Map::computeFov(int x, int y, int radius)
{
  _codMap.computeFov(x,y,radius);
}

void Map::fill(std::string tilesStr)
{
  int y = 0;
  int x = 0;
  for (auto it = tilesStr.begin(); it != tilesStr.end(); ++it)
  {
    if (*it == '\n')
    {
      ++y;
      x = 0;
    }
    else
    {
      Tile& tile = getTile(x,y);

      tile.type = Map::Tiles.getType(*it);

      bool walkable = Map::Tiles.isWalkable(tile.type);
      bool transparent = Map::Tiles.isTransparent(tile.type);

      _codMap.setProperties(x,y,transparent, walkable);

      ++x;
    }
  }

}

void Map::updateTiles()
{
  for ( u32 y = 0; y < _height; ++y )
  {
    for ( u32 x = 0; x < _width; ++x )
    {
      Tile& tile = getTile(x,y);
      _codMap.setProperties(x,
                            y,
                            Map::Tiles.isTransparent(tile.type),
                            Map::Tiles.isWalkable(tile.type));

      for ( ActorPtr actor : tile.actors->content() )
      {
        updateActorCell(actor);
      }
    }
  }
}

std::string Map::tilesToStr()
{
  std::string str;
  for (auto t = _tiles.begin(); t != _tiles.end(); ++t)
  {
    TileRow& trow = *t;
    for (auto ct = trow.begin(); ct != trow.end(); ++ct)
    {
      Tile& tile = *ct;
      str = str + Tiles.getCode(tile.type);
    }
    str += "\n";
  }

  if (!str.empty())
    str.erase(str.end()-1, str.end());

  return str;
}

TCODColor Map::getColor(u32 x, u32 y)
{
  return Map::Tiles.getColor(getTile(x,y).type);
}

char Map::getChar(u32 x, u32 y)
{
  return Map::Tiles.getChar(getTile(x,y).type);
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
    cloned->_exitActions[ pair.first ] = ActorActionPtr{ std::move(pair.second->clone()) };
  }

  return std::move(cloned);
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
