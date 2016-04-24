#include "text_window.h"
#include <utils/utils.h>
#include <engine.h>

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
  TCODConsole* console = Engine::instance().getConsole();
  if ( console )
  {
    TCOD_key_t key;
    key.vk = TCODK_NONE;

    while( !exitCondition(key) &&
           !(TCODConsole::isWindowClosed()))
    {
      displayText();

      render(*console);
      Engine::instance().flush();

      TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);
      handleKey(key);
    }
  }

  return *this;
}

std::string TextWindow::getText() const
{
  return _text;
}

TextWindow& TextWindow::setText(const std::string &text)
{
  _text = text;
  return *this;
}

TextWindow& TextWindow::setWindowTitle(const std::string &title)
{
  setTitle(title);
  return *this;
}

TextWindow& TextWindow::setWindowFrameColor(const TCODColor &frameColor)
{
  setFrameColor(frameColor);
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
  int frame = isFramed() ? 1 : 0;
  _margin = margin + frame;
  return *this;
}

bool TextWindow::exitCondition(const TCOD_key_t &key)
{
  return key.vk == TCODK_ESCAPE  ||
         key.vk == TCODK_ENTER   ||
         key.vk == TCODK_KPENTER;
}

}}

