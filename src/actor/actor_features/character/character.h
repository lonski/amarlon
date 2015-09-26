#ifndef character_H
#define character_H

#include <map>
#include <set>
#include <actor_feature.h>
#include <races.h>
#include <character_classes.h>
#include <ability_scores.h>
#include <saving_throws_table.h>
#include <carrying_capacity.h>
#include <spell_id.h>
#include <damage.h>
#include <item_slot_type.h>

namespace amarlon {

class Character;
class Pickable;
class Spell;
struct CharacterDescription;
typedef std::shared_ptr<Character> CharacterPtr;
typedef std::shared_ptr<Pickable> PickablePtr;
typedef std::shared_ptr<Spell> SpellPtr;
typedef std::shared_ptr<CharacterDescription> CharacterDescriptionPtr;

class Character : public ActorFeature
{
public:

  class Creator
  {
  public:
    virtual ~Creator() {}
    virtual CharacterPtr create(CharacterDescriptionPtr dsc) = 0;

  protected:
    void fillCommonCharacterPart(CharacterPtr character, CharacterDescriptionPtr dsc);

  };

  const static ActorFeature::Type featureType;
  virtual ActorFeature::Type getType() { return featureType; }

  Character();
  static CharacterPtr create(DescriptionPtr dsc);

  virtual bool isEqual(ActorFeaturePtr rhs) const;

  virtual bool isAlive() const;
  virtual int getHitPoints() const;
  virtual int getMaxHitPoints() const;
  virtual void setHitPoints(int newHp);
  virtual int modifyHitPoints(int modifier);
  virtual int takeDamage(Damage dmg, ActorPtr attacker);
  virtual int takeHeal(Damage heal, ActorPtr healer);
  virtual int getExperience() const;
  virtual void modifyExperience(int modifier);
  virtual int getLevel() const;
  virtual CharacterClass getClass() const;
  virtual Race getRace() const;
  virtual int getSavingThrow(SavingThrows::Type type);

  /**
   * @brief Temporary saving throws modifiers granted by effects.
   */
  virtual int getTmpSavingThrowModifier(SavingThrows::Type type);
  virtual void setTmpSavingThrowModifier(SavingThrows::Type type, int modifier);

  virtual int getSpeed();
  virtual int getMovePoints();
  virtual void setMovePoints(int points);

  virtual CarryingCapacity::LoadLevel getLoadLevel() = 0;
  virtual int getBaseAttackBonus() = 0;
  virtual int getMeleeAttackBonus() = 0;

  /**
   * @brief Temporary attack bonus granted by effects
   */
  virtual int getTmpAttackModifier();
  virtual void setTmpAttackModifier(int bonus);

  virtual Damage getDamage() = 0;
  virtual int getArmorClass();
  virtual std::vector<SpellPtr> getSpells() const;

  virtual std::string getDescription();

protected:
  virtual void setLevel(int level);
  virtual void setMaxHitPoints(int maxHp);
  PickablePtr getEquippedItem(ItemSlotType slot);

private:
  int _level;
  int _hitPoints;
  int _maxHitPoints;
  int _defaultArmorClass;
  int _experience;
  CharacterClass _class;
  Race _race;
  int _speed;
  int _movePoints;
  int _extraAttackBonus;
  std::set<SpellPtr> _spells;
  std::map<SavingThrows::Type, int> _savingThrowsTmpMods;

  friend class Character::Creator;
  friend class CharacterSerializer;

};


}

#endif // character_H
