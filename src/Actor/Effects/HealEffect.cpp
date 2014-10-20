#include "HealEffect.h"
#include <Actor/Actor.h>
#include "Gui/Gui.h"

HealEffect::HealEffect()
{
}

bool HealEffect::apply(Actor *executor, std::vector<Actor *>)
{
  bool r = false;

  if ( executor->afFighter() )
  {
    int healed = executor->afFighter()->heal(_healAmount);

    Gui::Root.message("You've been healed for "+std::to_string(healed)+".", TCODColor::lighterBlue);

    --_usesCount;
    r = true;
  }

  return r;
}

void HealEffect::load(const EffectDescription &dsc)
{
  _healAmount = dsc.heal;
  _usesCount = dsc.uses;
}
