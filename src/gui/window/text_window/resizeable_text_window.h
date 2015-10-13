#ifndef RESIZEABLE_TEXT_WINDOW_H
#define RESIZEABLE_TEXT_WINDOW_H

#include <text_window.h>
#include <alist.h>

namespace amarlon { namespace gui {

class ResizeableTextWindow : public TextWindow
{
  friend class WindowManager;

public:
  static WindowId getId() { return AWindow::RESIZABLE_TEXT; }
  virtual AWindow& setDefaults();

protected:
  ResizeableTextWindow();
  virtual void displayText();
  virtual void handleKey(TCOD_key_t&) {}

private:
  AListPtr _list;

};

}}

#endif // RESIZEABLE_TEXT_WINDOW_H
