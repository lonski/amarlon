#include "atext_edit.h"
#include <utils.h>

namespace amarlon { namespace gui {

ATextEdit::ATextEdit(int x, int y, int width, const std::string &title)
    : _active(false)
    , _width(width)
    , _backgroundColor(TCODColor::darkestGrey)
    , _textColor(TCODColor::white)
    , _title(title)
{
  setPosition(x,y);
}

void ATextEdit::render(TCODConsole &console)
{
  console.setDefaultForeground(_textColor);

  std::string buf = _text;
  if ( _active ) buf += "|";
  while ( buf.size() < (_width - _title.size()) ) buf += " ";

  if ( !_title.empty() )
    console.printEx(getX(), getY(),
                    TCOD_BKGND_DEFAULT, TCOD_LEFT,
                    "%s", _title.c_str() );

  console.setDefaultBackground( _active ? TCODColor::lerp(_backgroundColor, TCODColor::yellow, 0.1)
                                        : _backgroundColor);

  console.printEx(getX() + (_title.empty()?0:_title.size()+1), getY(),
                  TCOD_BKGND_SET, TCOD_LEFT,
                  "%s", buf.c_str() );
}

void ATextEdit::handleKey(TCOD_key_t key)
{
  if (key.vk == TCODK_BACKSPACE)
  {
    if (!_text.empty()) _text.erase(_text.end()-1, _text.end());
  }
  else if ( _text.size() < (_width - _title.size()) )
  {
    if ( key.c > 0 ) _text.push_back( key.c );
  }
  trim(_text);
}

int ATextEdit::getWidth() const
{
  return _width + _title.size();
}

int ATextEdit::getHeight() const
{
  return 1;
}

void ATextEdit::setWidth(int width)
{
  _width = std::max(1, width);
}

void ATextEdit::setHeight(int /*height*/)
{
  //nada
}

bool ATextEdit::isActive() const
{
  return _active;
}

void ATextEdit::activate()
{
  _active = true;
}

void ATextEdit::deactivate()
{
  _active = false;
}

std::string ATextEdit::getText() const
{
  return _text;
}

int ATextEdit::getInt() const
{
  return std::stoi(_text);
}

TCODColor ATextEdit::getBackgroundColor() const
{
  return _backgroundColor;
}

void ATextEdit::setBackgroundColor(const TCODColor &backgroundColor)
{
  _backgroundColor = backgroundColor;
}

TCODColor ATextEdit::getTextColor() const
{
  return _textColor;
}

void ATextEdit::setTextColor(const TCODColor &textColor)
{
  _textColor = textColor;
}

std::string ATextEdit::getTitle() const
{
  return _title;
}

void ATextEdit::setTitle(const std::string &title)
{
  _title = title;
}

}}
