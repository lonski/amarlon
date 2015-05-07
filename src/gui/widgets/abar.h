#ifndef ABAR_H
#define ABAR_H

#include <string>
#include <awidget.h>
#include <libtcod.hpp>

namespace amarlon { namespace gui {

class ABar : public AWidget
{
public:
  ABar();
  virtual ~ABar() {}

  virtual void render(TCODConsole& console);

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
  std::string _name;
  float _value;
  float _maxValue;
  TCODColor _bgColor;
  TCODColor _fgColor;
  bool _displayValues;
  TCODColor _textColor;

};

typedef std::shared_ptr<ABar> ABarPtr;

}}

#endif // BAR_H
