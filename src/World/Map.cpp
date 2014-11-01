#include "Map.h"
#include "Actor/Actor.h"
#include <iostream>
#include <algorithm>

namespace amarlon {

TileDB Map::Tiles;
MapGateway Map::Gateway;

using namespace std;

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

Map::~Map()
{
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

  Tile& tile = getTile(x, y);
  for(auto aIter = tile.actors->begin(); aIter != tile.actors->end(); ++aIter)
  {    
    if ( (*aIter)->blocks() )
    {
      actorBlocks = true;
      break;
    }
  }

  return terrianBlocks || actorBlocks;
}

void Map::addActor(Actor *actor)
{
  int x( actor->getX() );
  int y( actor->getY() );
  Tile& tile = getTile(x, y);

  //keep alive actors on top
  std::function<bool(Actor*)> addFunBack = [&tile](Actor* a){ return tile.actors->add(a); };
  std::function<bool(Actor*)> addFunFront = [&tile](Actor* a){ return tile.actors->addFront(a); };

  std::function<bool(Actor*)> addFun = actor->isAlive() ? addFunBack : addFunFront;

  if ( !addFun(actor) ) throw std::logic_error("Failed to add actor to tile!");

  //update transparency
  if ( codMap.isTransparent(x,y) && !actor->isTransparent() )
  {
    codMap.setProperties(x,y, false, codMap.isWalkable(x,y));
  }

}

Actor *Map::getFirstActor(int x, int y)
{
  Tile& tile = getTile(x, y);
  return tile.actors->size() > 0 ? *tile.actors->begin() : nullptr;
}

std::vector<Actor *> Map::getActors(int x, int y, bool (*filterFun)(Actor*) )
{
  std::vector<Actor*> r;
  Tile& tile = getTile(x, y);

  std::for_each(tile.actors->begin(), tile.actors->end(), [&](Actor* a)
  {    
    if ( filterFun == nullptr || filterFun(a))  r.push_back(a);
  });

  return r;
}

std::vector<Actor *> Map::getActors(std::function<bool(Actor *)>* filterFun)
{
  std::vector<Actor*> r;

  for(auto tileRow = _tiles.begin(); tileRow != _tiles.end(); ++tileRow)
  {
    for(auto tile = tileRow->begin(); tile != tileRow->end(); ++tile)
    {
      std::for_each(tile->actors->begin(), tile->actors->end(), [&](Actor* a)
      {
        if ( filterFun == nullptr || (*filterFun)(a)) r.push_back(a);
      });
    }
  }

  return r;
}

bool Map::removeActor(Actor* toRemove)
{
  Tile& tile = getTile(toRemove->getX(), toRemove->getY());
  return tile.actors->remove( toRemove );
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
  std::for_each(_tiles.begin(), _tiles.end(), [&](TileRow& tileRow)
  {
    std::for_each(tileRow.begin(), tileRow.end(), [&](Tile& tile)
    {
      for (auto aIter = tile.actors->begin(); aIter != tile.actors->end(); ++aIter)
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
    });
  });

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
    throw std::out_of_range("Requested map coordinates beyond map borders!\n y=" +
                            std::to_string(y) + ", height="+std::to_string(_height) +
                            " x="+std::to_string(x) + " width=" + std::to_string(_width)
                            );

  if (y >= _tiles.size())
    throw std::out_of_range("Tile not initalized!");

  if (x >= _tiles[y].size())
    throw std::out_of_range("Tile not initalized!");
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

Container &Map::getActorsContainer(u32 x, u32 y)
{
  return *getTile(x,y).actors;
}

}
