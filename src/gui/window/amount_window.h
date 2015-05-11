#ifndef AMOUNTWINDOW_H
#define AMOUNTWINDOW_H

#include <string>
#include <libtcod.hpp>
#include <awindow.h>

namespace amarlon { namespace gui {

class AmountWindow : public AWindow
{
  friend class WindowManager;
  AmountWindow();

public:
  virtual AWindow& show();
  virtual AWindow& setDefaults();
  static  WindowId getId() { return AWindow::AMOUNT; }

  /**
   * @brief sets maximum amount that can be picked, also it will be
   *        displayed as a default amount at window show
   */
  AmountWindow& setMaxAmount(const int& amount);

  /**
   * @return amount set in window. It can be used after calling show()
   *         method to collect result of executing window.
   */
  int getAmount();

private:
  std::string _title;
  TCODConsole _console;

  int _amount;
  bool _firstHit;

  void render();
  void renderFrame();
  void renderAmount();
  void blitConsole();
  void handlePressedKey(const TCOD_key_t& key);

};

}}
#endif // AMOUNTWINDOW_H
