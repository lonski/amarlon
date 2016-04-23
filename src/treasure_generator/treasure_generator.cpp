#include "treasure_generator.h"
#include <dices.h>
#include <xml/rapidxml.hpp>
#include <xml_utils.h>
#include <fstream>

using namespace rapidxml;

namespace amarlon {

TreasureGenerator::TreasureGenerator()
{

}

ActorContainer TreasureGenerator::generate(TreasureType /*tt*/)
{
  return ActorContainer();
}

ActorPtr TreasureGenerator::generateMagicWeapon()
{
  return _weaponGenerator.generate( _itemData.ids[BaseItemData::Weapon] );
}

bool TreasureGenerator::load(const std::string &fn)
{
  std::ifstream ifs(fn);

  if (ifs.is_open())
  {
    _itemData.ids.clear();

    std::vector<char> buf;
    buf.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    buf.push_back('\0');

    xml_document<> doc;
    doc.parse<0>(&buf[0]);

    xml_node<>* tg = doc.first_node("TreasureGenerator");

    //Parse item bases
    xml_node<>* itemBases = tg ? tg->first_node("ItemBases") : nullptr;
    xml_node<>* itemBase = itemBases ? itemBases->first_node("ItemBase") : nullptr;

    while(itemBase != nullptr)
    {
      std::vector<int> ids;

      xml_node<>* itemNode = itemBase->first_node("Item");
      while ( itemNode != nullptr )
      {
        ids.push_back( getAttribute<int>(itemNode, "id") );
        itemNode = itemNode->next_sibling();
      }

      if ( !ids.empty() )
        _itemData.ids[
            Str2BaseItemDataType[getAttribute<std::string>(itemBase, "type")] ]
              = ids;

      itemBase = itemBase->next_sibling();
    }

    return true;
  }
  return false;
}

}
