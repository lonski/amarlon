#ifndef TEXT_WINDOW_H
#define TEXT_WINDOW_H

#include <string>
#include <apanel.h>
#include <awindow.h>

namespace amarlon { namespace gui {

class TextWindow : public AWindow
{
public:
  TextWindow();

  virtual AWindow& show();
  virtual AWindow& setDefaults();
  static WindowId getId() { return AWindow::TEXT; }

  std::string getWindowText() const;
  TextWindow& setWindowText(const std::string &text);
  TextWindow& setWindowTitle(const std::string &title);
  TextWindow& setWindowFrameColor(const TCODColor &getFrameColor);
  TextWindow& setCenterGameScreen();
  TextWindow& setCenterGameWindow();
  TextWindow& setMargin(int margin);

protected:
  std::string _text;
  bool _centerGameWindow;
  int _margin;

  virtual void displayText() = 0;
  virtual void handleKey(TCOD_key_t& key) = 0;

};

}}

#endif // TEXT_WINDOW_H
