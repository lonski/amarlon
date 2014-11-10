#include "amount_window.h"
#include <engine.h>

namespace amarlon { namespace gui {

AmountWindow::AmountWindow()
  : _console(21, 5)
{
  setDefaults();
}

Window &AmountWindow::setDefaults()
{
  _title = "Enter amount";
  _amount = 0;
  _firstHit = true;

  return *this;
}

Window& AmountWindow::show()
{
  TCOD_key_t key;
  _firstHit = true;

  while(key.vk != TCODK_ENTER   && //accept
        key.vk != TCODK_KPENTER && //accept
        key.vk != TCODK_ESCAPE  && //cancel
        !TCODConsole::isWindowClosed())
  {
    render();
    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);
    handlePressedKey(key);
  }

  return *this;
}

int AmountWindow::getAmount()
{
  return _amount;
}

AmountWindow &AmountWindow::setMaxAmount(const int &amount)
{
  _amount = amount;
  return *this;
}

void AmountWindow::render()
{
  renderFrame();
  renderAmount();
  blitConsole();
}

void AmountWindow::renderFrame()
{
  _console.setDefaultForeground(TCODColor(200,180,50));
  _console.printFrame(0, 0, _console.getWidth(), _console.getHeight(), true, TCOD_BKGND_DEFAULT,
                      _title.empty() ? NULL : _title.c_str() );
}

void AmountWindow::renderAmount()
{
  int middle = _console.getWidth() / 2;
  int size = std::string(std::to_string(_amount)).size();
  int xpos = middle - size / 2;
  _console.print(xpos, 2, "%d", _amount);
}

void AmountWindow::blitConsole()
{
  int posX = Engine::consoleWidth  / 2 - _console.getWidth()  / 2;
  int posY = Engine::consoleHeight / 2 - _console.getHeight() / 2;

  TCODConsole::blit(&_console, 0, 0, _console.getWidth(), _console.getHeight(), TCODConsole::root, posX, posY);
  TCODConsole::flush();
}

void AmountWindow::handlePressedKey(const TCOD_key_t &key)
{
  std::string aStr( std::to_string(_amount) );

  if (key.vk == TCODK_BACKSPACE)
  {
    if (aStr.size() > 1)
      aStr.erase(aStr.end()-1, aStr.end());
    else if (!aStr.empty())
      aStr = "0";
  }
  else if ( aStr.size() < 10 )
  {
    int kpKey = (int)key.vk - (int)TCODK_KP0;
    int stKey = (int)key.vk - (int)TCODK_0;
    short digit = 0;

    if (kpKey > 0 && kpKey < 10)
    {
      digit = kpKey;
    }
    else if (stKey > 0 && stKey < 10)
    {
      digit = stKey;
    }

    if ( digit > 0 )
    {
      if (_firstHit)
        aStr = std::to_string(digit);
      else
        aStr += std::to_string(digit);
    }
  }

  _amount = std::stol(aStr);

}

}}
