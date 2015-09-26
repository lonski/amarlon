#ifndef STATUS_EFFECTS_MANAGER_H
#define STATUS_EFFECTS_MANAGER_H

#include <memory>
#include <list>
#include <vector>
#include <spell_id.h>
#include <target.h>

namespace amarlon {

class Actor;
class StatusEffectsManager;
class StatusEffect;
typedef std::shared_ptr<StatusEffectsManager> StatusEffectsManagerPtr;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::weak_ptr<Actor> ActorWPtr;
typedef std::shared_ptr<StatusEffect> StatusEffectPtr;

class StatusEffectsManager
{
public:
  StatusEffectsManager(ActorPtr owner = nullptr);

  void add(StatusEffectPtr effect);
  void remove(StatusEffectPtr effect);
  void tick(int time = 1);

  std::vector<StatusEffectPtr> getEffects() const;

  StatusEffectsManagerPtr clone();

private:
  ActorWPtr _owner;
  std::list<StatusEffectPtr> _effects;

  void notifyAdd(StatusEffectPtr e);
  void notifyRemove(StatusEffectPtr e);
};

}

#endif // STATUS_EFFECTS_MANAGER_H
