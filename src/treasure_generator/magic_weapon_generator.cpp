#include "magic_weapon_generator.h"

namespace amarlon {

MagicWeaponGenerator::MagicWeaponGenerator()
{

}

ActorPtr MagicWeaponGenerator::generate(const std::vector<int> baseIDs)
{
  if ( baseIDs.size() > 0 )
  {
    int i = dices::roll(0, baseIDs.size() - 1);
    ActorPtr actor = Actor::create( baseIDs[i] );

    if ( actor )
    {
      rollWeaponBonuses(actor);
      randomAmountForMagicAmunition(actor);
    }

    return actor;
  }
  return nullptr;
}

void MagicWeaponGenerator::randomAmountForMagicAmunition(ActorPtr actor)
{
  PickablePtr p = actor->getFeature<Pickable>();
  if ( p->getItemType().category == PickableCategory::Amunition )
  {
    p->setAmount( dices::roll(1,10));
  }
}

void MagicWeaponGenerator::rollWeaponBonuses(ActorPtr actor)
{
  PickablePtr p = actor->getFeature<Pickable>();
  int roll = dices::roll(dices::D100);

  applyDamageBonus(actor, roll);

  if ( roll >= 96 ) //Cursed
  {
    p->setCursed(true);
  }
  else if ( p->getItemType().isMeleeWeapon() && roll >= 86 && roll <= 95 )
  {
    applyDamageBonus(actor, dices::roll(dices::D100));
    rollSpecialAbility(actor);
  }

}

void MagicWeaponGenerator::rollSpecialAbility(ActorPtr actor)
{
  PickablePtr item = actor->getFeature<Pickable>();

  int roll = dices::roll(dices::D20);

  //TODO: Implement weapon special abilities
  static std::map<int, std::pair<SpellId,UseType> > spellIds = {
    { 20, std::make_pair(SpellId::Null,        UseType::InfiniteUse) },
    { 19, std::make_pair(SpellId::Null,        UseType::InfiniteUse) },
    { 16, std::make_pair(SpellId::Null,        UseType::InfiniteUse) },
    { 12, std::make_pair(SpellId::Null,        UseType::InfiniteUse)  },
    { 11, std::make_pair(SpellId::CharmPerson, UseType::DailyUse) },
    {  9, std::make_pair(SpellId::Null,        UseType::InfiniteUse)  }
  };

  auto it = std::find_if(spellIds.begin(), spellIds.end(), [roll](auto& kv){
    return roll <= kv.first;
  });

  if ( it->second.first != SpellId::Null )
  {
    SpellPtr spell = Spell::create(it->second.first);

    item->setSpell(spell);
    item->setUseType(it->second.second);
    item->setUseRestriction(UseRestriction::UsableWhenEquipped);
    item->setUsesCount(1);

    actor->setName( actor->getName() + " of " + spell->getName());
  }
}

void MagicWeaponGenerator::applyDamageBonus(ActorPtr actor, int roll)
{
  PickablePtr p = actor->getFeature<Pickable>();

  std::pair<int,int> bonus = p->getItemType().isMeleeWeapon() ? getMeleeDamageBonus(roll)
                                                              : getRangedDamageBonus(roll);

  if ( bonus.first != 0 )
  {
    p->getMutableDamage()->value += bonus.first;
    actor->setName( actor->getName() + " +" + std::to_string(std::abs(bonus.first)));
  }

  if ( bonus.second != 0 )
  {
    int speciesRoll = dices::roll(dices::D6);

    int dmg = p->getDamage().specialDamage[ (SpeciesType)speciesRoll ];
    p->getMutableDamage()->specialDamage[ (SpeciesType)speciesRoll ] = dmg + bonus.second;
  }
}

std::pair<int, int> MagicWeaponGenerator::getMeleeDamageBonus(int roll)
{
  static std::map<int, std::pair<int,int> > damageBonuses = {
    { 100, std::make_pair(-2,0) },
    { 98,  std::make_pair(-1,0) },
    { 95,  std::make_pair(0,0)  },
    { 85,  std::make_pair(1,3)  },
    { 75,  std::make_pair(1,2)  },
    { 58,  std::make_pair(5,0)  },
    { 57,  std::make_pair(4,0)  },
    { 55,  std::make_pair(3,0)  },
    { 50,  std::make_pair(2,0)  },
    { 40,  std::make_pair(1,0)  }
  };

  auto it = std::find_if(damageBonuses.begin(), damageBonuses.end(), [roll](auto& kv){
    return roll <= kv.first;
  });

  return it->second;
}

std::pair<int, int> MagicWeaponGenerator::getRangedDamageBonus(int roll)
{
  static std::map<int, std::pair<int,int> > damageBonuses = {
    { 100, std::make_pair(-2,0) },
    { 98,  std::make_pair(-1,0) },
    { 94,  std::make_pair(1,3)  },
    { 82,  std::make_pair(1,2)  },
    { 64,  std::make_pair(3,0)  },
    { 58,  std::make_pair(2,0)  },
    { 46,  std::make_pair(1,0)  }
  };

  auto it = std::find_if(damageBonuses.begin(), damageBonuses.end(), [roll](auto& kv){
    return roll <= kv.first;
  });

  return it->second;
}

}
