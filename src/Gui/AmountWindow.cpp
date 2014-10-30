#include "AmountWindow.h"
#include "Utils/glodef.h"
#include <iostream>

namespace amarlon { namespace gui {

AmountWindow::AmountWindow(int defAmount, std::string title)
  : _title(title)
  , _conWidth(21)
  , _conHeight(5)
  , _console(_conWidth, _conHeight)
  , _amount(defAmount)
  , _firstHit(true)
{
}

int AmountWindow::getAmount()
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

  return _amount;
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
  _console.printFrame(0, 0, _conWidth, _conHeight, true, TCOD_BKGND_DEFAULT,
                      _title.empty() ? NULL : _title.c_str() );
}

void AmountWindow::renderAmount()
{
  int middle = _conWidth / 2;
  int size = std::string(std::to_string(_amount)).size();
  int xpos = middle - size / 2;
  _console.print(xpos, 2, "%d", _amount);
}

void AmountWindow::blitConsole()
{
  int posX = gloScreenWidth  / 2 - _conWidth  / 2;
  int posY = gloScreenHeight / 2 - _conHeight / 2;

  TCODConsole::blit(&_console, 0, 0, _conWidth, _conHeight, TCODConsole::root, posX, posY);
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
