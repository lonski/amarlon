#ifndef SPELL_SLOT_PANEL_H
#define SPELL_SLOT_PANEL_H

#include <asub_panel.h>
#include <spell_book.h>

namespace amarlon { namespace gui {

class AMenu;
class SpellBookWindow;
typedef std::shared_ptr<AMenu> AMenuPtr;

class SpellSlotPanel : public ASubPanel
{
public:
  SpellSlotPanel(SpellBookWindow& parent);

  virtual void selectNext();
  virtual void selectPrevious();
  virtual void setSpellBook(SpellBookPtr spellbook);
  virtual void activate();
  virtual void deactivate();

  virtual void update();
  virtual void manage();

private:
  AMenuPtr _slots;
  SpellBookPtr _spellbook;
  SpellBookWindow& _parent;

};

}}

#endif // SPELL_SLOT_PANEL_H
