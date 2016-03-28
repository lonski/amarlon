#include "apanel_button.h"

namespace amarlon { namespace gui {

APanelButton::APanelButton(int w, const std::string &label)
  : ASubPanel(w,5)
  , _btn( new ASlotMenuItem(w,label,"",""))
  , _callback( [](){} )
{
  setFrame(false);
  _btn->setPosition(0,0);
  addWidget(_btn);
  deactivate();
}

void APanelButton::activate()
{
  ASubPanel::activate();
  _btn->select();
}

void APanelButton::deactivate()
{
  ASubPanel::deactivate();
  _btn->deselect();
}

void APanelButton::setCallBack(std::function<void ()> callback)
{
  _callback = callback;
}

void APanelButton::manage()
{
  _callback();
}

}}
