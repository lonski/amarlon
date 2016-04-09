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
  ALabel(const std::string& value, int x = 0, int y = 0);
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

  virtual int getWidth() const;
  virtual int getHeight() const;

  virtual void setWidth(int width);
  virtual void setHeight(int height);

private:  
  std::string _value;
  TCODColor   _color;
  TCODColor   _bgcolor;
  bool        _autosize;
  int         _width;
  int         _height;

};

typedef std::shared_ptr<ALabel> ALabelPtr;

}}

#endif // LABEL_H
