#include "effect_forge.h"
#include <effect.h>
#include <selene.h>

namespace amarlon { namespace lua_api {

EffectForge::EffectForge()
{ 
}

void EffectForge::newRecipe()
{
  _currentRecipe = EffectDescription();
}

void EffectForge::setEffectType(int type)
{
  _currentRecipe.type = static_cast<EffectType>(type);
}

void EffectForge::setEffectTime(int time)
{
  _currentRecipe.time = time;
}

void EffectForge::setEffectParam(std::string name, std::string value)
{
  _currentRecipe.params[name] = value;
}

void EffectForge::pushRecipe()
{
  _recipes.push_back( _currentRecipe );
}

std::vector<EffectPtr> EffectForge::produce()
{
  std::vector<EffectPtr> effects;

  for ( auto& r : _recipes )
  {
    effects.push_back( Effect::create(r) );
  }

  return effects;
}

void EffectForge::reg(sel::State &state)
{
  state["EffectForge"].SetClass<lua_api::EffectForge>( "newRecipe",      &lua_api::EffectForge::newRecipe,
                                                       "setEffectType",  &lua_api::EffectForge::setEffectType,
                                                       "setEffectParam", &lua_api::EffectForge::setEffectParam,
                                                       "pushRecipe",     &lua_api::EffectForge::pushRecipe);
}

}}

