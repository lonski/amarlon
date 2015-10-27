#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#include <character.h>

namespace amarlon {

struct LevelData;

class PlayableCharacter : public Character
{
public:

  PlayableCharacter();
  PlayableCharacter(DescriptionPtr dsc);
  ~PlayableCharacter();

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

  /* overriden functions */
  virtual CarryingCapacity::LoadLevel getLoadLevel();
  virtual int getBaseAttackBonus();
  virtual int getMeleeAttackBonus();
  virtual int getMissileAttackBonus();
  virtual Damage getDamage();
  virtual int modifyExperience(int modifier);
  virtual int getSpeed();
  virtual bool abilityRoll(AbilityScore::Type as, int extraModifier = 0);

  /* class specific functions */
  virtual int getAbilityScore(AbilityScore::Type as);
  virtual void advanceLevel();

private:
  std::map<AbilityScore::Type, int> _abilityScores;

  int getModifier(AbilityScore::Type as);
  void advanceLevel(LevelData data);

  int getEquipmentWeight();
  int calculateInventoryItemsWeight();
  int calculateWearedItemsWeight();

  int calculateLoadPenalty();

};

typedef std::shared_ptr<PlayableCharacter> PlayableCharacterPtr;

}

#endif // PLAYABLE_CHARACTER_H
