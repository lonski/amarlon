#ifndef TEXT_WINDOW_H
#define TEXT_WINDOW_H

#include <string>
#include <gui/widget/panel.h>
#include <gui/window/window.h>

namespace amarlon { namespace gui {

class TextWindow : public Window
{
  friend class WindowManager;
  TextWindow();

public:
  virtual Window& show();
  virtual Window& setDefaults();
  static WindowId getId() { return Window::TEXT; }

  std::string getWindowText() const;
  TextWindow& setWindowText(const std::string &text);
  TextWindow& setWindowTitle(const std::string &title);
  TextWindow& setWindowFrameColor(const TCODColor &getFrameColor);
  TextWindow& setCenterGameScreen();
  TextWindow& setCenterGameWindow();

private:
  PanelPtr _panel;
  std::string _text;
  bool _centerGameWindow;

  void displayText();

};

}}

#endif // TEXT_WINDOW_H
