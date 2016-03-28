#include "fixed_size_text_window.h"

namespace amarlon { namespace gui {

const int MARGIN = 2;

FixedSizeTextWindow::FixedSizeTextWindow(int w, int h)
  : _lineCount(0)
  , _lineWidth(0)
  , _lineStart(0)
{
  setWidth(w);
  setHeight(h);
  setDefaults();
}

AWindow& FixedSizeTextWindow::setDefaults()
{
  removeAllWidgets();

  _lineCount = getHeight() - 2*MARGIN;
  _lineWidth = getWidth() - 2*MARGIN;
  _lineStart = 0;

  _list.reset( new AList );  
  _list->setAutosize(false);
  _list->setWidth(getWidth() - 2*MARGIN);
  _list->setHeight(getHeight() - 2*MARGIN);
  _list->setPosition(MARGIN, MARGIN / 2);

  addWidget(_list);
  setPosition(PositionFlag::WINDOW_CENTER);

  TextWindow::setDefaults();

  return *this;
}

TextWindow& FixedSizeTextWindow::setText(std::string text)
{
  _allLines = _formater.format(text, _lineWidth);
  return *this;
}

void FixedSizeTextWindow::setWidth(int width)
{
  TextWindow::setWidth(width);
  if ( _list ) _list->setWidth(getWidth() - 2*MARGIN);
  _lineWidth = getWidth() - 2*MARGIN;
}

void FixedSizeTextWindow::setHeight(int height)
{
  TextWindow::setHeight(height);
  if ( _list ) _list->setHeight(getHeight() - 2*MARGIN);
  _lineCount = getHeight() - 2*MARGIN;
}

void FixedSizeTextWindow::displayText()
{
  _list->clear();
  unsigned l = _lineStart;
  while ( l < _allLines.size() && l < _lineCount + _lineStart )
  {
    _list->pushBack( _allLines[l] );
    ++l;
  }
}

void FixedSizeTextWindow::handleKey(TCOD_key_t& k)
{
  switch( k.vk )
  {
    case TCODK_UP: if (_lineStart > 0) --_lineStart; break;
    case TCODK_DOWN: if (_lineStart < _allLines.size() - _lineCount ) ++_lineStart; break;
    default:;
  }
}

}}

