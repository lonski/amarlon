#ifndef SPELL_SLOT
#define SPELL_SLOT

#include <memory>

namespace amarlon {

class Spell;
typedef std::shared_ptr<Spell> SpellPtr;

struct SpellSlot
{
  SpellSlot(int lv = 0, bool prepared = false, SpellPtr s = nullptr)
    : level(lv)
    , isPrepared(prepared)
    , spell(s)
  {}

  /**
   * @brief Spell level. "spell" field can be null
   *        if no spell is assigned to this slot.
   */
  int level;

  /**
   * @brief True if spell is preapared and is ready to cast.
   *        False if rest is needed to renew the spell
   */
  bool isPrepared;

  /**
   * @brief Spell assigned to this slot
   */
  SpellPtr spell;

  /**
   * @brief Clears the spell assigned to slot
   */
  void clear()
  {
    isPrepared = false;
    spell = nullptr;
  }

private:

};

typedef std::shared_ptr<SpellSlot> SpellSlotPtr;

}

#endif // SPELL_SLOT

