#ifndef STATUS_EFFECT_H
#define STATUS_EFFECT_H

#include <memory>
#include <spell_id.h>
#include <target.h>
#include <string>

namespace amarlon {

class Spell;
typedef std::shared_ptr<Spell> SpellPtr;

class StatusEffect
{
public:
  StatusEffect(const std::string& name, const std::string& script, int duration);

  bool cancel(Target target);
  bool tickDay(Target target);
  int getDuration() const;
  void setDuration(int duration);
  std::string getName() const;
  std::string getScript() const;

  bool operator==(const StatusEffect& rhs);

private:
  std::string _name;
  std::string _script;
  int _duration;

};

typedef std::shared_ptr<StatusEffect> StatusEffectPtr;

}

#endif // STATUS_EFFECT_H
