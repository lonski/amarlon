#ifndef RESIZEABLE_TEXT_WINDOW_H
#define RESIZEABLE_TEXT_WINDOW_H

#include <gui/window/text_window/text_window.h>
#include <gui/widget/list.h>

namespace amarlon { namespace gui {

class ResizeableTextWindow : public TextWindow
{
  friend class WindowManager;
  ResizeableTextWindow();

public:
  virtual Window& setDefaults();

protected:
  virtual void displayText();
  virtual void handleKey(TCOD_key_t&) {}

private:
  ListPtr _list;

};

}}

#endif // RESIZEABLE_TEXT_WINDOW_H
