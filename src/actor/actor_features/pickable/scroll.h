#ifndef SCROLL_H
#define SCROLL_H

#include <memory>
#include <pickable.h>

namespace amarlon {

class Spell;
typedef std::shared_ptr<Spell> SpellPtr;

class Scroll : public Pickable
{
public:
  Scroll(DescriptionPtr dsc = nullptr);
  virtual DescriptionPtr toDescriptionStruct(ActorFeaturePtr cmp = nullptr);
  virtual ~Scroll();

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

  /**
   * @brief Cast the spell. Check if executor (caster) has valid class to do so.
   */
  virtual bool use(ActorPtr executor, const Target& target);

  /**
   * @brief Transcribes the spell from scroll to transcriber's spellbook
   */
  virtual bool transcribe(ActorPtr transcriber);

  SpellPtr getSpell() const;

  virtual bool isUsable() const;
  virtual TargetType getTargetType() const;
  virtual int getRange() const;
  virtual int getRadius() const;

private:
  SpellPtr _spell;

};

typedef std::shared_ptr<Scroll> ScrollPtr;

}

#endif // SCROLL_H
