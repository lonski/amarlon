#include "map.h"
#include <iostream>

TileDB Map::Tiles;
MapGateway Map::Gateway;

Map::Map(u32 width, u32 height, MapId id)
  : _width(width)
  , _height(height)
  , codMap(width, height)
  , _id(id)
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

bool Map::isExplored(u32 x, u32 y)
{
  return getTile(x,y).explored;
}

bool Map::isInFov(u32 x, u32 y)
{
  bool inFov = codMap.isInFov(x,y);

  if (inFov) getTile(x,y).explored = true;

  return inFov;
}

bool Map::isBlocked(u32 x, u32 y)
{
  return !codMap.isWalkable(x,y);
}

void Map::render(TCODConsole *console)
{
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
}

void Map::computeFov(u32 x, u32 y, int radius)
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



