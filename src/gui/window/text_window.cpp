#include "text_window.h"
#include <utils/utils.h>
#include <gui/widget/label.h>

namespace amarlon { namespace gui {

TextWindow::TextWindow()
{  
  _panel.reset( new Panel(1, 1) );
  setDefaults();
}

Window& TextWindow::setDefaults()
{
  _text = "";
  _centerGameWindow = true;
  _panel.reset( new Panel(1,1) );

  return *this;
}

Window& TextWindow::show()
{
  displayText();

  TCOD_key_t key;

  while( !(key.vk == TCODK_ESCAPE  ) &&
         !(key.vk == TCODK_ENTER   ) &&
         !(key.vk == TCODK_KPENTER ) &&
         !(TCODConsole::isWindowClosed()))
  {
    _panel->render(*TCODConsole::root);
    TCODConsole::root->flush();

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);
  }

  return *this;
}

std::string TextWindow::getWindowText() const
{
  return _text;
}

TextWindow &TextWindow::setWindowText(const std::string &text)
{
  _text = text;
  return *this;
}

TextWindow &TextWindow::setWindowTitle(const std::string &title)
{
  _panel->setTitle(title);
  return *this;
}

TextWindow &TextWindow::setWindowFrameColor(const TCODColor &frameColor)
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
  _centerGameWindow = false;
  return *this;
}

void TextWindow::displayText()
{
  std::vector<std::string> lines = explode(_text, '\n');
  int margin = _panel->isFramed() ? 2 : 0;
  int row = margin;

  std::for_each(lines.begin(), lines.end(), [&](const std::string& line)
  {
    if ( (int)line.size() > _panel->getWidth() - 2*margin)
    {
      _panel->setWidth( line.size() + 2*margin );
    }
    LabelPtr label( new Label );
    label->setPosition( margin, row++ );
    label->setValue( line );
    _panel->addWidget( label );
  });

  if ( row > _panel->getHeight() - 2*margin)
  {
    _panel->setHeight( row + margin );
  }

  _panel->centerPosition(_centerGameWindow);
}

}}
