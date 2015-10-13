#include "message_box.h"
#include <resizeable_text_window.h>
#include <amenu.h>
#include <alabel_menu_item.h>
#include <engine.h>

namespace amarlon { namespace gui {

void msgBox(const std::__cxx11::string &text, MsgType type)
{
  TCODColor color;
  switch (type)
  {
    case MsgType::Error: color = TCODColor::red; break;
    case MsgType::Warning: color = TCODColor::yellow; break;
    case MsgType::Info: color = TCODColor::darkerOrange; break;
  }

  Engine::instance().getWindowManager()
                    .getWindow<ResizeableTextWindow>()
                    .setWindowFrameColor(color)
                    .setWindowText(text)
                    .setCenterGameScreen()
                    .setMargin(1)
      .show();
}

QuestionDialog::Response questionBox(const std::__cxx11::string &text, MsgType type)
{
  TCODColor color;
  switch (type)
  {
    case MsgType::Error: color = TCODColor::red; break;
    case MsgType::Warning: color = TCODColor::yellow; break;
    case MsgType::Info: color = TCODColor::darkerOrange; break;
  }

  return Engine::instance().getWindowManager()
                           .getWindow<QuestionDialog>()
                           .setWindowFrameColor(color)
                           .setWindowText(text)
                           .setCenterGameScreen()
                           .setMargin(1)
                           .show()
                           .downcast<QuestionDialog>()
                           .getResponse();
}


}}
