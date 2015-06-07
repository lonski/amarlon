#ifndef character_H
#define character_H

#include <actor_feature.h>
#include <actor_descriptions.h>
#include <map>
#include <ability_scores.h>
#include <character_classes.h>

namespace amarlon {

class Character;
class Pickable;
typedef std::shared_ptr<Character> CharacterPtr;
typedef std::shared_ptr<Pickable> PickablePtr;

class Character : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;

  Character();
  static CharacterPtr create(DescriptionPtr dsc);

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs);
  virtual ActorFeature::Type getType() { return featureType; }

  bool isAlive() const;

  int getHitPoints() const;
  int getMaxHitPoints() const;
  void setHitPoints(int newHp);
  void modifyHitPoints(int modifier);

  int getExperience() const;
  int getLevel() const;
  CharacterClass getClass() const;

  /**
   * @brief Returns the Attack Bonus based on character level
   *        and STR modifier
   */
  int getMeleeAttackBonus();

  /**
   * @brief Returns a damage roll based on character's weapon
   *        and STR modifier
   */
  int rollMeleeDamage();

  /**
   * @brief Retrives Armor Class of equipped armor.
   *        If no armor is equipped, returns AC value without armor.
   */
  int getArmorClass();

  /**
   * @brief Returns the value of givem Ability Score
   */
  int getAbilityScore(AbilityScore::Type as);

private:
  int _hitPoints;
  int _maxHitPoints;
  int _attackBonus;
  int _level;
  int _experience;
  std::map<AbilityScore::Type, int> _abilityScores;
  CharacterClass _class;

  PickablePtr getEquippedItem(ItemSlotType slot);
  int getModifier(AbilityScore::Type as);

};


}

#endif // character_H
