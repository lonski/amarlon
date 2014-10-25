#ifndef LABEL_H
#define LABEL_H

#include "widget.h"
#include "libtcod.hpp"

namespace amarlon { namespace gui {

class Label : public Widget
{
public:
  Label();
  virtual ~Label() {}

  virtual void render(TCODConsole& console);

  std::string getValue() const;
  void setValue(const std::string &getValue);

  TCODColor getColor() const;
  void setColor(const TCODColor &getColor);

private:
  std::string _value;
  TCODColor _color;

};

}}

#endif // LABEL_H
