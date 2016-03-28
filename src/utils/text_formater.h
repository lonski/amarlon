#ifndef TEXT_FORMATER_H
#define TEXT_FORMATER_H

#include <vector>
#include <colored_string.h>
#include <libtcod.hpp>

namespace amarlon {

class TextFormater
{
public:
  TextFormater();
  ~TextFormater();

  std::vector<ColoredString> format(std::string text, unsigned lineWidth = 100);

private:
  std::vector<ColoredString> _lines;
  unsigned _lineWidth;

  void pushTextAsLines(std::string text, TCODColor color);

};


}

#endif // TEXT_FORMATER_H
