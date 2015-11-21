#ifndef INPUT_DIALOG_H
#define INPUT_DIALOG_H

#include <string>
#include <libtcod.hpp>
#include <awindow.h>

namespace amarlon { namespace gui {

class InputDialog : public AWindow
{
  friend class WindowManager;
  InputDialog();

public:
  virtual AWindow& show();
  virtual AWindow& setDefaults();
  static  WindowId getId() { return AWindow::INPUT; }

  std::string getText() const;
  void setText(const std::string& text);

  virtual void render(TCODConsole&);

  int getMaxSize() const;
  void setMaxSize(int maxSize);

  virtual void setWidth(int width);
  virtual void setHeight(int height);

private:
  std::shared_ptr<TCODConsole> _console;

  std::string _input;
  unsigned _maxSize;

  void renderFrame();
  void renderInput();
  void blitConsole();
  void handlePressedKey(const TCOD_key_t& key);

};

}}
#endif // INPUT_DIALOG_H
