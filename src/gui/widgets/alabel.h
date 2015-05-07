#ifndef ALABEL_H
#define ALABEL_H

#include <string>
#include <libtcod.hpp>
#include <awidget.h>

namespace amarlon { namespace gui {

class ALabel : public AWidget
{
public:
  ALabel();
  virtual ~ALabel() {}

  virtual void render(TCODConsole& console);

  std::string getValue   () const;
  TCODColor   getColor   () const;
  TCODColor   getBgcolor () const;
  bool        isAutosized() const;

  void setValue   (const std::string &value);
  void setColor   (const TCODColor   &color);
  void setBgcolor (const TCODColor   &bgColor);
  void setAutosize(bool  autosize);

private:
  std::string _value;
  TCODColor   _color;
  TCODColor   _bgcolor;
  bool        _autosize;

};

typedef std::shared_ptr<ALabel> ALabelPtr;

}}

#endif // LABEL_H
