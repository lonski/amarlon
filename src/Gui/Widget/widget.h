#ifndef WIDGET_H
#define WIDGET_H

#include <memory>
#include <map>
#include <string>

class TCODConsole;

namespace amarlon { namespace gui {

class Widget
{
public:
  Widget(const int& w = 1, const int& h = 1);
  virtual ~Widget() {}

  virtual void render(TCODConsole& console) = 0;

  virtual int getX() const;
  virtual int getY() const;

  virtual void setPosition(int x, int y);
  virtual void centerPosition();

  virtual std::string getTag(const std::string& tagName);
  virtual void setTag(const std::string& tagName, const std::string& tagValue);

  virtual int getWidth() const;
  virtual void setWidth(int width);

  int getHeight() const;
  void setHeight(int height);

protected:
  std::map<std::string, std::string> _tags;
  int _x;
  int _y;
  int _width;
  int _height;

};

typedef std::shared_ptr<Widget> WidgetPtr;

}}

#endif // WIDGET_H
