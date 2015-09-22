#ifndef STATUS_EFFECTS_MANAGER_H
#define STATUS_EFFECTS_MANAGER_H

#include <memory>
#include <list>
#include <vector>

namespace amarlon {

class Actor;
class Effect;
class StatusEffectsManager;
typedef std::shared_ptr<StatusEffectsManager> StatusEffectsManagerPtr;
typedef std::shared_ptr<Effect> EffectPtr;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::weak_ptr<Actor> ActorWPtr;

class StatusEffectsManager
{
public:
  StatusEffectsManager(ActorPtr owner = nullptr);

  void add(EffectPtr effect);
  void remove(EffectPtr effect);
  void tick(int time = 1);

  std::vector<EffectPtr> getPermamentEffects() const;
  std::vector<EffectPtr> getTemporaryEffects() const;

  StatusEffectsManagerPtr clone();

private:
  ActorWPtr _owner;
  std::list<EffectPtr> _permEffects;
  std::list<EffectPtr> _tempEffects;

};

}

#endif // STATUS_EFFECTS_MANAGER_H
