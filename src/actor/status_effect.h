#ifndef STATUS_EFFECT_H
#define STATUS_EFFECT_H

#include <memory>
#include <spell_id.h>
#include <target.h>
#include <string>

namespace amarlon {

class StatusEffect
{
public:
  StatusEffect(SpellId spell, int duration);

  bool cancel(Target target);
  int getDuration() const;
  void setDuration(int duration);
  std::string getName() const;
  SpellId getSpellId() const;

  bool operator==(const StatusEffect& rhs);

private:
  SpellId _spell;
  int _duration;

};

typedef std::shared_ptr<StatusEffect> StatusEffectPtr;

}

#endif // STATUS_EFFECT_H
