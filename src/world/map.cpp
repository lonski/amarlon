#include "map.h"
#include <algorithm>
#include <actor.h>
#include <amarlon_except.h>
#include <actor_action.h>
#include <utils.h>
#include <libtcod.hpp>
#include <actor_container.h>
#include <teleport_action.h>

namespace amarlon {

using namespace std;

Map::Map(const MapData &data)
{
  _data.CopyFrom(data);
  initialize();
}

const MapData &Map::getData() const
{
  updateData();
  return _data;
}

Map& Map::operator=(const Map &rhs)
{
  if ( this != &rhs )
  {
    rhs.updateData();
    _data.CopyFrom(rhs._data);
    initialize();
  }
  return *this;
}

void Map::initialize()
{
  _codMap.reset( new TCODMap(getWidth(), getHeight()) );

  //Load Tiles
  allocateTiles();
  uint32 y(0), x(0);
  for( auto it = _data.tiles().begin(); it != _data.tiles().end(); ++it )
  {
    Tile& tile = getTile(x, y);
    tile.setState( *it );

    if ( x == getWidth() - 1 )
    {
      x = 0;
      ++y;
    }
    else
    {
      ++x;
    }
  }

  //Load Actors
  for( auto it = _data.actors().begin(); it != _data.actors().end(); ++it )
  {
    addActor( Actor::create(*it) );
  }

  //Load Teleports
  for( auto it = _data.teleports().begin(); it != _data.teleports().end(); ++it )
  {
    Direction direction = static_cast<Direction>(it->direction());

    _exitActions[ direction ] = std::make_shared<TeleportAction>(
                                  static_cast<MapId>(it->map_id()),
                                  it->x(),
                                  it->y()
                                );
  }

  updateTiles();
}

void Map::allocateTiles()
{
  _tiles.clear();
  for (u32 y = 0; y < getHeight(); ++y)
  {
    TileRow row;
    for(u32 x = 0; x < getWidth(); ++x)
    {
      row.push_back(Tile());
    }
    _tiles.push_back(row);
  }
}

void Map::updateData() const
{
  //Update tiles
  _data.mutable_tiles()->Clear();
  for( const TileRow& row : _tiles )
    for( const Tile& tile : row )
      _data.mutable_tiles()->Add()->CopyFrom(tile.getState());

  //Update Teleports
  _data.mutable_teleports()->Clear();
  for ( auto& kv : _exitActions )
  {
    TeleportActionPtr action = std::dynamic_pointer_cast<TeleportAction>(kv.second);
    TeleportActionData* tp = _data.mutable_teleports()->Add();
    tp->set_direction( static_cast<int>(action->getMapId()) );
    tp->set_x( static_cast<int>(action->getX()) );
    tp->set_y( static_cast<int>(action->getY()) );
  }

  //Update Actors
  _data.mutable_actors()->Clear();
  for ( ActorPtr actor : getActors() )
    _data.mutable_actors()->Add()->CopyFrom(actor->getData());

}

Map::~Map()
{
}

bool Map::isExplored(int x, int y)
{
  return getTile(x,y).isExplored();
}

bool Map::isExplored(const Point &p)
{
  return isExplored(p.x, p.y);
}

bool Map::isInFov(int x, int y)
{
  bool inFov = _codMap->isInFov(x,y);

  if (inFov) getTile(x,y).setExplored(true);

  return inFov;
}

bool Map::isInFov(const Point &p)
{
  return isInFov(p.x, p.y);
}

bool Map::isBlocked(int x, int y)
{
  ActorPtr actor = getTile(x,y).top();
  bool actorBlocks = actor ? actor->isBlocking() : false;
  return !_codMap->isWalkable(x,y) || actorBlocks;
}

bool Map::isBlocked(const Point &p)
{
  return isBlocked(p.x, p.y);
}

bool Map::isTransparent(int x, int y) const
{
  return _codMap->isTransparent(x,y);
}

bool Map::isTransparent(const Point &p) const
{
  return isTransparent(p.x, p.y);
}

void Map::addActor(ActorPtr actor)
{
  Tile& tile = getTile( actor->getX(), actor->getY() );

  tile.addActor(actor);
  actor->setMap( shared_from_this() );

  for ( auto a : tile.getActors() ) a->interract( actor );
}

ActorPtr Map::getFirstActor(int x, int y) const
{
  return getTile(x, y).top();
}

std::vector<ActorPtr > Map::getActors(int x, int y, std::function<bool(ActorPtr)> filterFun) const
{
  const Tile& tile = getTile(x, y);
  return tile.getActors( filterFun ).toVector();
}

std::vector<ActorPtr> Map::getActors(const Point &p, std::function<bool (ActorPtr)> filterFun) const
{
  return getActors(p.x, p.y, filterFun);
}

std::vector<ActorPtr> Map::getActors(int x, int y, int radius, std::function<bool (ActorPtr)> filterFun) const
{
  std::vector<ActorPtr> actors;
  for( uint32_t ly = 0; ly < getHeight(); ++ly )
  {
    for( uint32_t lx = 0; lx < getWidth(); ++lx )
    {
      if ( calculateDistance(x, y, lx, ly ) <= radius )
      {
        auto actorsFromTile = getActors(lx,ly,filterFun);
        actors.insert(actors.end(), actorsFromTile.begin(), actorsFromTile.end());
      }
    }
  }
  return actors;
}

std::vector<ActorPtr> Map::getActors(int x, int y, int radius) const
{
  return getActors(x,y,radius, [](ActorPtr){return true;});
}

std::vector<ActorPtr> Map::getActors(std::function<bool(ActorPtr)> filterFun) const
{
  std::vector<ActorPtr> r;

  for(const auto& tileRow : _tiles)
  {
    for(const auto& tile : tileRow)
    {
      auto actorsFromTile = tile.getActors( filterFun ).toVector();
      r.insert( r.end(), actorsFromTile.begin(), actorsFromTile.end() );
    }
  }

  return r;
}

std::vector<ActorPtr> Map::getActors() const
{
  return getActors([](ActorPtr){return true;});
}

bool Map::removeActor(ActorPtr toRemove)
{  
  Tile& tile = getTile(toRemove->getX(), toRemove->getY());
  return tile.removeActor( toRemove );
}

void Map::render(TCODConsole *console)
{
  for(u32 y = 0; y < getHeight(); ++y)
  {
    for(u32 x = 0; x < getWidth(); ++x)
    {
      renderTile(x, y, console);
    }
  }
}

void Map::renderTile(u32 x, u32 y, TCODConsole *console)
{
  //console->setCharBackground( x, x, TCODColor::black );
  ActorPtr actor;

  if ( isInFov(x,y) )         //Tile is in the field of view
  {
    Tile&    tile  = getTile(x, y);
    actor = tile.top([](ActorPtr a){ return a->isVisible() || a->isPlayerControlled(); });

    console->setChar( x, y, tile.getChar() );
    console->setCharForeground( x, y, tile.getColor() );

    updateTile(x, y);
  }
  else if ( isExplored(x,y) ) //Tile is beyond the 'fog of war'
  {
    Tile&    tile  = getTile(x, y);
    actor = tile.top([](ActorPtr a){ return !a->isFovOnly() && a->isVisible(); });

    console->setChar( x, y, tile.getChar() );
    console->setCharForeground( x, y, tile.getColor()*0.6 );
  }

  if ( actor ) actor->render(console);
}

void Map::updateTiles()
{
  for ( uint32_t y = 0; y < getHeight(); ++y )
  {
    for ( uint32_t x = 0; x < getWidth(); ++x )
    {
      updateTile(x, y);
    }
  }
}

void Map::updateTile(u32 x, u32 y)
{
  Tile& tile = getTile(x, y);
  ActorPtr actor = tile.top();

  bool walkable    = tile.isWalkable();
  bool transparent = actor ? actor->isTransparent(): tile.isTransparent();

  _codMap->setProperties( x, y, transparent, walkable );
}

void Map::computeFov(int x, int y, int radius)
{
  _codMap->computeFov(x,y,radius);
}

TCODMap& Map::getCODMap()
{
  return *_codMap;
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

const Tile& Map::getTile(u32 x, u32 y) const
{
  validateMapCoords(x, y);

  const TileRow& tRow = _tiles[y];
  return tRow[x];
}

void Map::validateMapCoords(u32 x, u32 y) const
{
  if (x >= getWidth() || y >= getHeight())
    throw amarlon_exeption("Requested map coordinates beyond map borders!\n y=" +
                           std::to_string(y) + ", height="+std::to_string(getHeight()) +
                           " x="+std::to_string(x) + " width=" + std::to_string(getWidth()) + " mapId=" + std::to_string((int)getId())
                           );

  if (y >= _tiles.size())
    throw amarlon_exeption("Tile not initalized!");

  if (x >= _tiles[y].size())
    throw amarlon_exeption("Tile not initalized!");
}

u32 Map::getWidth() const
{
  return _data.width();
}

u32 Map::getHeight() const
{
  return _data.height();
}

MapId Map::getId() const
{
  return static_cast<MapId>(_data.id());
}

void Map::setId(const MapId &id)
{
  _data.set_id(static_cast<int>(id));
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

void Map::performActionOnActors(std::function<void(ActorPtr )> func)
{
  for(auto& tileRow : _tiles)
  {
    for(auto& tile : tileRow)
    {
      for( auto a : tile.getActors() )
      {
        func(a);
      }
    }
  }

}

}

