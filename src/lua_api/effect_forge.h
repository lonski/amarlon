#ifndef EFFECT_FORGE_H
#define EFFECT_FORGE_H

#include <string>
#include <vector>
#include <memory>
#include <effect_description.h>

namespace sel {
class State;
}

namespace amarlon {

class Effect;
typedef std::shared_ptr<Effect> EffectPtr;

namespace lua_api {

class EffectForge
{
public:
  EffectForge();

  void newRecipe();
  void setEffectType(int type);
  void setEffectTime(int time);
  void setEffectParam(std::string name, std::string value);
  void pushRecipe();

  std::vector<EffectPtr> produce();

  static void reg(sel::State& state);

private:
  EffectDescription _currentRecipe;
  std::vector<EffectDescription> _recipes;

};

}}

#endif // EFFECT_FORGE_H
