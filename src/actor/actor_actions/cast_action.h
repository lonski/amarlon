#ifndef CAST_ACTION_H
#define CAST_ACTION_H

#include <memory>
#include <actor_action.h>
#include <target.h>

namespace amarlon {

class Spell;
typedef std::shared_ptr<Spell> SpellPtr;

class CastAction : public ActorAction
{
public:
    CastAction(SpellPtr spell, Target target);
    virtual ~CastAction();

    virtual ActorActionResult perform(ActorPtr caster);
    virtual ActorActionUPtr clone();

private:
    SpellPtr _spell;
    ActorPtr _caster;
    Target _target;

    bool isClassCorrect() const;
    bool isLevelCorrect() const;
};

typedef std::shared_ptr<CastAction> CastActionPtr;
typedef std::unique_ptr<CastAction> CastActionUPtr;

}

#endif // CAST_ACTION_H
