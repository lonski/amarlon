#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <map>
#include <memory>
#include <gui/window/window.h>

namespace amarlon { namespace gui {

class WindowManager
{
public:
  WindowManager() {}

  /**
   * @brief Returns a window of asked type. The windows are lazy initalized.
   *        Once created window will persist. Before each return, window is set to
   *        defaults using Window::setDefaults methos.
   */
  template<typename T>
  T& getWindow();

private:
  std::map<Window::WindowId, WindowPtr> _windows;

};

typedef std::shared_ptr<WindowManager> WindowManagerPtr;

// === IMPLEMENTATION === //

template<typename T>
T& WindowManager::getWindow()
{
  auto found = _windows.find( T::getId() );
  if ( found == _windows.end() )
  {
    found = _windows.insert( std::make_pair(T::getId(), WindowPtr(new T)) ).first;
  }

  T& t = *(std::dynamic_pointer_cast<T>(found->second));
  t.setDefaults();

  return t;
}

}}

#endif // WINDOW_MANAGER_H
