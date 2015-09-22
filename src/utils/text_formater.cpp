#include "text_formater.h"
#include <utils.h>

namespace amarlon {

TextFormater::TextFormater()
  : _lineWidth(0)
{
}

TextFormater::~TextFormater()
{
}

std::vector<ColoredString> TextFormater::format(std::string text, unsigned lineWidth)
{
  _lineWidth = lineWidth;
  _lines.clear();

  for( std::string line : explode(text,'\n') )
  {
    TCODColor color = TCODColor::white;
    if ( !line.empty() && line.front() == '{' )
    {
      std::vector<std::string> coloredLine = explode( line.substr(1, line.size()) , '}');
      if ( coloredLine.size() == 2 )
      {
        pushTextAsLines(coloredLine[1], strToColor(coloredLine[0]));
      }
    }
    else
    {
      pushTextAsLines(line, color);
    }
  }

  return _lines;
}

void TextFormater::pushTextAsLines(std::string text, TCODColor color)
{
  std::string line;
  for ( std::string word : explode(text, ' ') )
  {    
    if ( line.size() + word.size() < _lineWidth )
    {
      line += word + " ";
    }
    else
    {      
      _lines.push_back( ColoredString(line, color) );
      line = word + " ";
    }
  }
  _lines.push_back( ColoredString(line, color) );
}

}

