#include "TileDB.h"
#include "Utils/utils.h"
#include <fstream>
#include <vector>

using namespace std;
using namespace rapidxml;

TileDB::TileDB()
{
  //loadTiles("d:/tiles.xml");
}

TileType TileDB::getType(char ch)
{
  TileType tType = TileType::Null;

  for(auto t = _tiles.begin(); t != _tiles.end(); ++t)
  {
    TileDescription& dsc = t->second;
    if ( dsc.code == ch)
    {
      tType = t->first;
      break;
    }
  }

  return tType;
}

char TileDB::getChar(TileType type)
{
  char ch = '#';
  if (_tiles.count(type))
    ch = _tiles[type].character;

  return ch;
}

char TileDB::getCode(TileType type)
{
  char ch = '#';
  if (_tiles.count(type))
    ch = _tiles[type].code;

  return ch;
}

TCODColor TileDB::getColor(TileType type)
{
  return _tiles[type].color;
}

bool TileDB::isWalkable(TileType type)
{
  bool w = false;
  if (_tiles.count(type))
    w = _tiles[type].walkable;

  return w;
}

bool TileDB::isTransparent(TileType type)
{
  bool t = false;
  if (_tiles.count(type))
    t = _tiles[type].transparent;

  return t;
}

bool TileDB::loadTiles(string fn)
{
  bool success = false;
  ifstream ifs(fn);

  if (ifs.is_open())
  {
    vector<char> buffer;
    buffer.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    buffer.push_back('\0');

    xml_document<> doc;
    doc.parse<0>(&buffer[0]);

    xml_node<>* root = doc.first_node("Tiles");
    xml_node<>* tileNode = root->first_node("Tile");

    while( tileNode != nullptr )
    {
      TileDescription tileDsc;
      tileDsc.character = tileNode->first_attribute("character")->value()[0];
      tileDsc.code = tileNode->first_attribute("code")->value()[0];

      string colorStr = tileNode->first_attribute("color")->value();
      tileDsc.color = strToColor(colorStr);

      TileType id = (TileType)std::stoi( tileNode->first_attribute("id")->value() );

      tileDsc.walkable = (bool)std::stoi( tileNode->first_attribute("walkable")->value() );
      tileDsc.transparent = (bool)std::stoi( tileNode->first_attribute("transparent")->value() );

      _tiles[id] = tileDsc;
      tileNode = tileNode->next_sibling();
    }

    doc.clear();
    success = true;
  }

  return success;
}
