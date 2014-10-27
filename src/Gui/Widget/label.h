#ifndef LABEL_H
#define LABEL_H

#include "widget.h"
#include "libtcod.hpp"
#include <string>

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

  TCOD_alignment_t getAligment() const;
  void setAligment(const TCOD_alignment_t &getAligment);

  TCODColor getBgcolor() const;
  void setBgcolor(const TCODColor &getBgcolor);

private:
  std::string _value;
  TCODColor _color;
  TCODColor _bgcolor;
  TCOD_alignment_t _aligment;

};

typedef std::shared_ptr<Label> LabelPtr;

}}

#endif // LABEL_H
