#ifndef STATUS_EFFECTS_MANAGER_H
#define STATUS_EFFECTS_MANAGER_H

#include <memory>
#include <list>
#include <vector>

namespace amarlon {

class Effect;
class StatusEffectsManager;
typedef std::shared_ptr<StatusEffectsManager> StatusEffectsManagerPtr;
typedef std::shared_ptr<Effect> EffectPtr;

class StatusEffectsManager
{
public:
  StatusEffectsManager();

  void add(EffectPtr effect);
  void remove(EffectPtr effect);
  void tick(int time = 1);

  std::vector<EffectPtr> getPermamentEffects() const;
  std::vector<EffectPtr> getTemporaryEffects() const;

  StatusEffectsManagerPtr clone();

private:
  std::list<EffectPtr> _permEffects;
  std::list<EffectPtr> _tempEffects;

};

}

#endif // STATUS_EFFECTS_MANAGER_H
