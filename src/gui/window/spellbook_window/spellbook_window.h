#ifndef SPELLBOOKWINDOW_H
#define SPELLBOOKWINDOW_H

#include <amultipanel_window.h>
#include <memory>

namespace amarlon {

class SpellBook;
typedef std::shared_ptr<SpellBook> SpellBookPtr;

namespace gui {

class ASubPanel;
class SpellLevelPanel;
class SpellSlotPanel;
class KnownSpellsPanel;
typedef std::shared_ptr<ASubPanel> ASubPanelPtr;
typedef std::shared_ptr<SpellLevelPanel> SpellLevelPanelPtr;
typedef std::shared_ptr<SpellSlotPanel> SpellSlotPanelPtr;
typedef std::shared_ptr<KnownSpellsPanel> KnownSpellsPanelPtr;

class SpellBookWindow : public AMultiPanelWIndow
{
public:
  SpellBookWindow();
  virtual ~SpellBookWindow();

  static WindowId getId() { return AWindow::SPELLBOOK; }

  virtual SpellBookWindow& setSpellBook(SpellBookPtr spellbook);

  virtual SpellLevelPanel&  getLevelsPanel();
  virtual SpellSlotPanel&   getSlotsPanel();
  virtual KnownSpellsPanel& getKnownSpellsPanel();

private:
  enum Panel
  {
    LEVELS,
    SLOTS,
    KNOWN
  };

  SpellBookPtr _spellbook;

  SpellLevelPanelPtr  _levels;
  SpellSlotPanelPtr   _slots;
  KnownSpellsPanelPtr _known;

protected:
  void managePanel(int panel);
  bool exitWindow(TCOD_key_t key);

};

}}

#endif // SPELLBOOKWINDOW_H
