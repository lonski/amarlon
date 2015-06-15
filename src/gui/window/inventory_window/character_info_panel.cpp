#include "character_info_panel.h"
#include <character.h>
#include <actor.h>
#include <playable_character.h>
#include <attack_bonus_table.h>

const unsigned MARGIN = 2;

namespace amarlon { namespace gui {

CharacterInfo::CharacterInfo(int w, int h)
  : AInventoryPanel(w, h)
  , _col1( new AList )
  , _col2( new AList )
{
  setTitle("Character info");
  _col1->setPosition(MARGIN, 1);
  _col2->setPosition( getWidth() / 3, 1);

  addWidget( _col1 );
  addWidget( _col2 );
}

CharacterInfo::~CharacterInfo()
{
}

void CharacterInfo::selectNext()
{
}

void CharacterInfo::selectPrevious()
{
}

void CharacterInfo::update()
{
  _col1->clear();
  _col2->clear();

  PlayableCharacterPtr character = std::dynamic_pointer_cast<PlayableCharacter>( Actor::Player->getFeature<Character>() );
  if ( character )
  {
    _col1->pushBack(ColoredString("HP : " + toStr(character->getHitPoints()) + "/" + toStr(character->getMaxHitPoints()) ));
    _col1->pushBack(ColoredString("AC : " + toStr(character->getArmorClass()) ));
    _col1->pushBack(ColoredString("AB : +" + toStr( character->getBaseAttackBonus()) ));
    _col1->pushBack(ColoredString(""));
    _col1->pushBack(ColoredString("Ability Scores", TCODColor::darkerAzure));
    _col1->pushBack(ColoredString(""));
    _col1->pushBack(ColoredString("STR : " + toStr(character->getAbilityScore(AbilityScore::STR)) ));
    _col1->pushBack(ColoredString("INT : " + toStr(character->getAbilityScore(AbilityScore::INT)) ));
    _col1->pushBack(ColoredString("WIS : " + toStr(character->getAbilityScore(AbilityScore::WIS)) ));
    _col1->pushBack(ColoredString("DEX : " + toStr(character->getAbilityScore(AbilityScore::DEX)) ));
    _col1->pushBack(ColoredString("CON : " + toStr(character->getAbilityScore(AbilityScore::CON)) ));
    _col1->pushBack(ColoredString("CHA : " + toStr(character->getAbilityScore(AbilityScore::CHA)) ));

    _col2->pushBack(ColoredString("Class      : " + CharacterClass2Str(character->getClass())));
    _col2->pushBack(ColoredString("Level      : " + toStr(character->getLevel()) ));
    _col2->pushBack(ColoredString("Experience : " + toStr(character->getExperience()) ));
    _col2->pushBack(ColoredString(""));
    _col2->pushBack(ColoredString("Saving Throws", TCODColor::darkerAzure));
    _col2->pushBack(ColoredString(""));
    _col2->pushBack(ColoredString("Death Ray            : " + toStr(character->getSavingThrow(saving_throws_table::DeathRayOrPoison)) ));
    _col2->pushBack(ColoredString("Magic Wands          : " + toStr(character->getSavingThrow(saving_throws_table::MagicWands)) ));
    _col2->pushBack(ColoredString("Paralysis or Petrify : " + toStr(character->getSavingThrow(saving_throws_table::ParalysisOrPertrify)) ));
    _col2->pushBack(ColoredString("Dragon Breath        : " + toStr(character->getSavingThrow(saving_throws_table::DragonBreath)) ));
    _col2->pushBack(ColoredString("Spells               : " + toStr(character->getSavingThrow(saving_throws_table::Spells)) ));
  }
}

}}
