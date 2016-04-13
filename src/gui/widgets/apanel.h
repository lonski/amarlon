#ifndef APANEL_H
#define APANEL_H

#include <vector>
#include <awidget.h>
#include <libtcod.hpp>

namespace amarlon { namespace gui {

class APanel : public AWidget
{
public:  
  APanel(int w = 1, int h = 1);
  ~APanel();
  virtual void render(TCODConsole& console);
  void addWidget(AWidget* widget);
  bool removeWidget(AWidget* widget);
  void addWidget(const AWidgetPtr& widget);

  virtual void handleInput(TCOD_mouse_t /*mouse*/, TCOD_key_t /*key*/) {}

  std::string getTitle() const;
  void setTitle(const std::string &title);

  TCODColor getTitleColor() const;
  void setTitleColor(const TCODColor &titleColor);

  bool isFramed() const;
  void setFrame(bool frame);

  TCODColor getFrameColor() const;
  void setFrameColor(const TCODColor &frameColor);

  virtual void setWidth(int width);
  virtual void setHeight(int height);

  virtual int getWidth() const;
  virtual int getHeight() const;

  virtual void removeAllWidgets();

  virtual std::vector< AWidgetPtr > getWidgets();

  bool isActive() const;
  void setActive(bool active);

private:
  bool _frame;
  TCODColor _frameColor;
  std::string _title;
  TCODColor _titleColor;
  bool _active;

  std::vector< AWidgetPtr > _widgets;

protected:
  std::unique_ptr<TCODConsole> _panelConsole;

  void renderFrame();
  void renderWidgets();
  void initPanelConsole();

};

typedef std::unique_ptr<APanel> APanelUPtr;
typedef std::shared_ptr<APanel> APanelPtr;

}}

#endif // APANEL_H
