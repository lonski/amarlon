#ifndef SPELLLEVELPANEL_H
#define SPELLLEVELPANEL_H

#include <asub_panel.h>

namespace amarlon { namespace gui {

class AMenu;
class SpellBookWindow;
typedef std::shared_ptr<AMenu> AMenuPtr;

class SpellLevelPanel : public ASubPanel
{
public:
  SpellLevelPanel(SpellBookWindow& parent);

  virtual void selectNext();
  virtual void selectPrevious();
  virtual void activate();
  virtual void deactivate();

  virtual int getSelectedLevel();

private:
  AMenuPtr _levels;
  SpellBookWindow& _parent;

};

}}

#endif // SPELLLEVELPANEL_H
