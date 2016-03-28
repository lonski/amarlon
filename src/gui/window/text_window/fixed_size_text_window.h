#ifndef ACTOR_INSPECTOR_H
#define ACTOR_INSPECTOR_H

#include <memory>
#include <text_window.h>
#include <alist.h>
#include <colored_string.h>
#include <text_formater.h>

namespace amarlon { namespace gui {

class FixedSizeTextWindow : public TextWindow
{
  friend class WindowManager;

public:
  virtual AWindow& setDefaults();
  static  WindowId getId() { return AWindow::FIXED_SIZE_TEXT; }

  virtual TextWindow& setText(std::string text);
  virtual void setWidth(int width);
  virtual void setHeight(int height);

protected:
  FixedSizeTextWindow(int w=50, int h=40);
  virtual void displayText();
  virtual void handleKey(TCOD_key_t&);

  TextFormater _formater;
  AListPtr _list;
  unsigned _lineCount;
  unsigned _lineWidth;
  unsigned _lineStart;

  std::vector<ColoredString> _allLines;

};

}}


#endif // ACTOR_INSPECTOR_H
