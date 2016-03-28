#ifndef ACTOR_WRAPPER_H
#define ACTOR_WRAPPER_H

#include <memory>
#include <damage.h>

namespace amarlon {

class Actor;
class StatusEffect;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<StatusEffect> StatusEffectPtr;

namespace lua_api {

class ActorWrapper
{
public:
  ActorWrapper(ActorPtr actor);
  ~ActorWrapper();

  int getLevel();
  int getX() const;
  int getY() const;
  void takeHeal(Damage takeHeal, ActorWrapper healer);
  void takeDamage(Damage dmg, ActorWrapper attacker);
  void setAttackModifier(int modifier);
  int  getAttackModifier() const;
  void setSavingThrowModifier(int modifier, int savingThrowType);
  int  getSavingThrowModifier(int savingThrowType);
  void setMoraleModifier(int modifier);
  int  getMoraleModifier();
  void addStatusEffect(StatusEffectPtr effect);
  bool isAllyOf(ActorWrapper actor);
  std::string getName() const;

  ActorPtr getActor() const;

private:
  ActorPtr _actor;

};

}}

#endif // ACTOR_WRAPPER_H
