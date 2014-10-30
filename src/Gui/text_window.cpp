#include "text_window.h"
#include <Utils/Utils.h>
#include <Gui/Widget/label.h>

namespace amarlon { namespace gui {

TextWindow::TextWindow(const std::string &text, const int &w, const int &h)
  : Panel(w, h)
  , _text(text)
{  
}
std::string TextWindow::getText() const
{
  return _text;
}

void TextWindow::setText(const std::string &text)
{
  _text = text;
}

void TextWindow::show(TCODConsole& console)
{
  std::vector<std::string> lines = explode(_text, '\n');
  int margin = isFramed() ? 2 : 0;
  int row = margin;

  std::for_each(lines.begin(), lines.end(), [&](const std::string& line)
  {
    if ( (int)line.size() > getWidth() - 2*margin)
    {
      setWidth( line.size() + 2*margin );
    }
    LabelPtr label( new Label );
    label->setPosition( margin, row++ );
    label->setValue( line );
    addWidget( label );
  });

  if ( row > getHeight() - 2*margin)
  {
    setHeight( row + margin );
  }

  centerPosition();

  TCOD_key_t key;

  while( !(key.vk == TCODK_ESCAPE  ) &&
         !(key.vk == TCODK_ENTER   ) &&
         !(key.vk == TCODK_KPENTER ) &&
         !(TCODConsole::isWindowClosed()))
  {
    render(console);
    console.flush();

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);
  }

}

}}
