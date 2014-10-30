#ifndef TEXT_WINDOW_H
#define TEXT_WINDOW_H

#include <string>
#include <Gui/Widget/panel.h>

namespace amarlon { namespace gui {

class TextWindow : public Panel
{
public:
  TextWindow(const std::string& text = "", const int& w = 1, const int& h = 1);

  std::string getText() const;
  void setText(const std::string &text);

  void show(TCODConsole &console);

private:
  std::string _text;
};

  }}

#endif // TEXT_WINDOW_H
