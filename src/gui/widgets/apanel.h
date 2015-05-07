#ifndef APANEL_H
#define APANEL_H

#include <vector>
#include <awidget.h>
#include <libtcod.hpp>

namespace amarlon { namespace gui {

class APanel : public AWidget
{
public:
  APanel();
  APanel(int w, int h);
  ~APanel();
  virtual void render(TCODConsole& console);
  void addWidget(AWidget* widget);
  void addWidget(const AWidgetPtr& widget);

  std::string setTitle() const;
  void setTitle(const std::string &setTitle);

  TCODColor getTitleColor() const;
  void setTitleColor(const TCODColor &getTitleColor);

  bool isFramed() const;
  void setFrame(bool frame);

  TCODColor getFrameColor() const;
  void setFrameColor(const TCODColor &getFrameColor);

  virtual void setWidth(int width);
  virtual void setHeight(int height);

  void removeAllWidgets();

private:
  bool _frame;
  TCODColor _frameColor;
  std::string _title;
  TCODColor _titleColor;

  std::vector< AWidgetPtr > _widgets;
  std::unique_ptr<TCODConsole> _panelConsole;

  void renderFrame();
  void renderWidgets();
  void initPanelConsole();

};

typedef std::unique_ptr<APanel> APanelUPtr;
typedef std::shared_ptr<APanel> APanelPtr;

}}

#endif // APANEL_H
