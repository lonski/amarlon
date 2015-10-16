#ifndef TRAP_H
#define TRAP_H

#include <actor_feature.h>
#include <target.h>
#include <spell_id.h>

namespace amarlon {

class Actor;
class Trap;
class Spell;
struct TrapDescription;
typedef std::shared_ptr<TrapDescription> TrapDescriptionPtr;
typedef std::shared_ptr<Trap> TrapPtr;
typedef std::shared_ptr<Spell> SpellPtr;

class Trap : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;

  Trap();
  virtual ~Trap();

  static TrapPtr create(DescriptionPtr dsc);

  virtual ActorFeature::Type getType();
  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

  virtual void trigger(Target victim);

  virtual bool isArmed() const;
  virtual void setArmed(bool armed);

  /**
   * @brief Describes how hard is to disarm this trap.
   */
  virtual int getDifficulty();

  virtual SpellId getSpellId() const;

private:
  bool _armed;
  SpellPtr _spell;
  int _difficulty;

};

}

#endif // TRAP_H
