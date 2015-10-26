#ifndef character_H
#define character_H

#include <map>
#include <set>
#include <actor_feature.h>
#include <race_type.h>
#include <character_class_type.h>
#include <ability_scores.h>
#include <saving_throws_table.h>
#include <carrying_capacity.h>
#include <spell_id.h>
#include <damage.h>
#include <item_slot_type.h>
#include <skill_id.h>
#include <modifier.h>

namespace amarlon {

class Character;
class Pickable;
class Spell;
class SpellBook;
class Skill;
class Race;
class CharacterClass;
struct CharacterDescription;
typedef std::shared_ptr<Character> CharacterPtr;
typedef std::shared_ptr<CharacterClass> CharacterClassPtr;
typedef std::shared_ptr<Race> RacePtr;
typedef std::shared_ptr<Pickable> PickablePtr;
typedef std::shared_ptr<Spell> SpellPtr;
typedef std::shared_ptr<SpellBook> SpellBookPtr;
typedef std::shared_ptr<CharacterDescription> CharacterDescriptionPtr;
typedef std::shared_ptr<Skill> SkillPtr;

class Character : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;
  virtual ActorFeature::Type getType() { return featureType; }

  Character();
  Character(DescriptionPtr dsc);
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
  virtual int getExperienceToNextLevel() const;
  virtual int modifyExperience(int modifier);
  virtual int getLevel() const;
  virtual CharacterClassPtr getClass() const;
  virtual RacePtr getRace() const;
  virtual int getSavingThrow(SavingThrows::Type type);
  virtual bool rollSavingThrow(SavingThrows::Type type);

  virtual int getSpeed();
  virtual int getMovePoints();
  virtual void setMovePoints(int points);

  virtual CarryingCapacity::LoadLevel getLoadLevel() = 0;
  virtual int getBaseAttackBonus() = 0;
  virtual int getMeleeAttackBonus() = 0;
  virtual int getMissileAttackBonus() = 0;

  virtual Damage getDamage() = 0;
  virtual int getArmorClass(DamageType dmgType = DamageType::Physical);
  virtual SpellBookPtr getSpellBook();
  virtual std::string getDescription();
  virtual std::vector<SkillPtr> getSkills() const;
  virtual std::vector<SkillPtr> getSkills(std::function<bool(SkillPtr)> filter) const;
  virtual SkillPtr getSkill(SkillId id) const;

  virtual int getMorale() { return 0; }

  /**
   * @brief Restores character HP and spells.
   */
  virtual void rest();

  /**
   * @brief Character modifiers
   */
  virtual void addModifier(const Modifier& mod);
  virtual void removeModifier(const Modifier& mod);

protected:
  virtual void setLevel(int level);
  virtual void setMaxHitPoints(int maxHp);
  PickablePtr getEquippedItem(ItemSlotType slot);
  void cloneBase(Character* c);

private:
  int _level;
  int _hitPoints;
  int _maxHitPoints;
  int _defaultArmorClass;
  int _experience;
  CharacterClassPtr _class;
  RacePtr _race;
  int _speed;
  int _movePoints;
  SpellBookPtr _spellbook;
  std::vector<SkillPtr> _skills;

  SkillPtr getModifiedSkill(SkillPtr s) const;

protected:
  std::vector<Modifier> _modifiers;

  friend class CharacterSerializer;

};


}

#endif // character_H
