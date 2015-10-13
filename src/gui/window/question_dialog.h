#ifndef QUESTION_DIALOG_H
#define QUESTION_DIALOG_H

#include <memory>
#include <resizeable_text_window.h>

namespace amarlon { namespace gui {

class AMenu;
typedef std::shared_ptr<AMenu> AMenuPtr;

class QuestionDialog : public ResizeableTextWindow
{
public:
  enum Response
  {
    YES,
    NO
  };

  static WindowId getId() { return AWindow::QUESTION; }

  QuestionDialog();
  virtual Response getResponse();
  virtual AWindow& setDefaults();

protected:
  virtual void handleKey(TCOD_key_t&key);
  virtual void displayText();

private:
  AMenuPtr _menu;

};

}}

#endif // QUESTION_DIALOG_H
