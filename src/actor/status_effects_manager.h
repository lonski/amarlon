#ifndef STATUS_EFFECTS_MANAGER_H
#define STATUS_EFFECTS_MANAGER_H

#include <memory>
#include <list>
#include <vector>
#include <spell_id.h>
#include <target.h>
#include <colored_string.h>

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
  StatusEffectsManagerPtr clone();

  bool add(StatusEffectPtr effect);
  void remove(StatusEffectPtr effect);
  void remove(const std::string &name);
  void removeAll();
  void tick(int time = 1);

  std::vector<StatusEffectPtr> getEffects() const;
  std::vector<ColoredString> getEffectsStringList() const;
  bool hasEffect(const std::string &name) const;

private:
  ActorWPtr _owner;
  std::list<StatusEffectPtr> _effects;

  void notifyAdd(StatusEffectPtr e);
  void notifyRemove(StatusEffectPtr e);
};

}

#endif // STATUS_EFFECTS_MANAGER_H
