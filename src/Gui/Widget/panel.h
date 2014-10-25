#ifndef PANEL_H
#define PANEL_H

#include <vector>
#include "widget.h"
#include "libtcod.hpp"

namespace amarlon { namespace gui {

class Panel : public Widget
{
public:
  Panel(const int& w, const int& h);
  virtual ~Panel() {}

  virtual void render(TCODConsole& console);

  void addWidget(Widget* widget);
  void addWidget(WidgetPtr widget);

  int getWidth() const;
  void setWidth(int width);

  int getHeight() const;
  void setHeight(int height);

private:
  int _width;
  int _height;
  bool _frame;
  TCODColor _frameColor;

  std::vector<WidgetPtr> _widgets;
  std::shared_ptr<TCODConsole> _panel;

};

}}

#endif // PANEL_H
