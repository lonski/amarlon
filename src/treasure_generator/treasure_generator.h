#ifndef TREASUREGENERATOR_H
#define TREASUREGENERATOR_H

#include <actor.h>
#include <treasure_type.h>
#include <actor_container.h>
#include <base_item_data.h>
#include <magic_weapon_generator.h>

namespace amarlon {

class TreasureGenerator
{
public:
  TreasureGenerator();

  ActorContainer generate(TreasureType tt);
  ActorPtr generateMagicWeapon();

  bool load(const std::string& fn);

private:
  BaseItemData _itemData;
  MagicWeaponGenerator _weaponGenerator;

};

}

#endif // TREASUREGENERATOR_H
