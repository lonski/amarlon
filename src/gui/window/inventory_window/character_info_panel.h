#ifndef CHARACTER_INFO_PANEL_H
#define CHARACTER_INFO_PANEL_H

#include <inventory_panel.h>
#include <alist.h>

namespace amarlon { namespace gui {

class CharacterInfo : public AInventoryPanel
{
public:
  CharacterInfo(int w, int h);
  ~CharacterInfo();

  virtual void selectNext();
  virtual void selectPrevious();
  virtual bool isActivable() const { return false; }

  virtual void update();

private:
  AListPtr _col1;
  AListPtr _col2;
};

typedef std::shared_ptr<CharacterInfo> CharacterInfoPtr;

}}

#endif // CHARACTER_INFO_PANEL_H
