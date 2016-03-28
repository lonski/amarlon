#include "resizeable_text_window.h"
#include <utils/utils.h>
#include <alist.h>

namespace amarlon { namespace gui {

ResizeableTextWindow::ResizeableTextWindow()
  : _list(new AList)
{
  setDefaults();
}

AWindow& ResizeableTextWindow::setDefaults()
{
  removeAllWidgets();
  setFrame(true);
  _list.reset( new AList );
  addWidget(_list);

  TextWindow::setDefaults();

  return *this;
}

void ResizeableTextWindow::displayText()
{
  _list->clear();
  _list->setPosition(_margin, _margin -1);

  std::vector<std::string> lines = explode(_text, '#');

  size_t width = 1;
  std::for_each(lines.begin(), lines.end(), [&](const std::string& line)
  {
    _list->pushBack( ColoredString(line, TCODColor::white) );
    if ( line.size() > width ) width = line.size();
  });

  setHeight( _list->size() + _margin*2 );
  setWidth( width + _margin*2 );
  setPosition( _centerGameWindow ? AWidget::WINDOW_CENTER : AWidget::GAME_SCREEN_CENTER);
}

}}

