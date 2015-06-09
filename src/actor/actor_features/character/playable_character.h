#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#include <character.h>

namespace amarlon {

class PlayableCharacter : public Character
{
public:
  PlayableCharacter();
  ~PlayableCharacter();

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs);

  /* overriden functions */
  virtual int getMeleeAttackBonus();
  virtual int rollMeleeDamage();

  /* class specific functions */
  virtual int getAbilityScore(AbilityScore::Type as);

private:
  std::map<AbilityScore::Type, int> _abilityScores;

  int getModifier(AbilityScore::Type as);

  friend class Character;
};

typedef std::shared_ptr<PlayableCharacter> PlayableCharacterPtr;

}

#endif // PLAYABLE_CHARACTER_H
