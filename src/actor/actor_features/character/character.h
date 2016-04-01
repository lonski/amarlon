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
#include <relations.h>
#include <actor.pb.h>

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
  const static ActorFeature::Type FeatureType;

  static CharacterPtr create(const CharacterData& data);

  Character();
  Character(const Character& rhs);
  virtual ~Character();

  bool operator==(const Character& rhs) const;
  Character& operator=(const Character& rhs);
  virtual const CharacterData& getData() const;
  virtual const ::google::protobuf::Message& getDataPolymorphic() const;

  virtual ActorFeature::Type getFeatureType();
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
  virtual bool abilityRoll(AbilityScore::Type as, int extraModifier = 0);

  virtual int getSpeed();
  virtual int getMovePoints();
  virtual void setMovePoints(int points);

  virtual CarryingCapacity::LoadLevel getLoadLevel();
  virtual int getBaseAttackBonus();
  virtual int getMeleeAttackBonus();
  virtual int getMissileAttackBonus();

  virtual Damage getBareHandsDamage();
  virtual Damage getDamage();
  virtual int getArmorClass(DamageType dmgType = DamageType::Physical);
  virtual SpellBookPtr getSpellBook();
  virtual std::string getDescription();
  virtual std::vector<SkillPtr> getSkills() const;
  virtual std::vector<SkillPtr> getSkills(std::function<bool(SkillPtr)> filter) const;
  virtual SkillPtr getSkill(SkillId id) const;
  virtual int getAbilityScore(AbilityScore::Type as);
  int getModifier(AbilityScore::Type as);

  virtual int getMorale();

  /**
   * @brief Restores character HP and spells.
   */
  virtual void rest();

  /**
   * @brief Character modifiers
   */
  virtual void addModifier(const Modifier& mod);
  virtual void removeModifier(const Modifier& mod);

  virtual relations::Team getTeam() const;
  virtual void setTeam(relations::Team team);
  void turnHostileTo(ActorPtr attacker);

  virtual std::string debug(const std::string &linebreak);

protected:
  Character(const CharacterData& data);
  virtual void setLevel(int level);
  virtual void setMaxHitPoints(int maxHp);
  PickablePtr getEquippedItem(ItemSlotType slot);
  void cloneBase(Character* c);
  virtual void setAbilityScore(AbilityScore::Type as, int value);

private:
  mutable CharacterData _data;

  std::vector<SkillPtr> _skills;
  SpellBookPtr _spellbook;

  void initialize();
  void updateData() const;
  SkillPtr getModifiedSkill(SkillPtr s) const;
  int getEquipmentWeight();
  int calculateInventoryItemsWeight();
  int calculateWearedItemsWeight();
  int calculateLoadPenalty();

protected:
  std::vector<Modifier> _modifiers;

  friend class CharacterSerializer;

};


}

#endif // character_H
