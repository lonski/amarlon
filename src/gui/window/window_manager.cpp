#include "window_manager.h"

namespace amarlon { namespace gui {

std::vector<WindowPtr> WindowManager::getWindows(std::function<bool (WindowPtr)> filter)
{
  std::vector<WindowPtr> windows;

  for(auto wpair : _windows)
  {
    if ( filter(wpair.second) )
    {
      windows.push_back(wpair.second);
    }
  }

  return windows;
}

}}
