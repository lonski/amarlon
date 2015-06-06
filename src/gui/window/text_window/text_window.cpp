#include "text_window.h"
#include <utils/utils.h>

namespace amarlon { namespace gui {

TextWindow::TextWindow()
{
  setDefaults();
}

AWindow& TextWindow::setDefaults()
{
  _text = "";
  _centerGameWindow = true;
  setMargin(0);

  return *this;
}

AWindow& TextWindow::show()
{
  _visible = true;
  TCOD_key_t key;
  key.vk = TCODK_NONE;

  while( !(key.vk == TCODK_ESCAPE  ) &&
         !(key.vk == TCODK_ENTER   ) &&
         !(key.vk == TCODK_KPENTER ) &&
         !(TCODConsole::isWindowClosed()))
  {  
    displayText();

    _panel->render(*TCODConsole::root);
    TCODConsole::root->flush();

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);
    handleKey(key);
  }

  _visible = false;
  return *this;
}

std::string TextWindow::getWindowText() const
{
  return _text;
}

TextWindow& TextWindow::setWindowText(const std::string &text)
{
  _text = text;
  return *this;
}

TextWindow& TextWindow::setWindowTitle(const std::string &title)
{
  _panel->setTitle(title);
  return *this;
}

TextWindow& TextWindow::setWindowFrameColor(const TCODColor &frameColor)
{
  _panel->setFrameColor(frameColor);
  return *this;
}

TextWindow &TextWindow::setCenterGameScreen()
{
  _centerGameWindow = false;
  return *this;
}

TextWindow &TextWindow::setCenterGameWindow()
{
  _centerGameWindow = true;
  return *this;
}

TextWindow &TextWindow::setMargin(int margin)
{
  int frame = _panel && _panel->isFramed() ? 1 : 0;
  _margin = margin + frame;
  return *this;
}

}}
