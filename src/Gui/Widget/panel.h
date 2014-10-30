#ifndef PANEL_H
#define PANEL_H

#include <string>
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
  void removeAllWidgets();

  virtual void setWidth(int width);
  virtual void setHeight(int height);

  std::string setTitle() const;
  void setTitle(const std::string &setTitle);

  TCODColor getTitleColor() const;
  void setTitleColor(const TCODColor &getTitleColor);

  bool isFramed() const;
  void setFrame(bool frame);

  TCODColor getFrameColor() const;
  void setFrameColor(const TCODColor &getFrameColor);

private:
  bool _frame;
  TCODColor _frameColor;
  std::string _title;
  TCODColor _titleColor;

  std::vector<WidgetPtr> _widgets;
  std::shared_ptr<TCODConsole> _panel;

};

typedef std::shared_ptr<Panel> PanelPtr;

}}

#endif // PANEL_H
