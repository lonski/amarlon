#ifndef TALK_WINDOW_H
#define TALK_WINDOW_H

#include <resizeable_text_window.h>
#include <dialog.h>

namespace amarlon {

namespace gui {

class AMenu;
typedef std::shared_ptr<AMenu> AMenuPtr;

class TalkWindow : public ResizeableTextWindow
{
public:
  TalkWindow();
  virtual ~TalkWindow();
  static WindowId getId() { return AWindow::TALK_WINDOW; }
  virtual AWindow& setDefaults();

  virtual AWindow& show();
  virtual TalkWindow& setDialog(const Dialog& d);
  virtual Choice getChoice();

protected:
  virtual void displayText();
  virtual void handleKey(TCOD_key_t&);
  virtual bool exitCondition(const TCOD_key_t &key);

private:
  AMenuPtr _choices;
  Dialog _dialog;

};

}}

#endif // TALK_WINDOW_H
