#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <libtcod.hpp>
#include "widget.h"

namespace amarlon { namespace gui {

class Label : public Widget
{
public:
  Label();
  virtual ~Label() {}

  virtual void render(TCODConsole& console);

  std::string getValue() const;
  void setValue(const std::string &value);

  TCODColor getColor() const;
  void setColor(const TCODColor &color);

  TCOD_alignment_t getAligment() const;
  void setAligment(const TCOD_alignment_t &aligmnet);

  TCODColor getBgcolor() const;
  void setBgcolor(const TCODColor &bgColor);

private:
  std::string _value;
  TCODColor _color;
  TCODColor _bgcolor;
  TCOD_alignment_t _aligment;

};

typedef std::shared_ptr<Label> LabelPtr;

}}

#endif // LABEL_H
