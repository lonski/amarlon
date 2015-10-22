#ifndef INVENTORY_PANEL
#define INVENTORY_PANEL

#include <memory>
#include <apanel.h>

namespace amarlon { namespace gui {

class ASubPanel : public APanel
{
public:
  ASubPanel(int w, int h)
    : APanel(w, h)
    , _active(false)
  {
  }

  virtual ~ASubPanel() {}
  virtual bool isActive() const { return _active; }
  virtual void activate() { _active = true; }
  virtual void deactivate() { _active = false; }
  virtual bool isActivable() const { return true; }
  virtual void manage() {}
  virtual void update() {}

  virtual void selectNext() = 0;
  virtual void selectPrevious() = 0;

private:
  bool _active;

};

typedef std::shared_ptr<ASubPanel> ASubPanelPtr;

}}

#endif // INVENTORY_PANEL

