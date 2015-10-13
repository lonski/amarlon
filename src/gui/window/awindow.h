#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <apanel.h>
#include <cassert>

namespace amarlon { namespace gui {

class AWindow : public APanel
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
    TEXT,
    MENU,
    RESIZABLE_TEXT,
    FIXED_SIZE_TEXT,
    GAME_MENU,
    LOAD_SAVE_GAME,
    INPUT,
    SPELLBOOK,
    QUESTION
  };

  /**
   * @brief executes window and waits for user input
   */
  virtual AWindow& show() = 0;

  /**
   * @brief sets default values of window. Is called everytime when
   *        window is retrieved via WindowManager.
   */
  virtual AWindow& setDefaults() { return *this; }

  /**
   * @brief a dynamic cast wrapper, which is intended to use
   *        for example when making a function composition
   */
  template<typename T>
  T& downcast();

 virtual ~AWindow() {}

protected:
  AWindow() {}

};

typedef std::shared_ptr<AWindow> WindowPtr;

// === IMPLEMENTATION === //

template<typename T>
T& AWindow::downcast()
{
  T* t = dynamic_cast<T*>(this);
  assert(t != nullptr);

  return *t;
}


}}

#endif // WINDOW_H
