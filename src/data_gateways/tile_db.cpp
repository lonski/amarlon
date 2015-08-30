#include "tile_db.h"
#include <fstream>
#include <vector>
#include <utils/utils.h>
#include <memory>

namespace amarlon {

using namespace std;
using namespace rapidxml;

TileDB::TileDB()
{
}

TileType TileDB::getType(char ch)
{
  TileType tType = TileType::Null;

  for( auto t : _tiles)
  {
    if ( t.second.code == ch)
    {
      tType = t.first;
      break;
    }
  }

  return tType;
}

template<typename T>
T TileDB::get(TileType type, T TileDescription::*field, T defValue)
{
  auto it = _tiles.find( type );
  return it != _tiles.end() ? it->second.*field : defValue;
}

char TileDB::getChar(TileType type)
{
  return get<char>(type, &TileDescription::character, '#');
}

TCODColor TileDB::getColor(TileType type)
{
  return get<TCODColor>(type, &TileDescription::color, TCODColor::white);
}

bool TileDB::isWalkable(TileType type)
{
  return get<bool>(type, &TileDescription::walkable, false);
}

bool TileDB::isTransparent(TileType type)
{
  return get<bool>(type, &TileDescription::transparent, false);
}

void TileDB::loadTiles(const string& fn)
{
  ifstream ifs(fn);

  if (ifs.is_open())
  {
    vector<char> buffer;
    buffer.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    buffer.push_back('\0');

    parseTiles(buffer);
  }
}

void TileDB::parseTiles(vector<char>& dataToParse)
{
  xml_document<> doc;
  doc.parse<0>(&dataToParse[0]);

  xml_node<>* root = doc.first_node("Tiles");
  xml_node<>* tileNode = root ? root->first_node("Tile") : nullptr;

  while( tileNode != nullptr )
  {
    _tileParser.setSource( tileNode );

    std::unique_ptr<TileDescription> tileDsc( _tileParser.parseTileDsc() );
    if ( tileDsc ) _tiles[ tileDsc->type ] = *tileDsc;

    tileNode = tileNode->next_sibling();
  }

  doc.clear();
}

}
