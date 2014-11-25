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

  AWidget(const int& w = 1, const int& h = 1);
  virtual ~AWidget() {}

  virtual void render(TCODConsole& console) = 0;

  virtual int getX() const;
  virtual int getY() const;

  virtual void setPosition(int x, int y);
  virtual void setPosition(PositionFlag position);

  virtual int getWidth() const;
  virtual int getHeight() const;

  virtual void setWidth(int width);
  virtual void setHeight(int height);

  virtual std::string getTag(const std::string& tagName);
  virtual void setTag(const std::string& tagName, const std::string& tagValue);

protected:
  std::map<std::string, std::string> _tags;
  int _x;
  int _y;
  int _width;
  int _height;

};

typedef std::shared_ptr<AWidget> AWidgetPtr;

}}

#endif // WIDGET_H
