#ifndef SPELLBOOK_H
#define SPELLBOOK_H

#include <memory>
#include <vector>
#include <spell_slot.h>

namespace amarlon {

class Spell;
class SpellBook;
struct SpellbookDescription;
typedef std::shared_ptr<Spell> SpellPtr;
typedef std::shared_ptr<SpellBook> SpellBookPtr;

class SpellBook
{
public:
  SpellBook();
  static SpellBookPtr create(SpellbookDescription dsc);

  std::vector<SpellSlotPtr> getSlots(std::function<bool(SpellSlotPtr)> filter = [](SpellSlotPtr){return true;}) const;
  std::vector<SpellPtr> getKnownSpells( std::function<bool(SpellPtr)> filter = [](SpellPtr){return true;} ) const;

  void addSlot(SpellSlotPtr slot);
  void addSlot(SpellSlot* slot);

  void addKnownSpell(SpellPtr spell);
  void addKnownSpell(Spell* spell);

  int getSlotCount(int level) const;

  /**
   * @brief Prepares all spells so they will be ready to cast.
   */
  void prepareSpells();

  bool operator==(const SpellBook& rhs);
  SpellBookPtr clone();

private:
  std::vector<SpellSlotPtr> _spellSlots;
  std::vector<SpellPtr>  _knownSpells;

};

}

#endif // SPELLBOOK_H
