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
  _panel.reset( new APanel );
  _panel->setFrame(true);
  _list.reset( new AList );
  _panel->addWidget(_list);

  TextWindow::setDefaults();

  return *this;
}

void ResizeableTextWindow::displayText()
{
  _list->clear();
  _list->setPosition(_margin, _margin -1);

  std::vector<std::string> lines = explode(_text, '\n');

  size_t width = 1;
  std::for_each(lines.begin(), lines.end(), [&](const std::string& line)
  {
    _list->pushBack( ColoredString(line, TCODColor::white) );
    if ( line.size() > width ) width = line.size();
  });

  _panel->setHeight( _list->size() + _margin*2 );
  _panel->setWidth( width + _margin*2 );
  _panel->setPosition( _centerGameWindow ? AWidget::WINDOW_CENTER : AWidget::GAME_SCREEN_CENTER);
}

}}
