#ifndef SPELLBOOKWINDOW_H
#define SPELLBOOKWINDOW_H

#include <awindow.h>
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

class SpellBookWindow : public AWindow
{
public:
  SpellBookWindow();
  virtual ~SpellBookWindow();

  static WindowId getId() { return AWindow::SPELLBOOK; }

  virtual SpellBookWindow& setSpellBook(SpellBookPtr spellbook);
  virtual AWindow& show();

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

  std::map<Panel, ASubPanelPtr> _panels;
  Panel _activePanel;

  SpellLevelPanelPtr  _levels;
  SpellSlotPanelPtr   _slots;
  KnownSpellsPanelPtr _known;

  void handleKey(TCOD_key_t key);
  void activateNextPanel();
  void activatePreviousPanel();

};

}}

#endif // SPELLBOOKWINDOW_H
