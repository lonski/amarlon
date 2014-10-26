#ifndef BAR_H
#define BAR_H

#include <string>
#include "widget.h"
#include "libtcod.hpp"

namespace amarlon { namespace gui {

class Bar : public Widget
{
public:
  Bar();
  virtual ~Bar() {}

  virtual void render(TCODConsole& console);

  int getWidth() const;
  void setWidth(int getWidth);

  std::string getName() const;
  void setName(const std::string &getName);

  float getValue() const;
  void setValue(float getValue);

  float getMaxValue() const;
  void setMaxValue(float getMaxValue);

  TCODColor getBgColor() const;
  void setBgColor(const TCODColor &getBgColor);

  TCODColor getFgColor() const;
  void setFgColor(const TCODColor &getFgColor);

  bool displayValues() const;
  void setDisplayValues(bool displayValues);

  TCODColor getTextColor() const;
  void setTextColor(const TCODColor &getTextColor);

private:
  int _width;
  std::string _name;
  float _value;
  float _maxValue;
  TCODColor _bgColor;
  TCODColor _fgColor;
  bool _displayValues;
  TCODColor _textColor;

};

}}

#endif // BAR_H
