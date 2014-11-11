#include "resizeable_text_window.h"
#include <utils/utils.h>

namespace amarlon { namespace gui {

ResizeableTextWindow::ResizeableTextWindow()
  : _list(new List)
{
  setDefaults();
}

Window& ResizeableTextWindow::setDefaults()
{
  _panel.reset( new Panel(1,1) );
  _list.reset( new List );
  _list->setFixedSize(false);
  _panel->addWidget(_list);

  TextWindow::setDefaults();

  return *this;
}

void ResizeableTextWindow::displayText()
{
  _list->clear();
  int margin = _panel->isFramed() ? 1 : 0;
  _list->setPosition(margin, 0);

  std::vector<std::string> lines = explode(_text, '\n');

  size_t width = 1;
  std::for_each(lines.begin(), lines.end(), [&](const std::string& line)
  {
    _list->push( ColoredString(line, TCODColor::white) );
    if ( line.size() > width ) width = line.size();
  });

  _panel->setHeight( _list->size() + margin*2 );
  _panel->setWidth( width + margin*2 );
  _panel->centerPosition(_centerGameWindow);
}

}}
