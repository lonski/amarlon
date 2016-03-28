#ifndef APANEL_BUTTON_H
#define APANEL_BUTTON_H

#include <asub_panel.h>
#include <aslot_menu_item.h>

namespace amarlon { namespace gui {

class APanelButton : public ASubPanel
{
public:
  APanelButton(int w, const std::string& label);

  virtual void selectNext() {}
  virtual void selectPrevious() {}
  void activate();
  void deactivate();
  void setCallBack(std::function<void()> callback);
  void manage();

private:
  ASlotMenuItemPtr _btn;
  std::function<void()> _callback;

};

typedef std::shared_ptr<APanelButton> PanelButtonPtr;

}}

#endif // APANEL_BUTTON_H
