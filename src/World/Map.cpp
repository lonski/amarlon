#include "Map.h"
#include "Actor/Actor.h"
#include <iostream>
#include <algorithm>

TileDB Map::Tiles;
MapGateway Map::Gateway;

Map::Map(u32 width, u32 height, MapId id)
  : _id(id)
  , _width(width)
  , _height(height)
  , codMap(width, height)
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

bool Map::isExplored(int x, int y)
{
  return getTile(x,y).explored;
}

bool Map::isInFov(int x, int y)
{
  bool inFov = codMap.isInFov(x,y);

  if (inFov) getTile(x,y).explored = true;

  return inFov;
}

bool Map::isBlocked(int x, int y)
{
  bool terrianBlocks = !codMap.isWalkable(x,y);
  bool actorBlocks = false;

  for(auto aIter = _actors.begin(); aIter != _actors.end(); ++aIter)
  {
    Actor* a = *aIter;
    if (a->getX() == x && a->getY() == y && a->blocks())
    {
      actorBlocks = true;
      break;
    }
  }

  return terrianBlocks || actorBlocks;
}

void Map::addActor(Actor *actor)
{
  if (actor->isAlive())
  {
    _actors.push_back(actor);
  }
  else
  {
    _actors.push_front(actor);
  }

  int x( actor->getX() );
  int y( actor->getY() );
  if ( codMap.isTransparent(x,y) && !actor->isTransparent() )
  {
    codMap.setProperties(x,y, false, codMap.isWalkable(x,y));
  }
}

Actor *Map::getFirstActor(int x, int y)
{
  auto aIter = std::find_if(_actors.begin(), _actors.end(), [&](Actor* a)
  {
    return (a->getX() == x && a->getY() == y);
  });

  return ( aIter == _actors.end() ? nullptr : *aIter );
}

std::vector<Actor *> Map::getActors(int x, int y, bool (*filterFun)(Actor*) )
{
  std::vector<Actor*> r;

  std::for_each(_actors.begin(), _actors.end(), [&](Actor* a)
  {
    if (a->getX() == x && a->getY() == y)
    {
      if ( filterFun == nullptr || filterFun(a))
        r.push_back(a);
    }
  });

  return r;
}

std::vector<Actor *> Map::getActors(bool (*filterFun)(Actor *))
{
  std::vector<Actor*> r;

  std::for_each(_actors.begin(), _actors.end(), [&](Actor* a)
  {
    if ( filterFun == nullptr || filterFun(a))
      r.push_back(a);
  });

  return r;
}

bool Map::removeActor(Actor* toRemove)
{
  auto aIter = std::find(_actors.begin(), _actors.end(), toRemove);
  bool found = (aIter != _actors.end());

  if (found)
  {
    _actors.erase(aIter);
  }

  return found;
}

const Map::ActorArray &Map::actors() const
{
  return _actors;
}

void Map::render(TCODConsole *console)
{
  //render tiles
  for(u32 y = 0; y < _height; ++y)
  {
    for(u32 x = 0; x < _width; ++x)
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
  }

  //render actors
  for (auto aIter = _actors.begin(); aIter != _actors.end(); ++aIter)
  {
    Actor* actor = *aIter;

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

void Map::updateActorCells()
{
  std::for_each(_actors.begin(), _actors.end(), [&](Actor* a){ updateActorCell(a); });
}

void Map::updateActorCell(Actor* actor)
{
  codMap.setProperties(actor->getX(),
                       actor->getY(),
                       actor->isTransparent(),
                       codMap.isWalkable(actor->getX(), actor->getY()));
}

void Map::computeFov(int x, int y, int radius)
{
  codMap.computeFov(x,y,radius);
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

      codMap.setProperties(x,y,transparent, walkable);

      ++x;
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

//===== Map getTile
Tile &Map::getTile(u32 x, u32 y)
{
  validateMapCoords(x, y);

  TileRow& tRow = _tiles[y];
  return tRow[x];
}

void Map::validateMapCoords(u32 x, u32 y)
{
  if (x >= _width || y >= _height)
    throw std::out_of_range("Koordynaty mapy wieksze niz jej rozmiary!\n y=" +
                            std::to_string(y) + ", height="+std::to_string(_height) +
                            " x="+std::to_string(x) + " width=" + std::to_string(_width)
                            );

  if (y >= _tiles.size())
    throw std::out_of_range("Nie zainicjalizowane tile!");

  if (x >= _tiles[y].size())
    throw std::out_of_range("Nie zainicjalizowane tile!");
}
//~~~~~

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



