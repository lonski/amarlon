#ifndef STATUS_EFFECT_H
#define STATUS_EFFECT_H

#include <memory>
#include <spell_id.h>
#include <target.h>
#include <string>
#include <actor.pb.h>

namespace amarlon {

class Spell;
typedef std::shared_ptr<Spell> SpellPtr;

class StatusEffect
{
public:
  StatusEffect(const std::string& name, const std::string& script, int duration);
  StatusEffect(const StatusEffectData& data);
  StatusEffect(const StatusEffect& e);

  void operator=(const StatusEffect& rhs);
  bool operator==(const StatusEffect& rhs) const;

  const StatusEffectData& getData() const;

  bool cancel(Target target);
  int getDuration() const;
  void setDuration(int duration);
  std::string getName() const;
  std::string getScript() const;

private:
  StatusEffectData _data;

};

typedef std::shared_ptr<StatusEffect> StatusEffectPtr;

}

#endif // STATUS_EFFECT_H
