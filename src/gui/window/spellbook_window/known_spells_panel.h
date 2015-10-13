#ifndef KNOWN_SPELLS_PANEL_H
#define KNOWN_SPELLS_PANEL_H

#include <asub_panel.h>
#include <spell_book.h>

namespace amarlon { namespace gui {

class AMenu;
class SpellBookWindow;
typedef std::shared_ptr<AMenu> AMenuPtr;

class KnownSpellsPanel : public ASubPanel
{
public:
  KnownSpellsPanel(SpellBookWindow& parent);

  virtual void selectNext();
  virtual void selectPrevious();
  virtual void setSpellBook(SpellBookPtr spellbook);
  virtual void activate();
  virtual void deactivate();

  virtual void update();
  virtual void manage();

private:
  AMenuPtr _spells;
  SpellBookPtr _spellbook;
  SpellBookWindow& _parent;

};

}}

#endif // KNOWN_SPELLS_PANEL_H
