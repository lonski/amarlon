#ifndef character_H
#define character_H

#include <actor_feature.h>
#include <actor_descriptions.h>
#include <map>
#include <ability_scores.h>
#include <character_classes.h>
#include <saving_throws_table.h>
#include <races.h>
#include <carrying_capacity.h>
#include <set>
#include <spell_id.h>
#include <damage_type.h>

namespace amarlon {

class Character;
class Pickable;
class Spell;
typedef std::shared_ptr<Character> CharacterPtr;
typedef std::shared_ptr<Pickable> PickablePtr;
typedef std::shared_ptr<Spell> SpellPtr;

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

  virtual bool isEqual(ActorFeaturePtr rhs);

  virtual bool isAlive() const;
  virtual int getHitPoints() const;
  virtual int getMaxHitPoints() const;
  virtual void setHitPoints(int newHp);
  virtual void modifyHitPoints(int modifier);
  virtual void takeDamage(int damage, DamageType type = DamageType::Physical);
  virtual int getExperience() const;
  virtual void modifyExperience(int modifier);
  virtual int getLevel() const;
  virtual CharacterClass getClass() const;
  virtual Race getRace() const;
  virtual int getSavingThrow(SavingThrows::Type type);

  virtual int getSpeed();
  virtual int getMovePoints();
  virtual void setMovePoints(int points);

  virtual CarryingCapacity::LoadLevel getLoadLevel() = 0;
  virtual int getBaseAttackBonus() = 0;
  virtual int getMeleeAttackBonus() = 0;
  virtual int rollMeleeDamage() = 0;
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
  std::set<SpellPtr> _spells;

  friend class Character::Creator;
  friend class CharacterSerializer;

};


}

#endif // character_H
