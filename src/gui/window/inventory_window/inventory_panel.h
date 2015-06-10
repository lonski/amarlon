#ifndef INVENTORY_PANEL
#define INVENTORY_PANEL

#include <memory>
#include <apanel.h>

namespace amarlon { namespace gui {

class AInventoryPanel : public APanel
{
public:
  AInventoryPanel(int w, int h)
    : APanel(w, h)
    , _active(false)
  {
  }

  virtual ~AInventoryPanel() {}
  virtual bool isActive() const { return _active; }
  virtual void activate() { _active = true; }
  virtual void deactivate() { _active = false; }
  virtual bool isActivable() const { return true; }

  virtual void selectNext() = 0;
  virtual void selectPrevious() = 0;

private:
  bool _active;

};

typedef std::shared_ptr<AInventoryPanel> AInventoryPanelPtr;

}}

#endif // INVENTORY_PANEL

