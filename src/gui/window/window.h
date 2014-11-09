#ifndef WINDOW_H
#define WINDOW_H

#include <memory>

namespace amarlon { namespace gui {

class Window
{
public:
  /**
   * @brief This enum is used to identify windows by WindowManager.
   */
  enum WindowId
  {
    INVENTORY,
    AMOUNT,
    PICKUP,
    TEXT
  };

  /**
   * @brief executes window and waits for user input
   */
  virtual Window& show() = 0;

  /**
   * @brief sets default values of window. Is called everytime when
   *        window is retrieved via WindowManager.
   */
  virtual Window& setDefaults() { return *this; }

  /**
   * @brief a dynamic cast wrapper, which is intended to use
   *        for example when making a function composition
   */
  template<typename T>
  T& downcast();

protected:
  Window() {}

};

typedef std::shared_ptr<Window> WindowPtr;

// === IMPLEMENTATION === //

template<typename T>
T& Window::downcast()
{
  T* t = dynamic_cast<T*>(this);
  assert(t != nullptr);

  return *t;
}


}}

#endif // WINDOW_H
