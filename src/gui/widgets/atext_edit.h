#ifndef ATEXTEDIT_H
#define ATEXTEDIT_H

#include <awidget.h>

namespace amarlon { namespace gui {

class ATextEdit : public AWidget
{
public:
  ATextEdit(int x, int y, int width = 10, const std::string& title = "");

  virtual void render(TCODConsole& console);

  virtual void handleKey(TCOD_key_t key);

  virtual int getWidth() const;
  virtual int getHeight() const;
  virtual void setWidth(int width);
  virtual void setHeight(int height);

  bool isActive() const;
  void activate();
  void deactivate();

  std::string getText() const;
  int getInt() const;

  TCODColor getBackgroundColor() const;
  void setBackgroundColor(const TCODColor &backgroundColor);

  TCODColor getTextColor() const;
  void setTextColor(const TCODColor &textColor);

  std::string getTitle() const;
  void setTitle(const std::string &title);

private:
  bool _active;
  std::string _text;
  unsigned _width;
  TCODColor _backgroundColor;
  TCODColor _textColor;
  std::string _title;
  int _totalAlign;


};

typedef std::shared_ptr<ATextEdit> ATextEditPtr;

}}

#endif // ATEXTEDIT_H
