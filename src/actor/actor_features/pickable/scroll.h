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
  Scroll(bool stackable = true, int amount = 1);
  Scroll(DescriptionPtr dsc);
  virtual ~Scroll();

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

  /**
   * @brief Show dialog for player to choose action:
   *        - cast spell
   *        - copy spell to spellbook
   */
  virtual bool use(ActorPtr executor, const Target& target);

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
