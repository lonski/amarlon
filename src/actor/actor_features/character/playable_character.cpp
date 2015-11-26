#include "playable_character.h"
#include <actor.h>
#include <die_action.h>
#include <experience_table.h>
#include <race.h>
#include <inventory.h>
#include <actor_descriptions.h>
#include <character_class.h>
#include <spell_book.h>
#include <engine.h>
#include <spell_db.h>
#include <spell.h>
#include <character_type.h>

namespace amarlon {

PlayableCharacter::PlayableCharacter()
{
}

PlayableCharacter::PlayableCharacter(DescriptionPtr dsc)
  : Character(dsc)
{
}

DescriptionPtr PlayableCharacter::toDescriptionStruct(ActorFeaturePtr cmp)
{
  CharacterDescriptionPtr dsc;
  CharacterPtr cmpChr = std::dynamic_pointer_cast<PlayableCharacter>(cmp);

  dsc.reset( new CharacterDescription );
  Character::toDescriptionStruct( dsc, cmpChr );
  dsc->type = static_cast<int>(CharacterType::PlayableCharacter);

  return dsc;
}

PlayableCharacter::~PlayableCharacter()
{
}

ActorFeaturePtr PlayableCharacter::clone()
{
  auto* c = new PlayableCharacter(*this);
  cloneBase(c);
  return ActorFeaturePtr( c );
}

bool PlayableCharacter::isEqual(ActorFeaturePtr rhs) const
{  
  bool equal = false;
  PlayableCharacterPtr crhs = std::dynamic_pointer_cast<PlayableCharacter>(rhs);

  if (crhs != nullptr)
  {
    equal = Character::isEqual( rhs );
  }

  return equal;
}

int PlayableCharacter::modifyExperience(int modifier)
{
  modifier = Character::modifyExperience(modifier);

  ActorPtr actor = getOwner().lock();
  if ( actor )
  {
    actor->notify(Event( (modifier > 0 ? EventId::Actor_ExperienceGained : EventId::Actor_ExperienceLost),
                         { {"value", std::to_string(std::abs(modifier))} } ));
  }

  if ( getLevel() < Experience::MAX_LEVEL )
  {
    LevelData data = Experience::getLevelData(getClass()->getType(), getLevel() + 1);
    if ( data.expNeeded != 0 && getExperience() >= data.expNeeded)
    {
      advanceLevel(data);

      ActorPtr actor = getOwner().lock();
      if ( actor )
      {
        actor->notify(Event(EventId::Actor_LeveledUp));
      }

      //TODO: maybe popup some window or advance te level manually like BG/NWN?
    }
  }

  return modifier;
}

void PlayableCharacter::advanceLevel()
{
  advanceLevel( Experience::getLevelData(getClass()->getType(), getLevel() + 1) );
}

void PlayableCharacter::advanceLevel(LevelData data)
{
  setLevel( getLevel() + 1 );

  int hpBonus =  static_cast<int>( data.hitDice ); //always maximum hp
      hpBonus += data.hpBonus;
      hpBonus += data.applyConModifier ? getModifier(AbilityScore::CON) : 0;

  setMaxHitPoints( getMaxHitPoints() + std::max(hpBonus, 1) );
  modifyHitPoints( hpBonus );

  //Add new spell slots
  if ( !data.spellSlotCount.empty() )
  {
    SpellBookPtr sb = getSpellBook();
    for ( const auto& pair : data.spellSlotCount )
    {
      int slotCount = sb->getSlotCount( pair.first );

      //New spell level reached
      if ( slotCount == 0 && pair.second > 0 && getClass()->getType() == CharacterClassType::Cleric )
      {
         sb->addKnownSpells(getClass()->getType(), pair.first );
      }

      //Insert the slots
      while ( slotCount < pair.second )
      {
        sb->addSlot( new SpellSlot( pair.first ) );
        ++slotCount;
      }
    }
  }

}

}

