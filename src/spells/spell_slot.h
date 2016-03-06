#ifndef SPELL_SLOT
#define SPELL_SLOT

#include <memory>
#include <spellbook_description.h>
#include <spell.h>

namespace amarlon {

class Spell;
struct SpellSlot;
typedef std::shared_ptr<Spell> SpellPtr;
typedef std::shared_ptr<SpellSlot> SpellSlotPtr;

struct SpellSlot
{
  SpellSlot(int lv = 0, bool prepared = false, SpellPtr s = nullptr)
    : level(lv)
    , isPrepared(prepared)
    , spell(s)
  {}

  SpellSlot(const SpellSlot& slot)
  {
    *this = slot;
  }

  SpellSlotPtr clone() const
  {
    return SpellSlotPtr( new SpellSlot(*this) );
  }

  SpellSlotDescriptionPtr toDescriptionStruct()
  {
    SpellSlotDescriptionPtr dsc(new SpellSlotDescription);
    dsc->level = level;
    dsc->prepared = isPrepared;
    dsc->spell = spell ? (int)spell->getId() : 0;

    return dsc;
  }

  SpellSlot& operator=(const SpellSlot& rhs)
  {
    level = rhs.level;
    isPrepared = rhs.isPrepared;
    spell = rhs.spell ? rhs.spell->clone() : nullptr;
  }

  bool operator==(const SpellSlot& rhs) const
  {
    return level == rhs.level &&
           isPrepared == rhs.isPrepared &&
           ( ( spell && *spell == *rhs.spell ) || ( spell == nullptr && rhs.spell == nullptr) );
  }

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
};

}

#endif // SPELL_SLOT

