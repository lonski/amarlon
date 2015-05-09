#ifndef AWIDGET_H
#define AWIDGET_H

#include <memory>
#include <map>
#include <string>

class TCODConsole;

namespace amarlon { namespace gui {

class AWidget
{
public:
  enum PositionFlag
  {
    WINDOW_CENTER,
    GAME_SCREEN_CENTER
  };

  AWidget();
  virtual ~AWidget() {}

  virtual void render(TCODConsole& console) = 0;

  virtual int getX() const;
  virtual int getY() const;

  virtual void setPosition(int x, int y);
  virtual void setPosition(PositionFlag position);

  virtual int getWidth() const = 0;
  virtual int getHeight() const = 0;

  /* Some widgets could be autosized: e.g. AList, ALabel, AMenu
   * At the momment if autosize of those widgets is turned off
   * then setting width or height will not affect rendering the widget itself.
   * The widget will render always its whole content. It can be used only by
   * parent widget to aquire and set the coordinated where other widgets should be
   * positioned (e.g. getY() + getWidth() )
   * TODO: think if it is needed to implement such a feature
   */
  virtual void setWidth(int width) = 0;
  virtual void setHeight(int height) = 0;

  virtual std::string getTag(const std::string& tagName);
  virtual void setTag(const std::string& tagName, const std::string& tagValue);

private:
  std::map<std::string, std::string> _tags;
  int _x;
  int _y;  

};

typedef std::shared_ptr<AWidget> AWidgetPtr;
typedef std::unique_ptr<AWidget> AWidgetUPtr;

}}

#endif // WIDGET_H
