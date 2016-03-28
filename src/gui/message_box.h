#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <string>
#include <libtcod.hpp>
#include <question_dialog.h>

namespace amarlon { namespace gui {

enum class MsgType
{
  Error,
  Warning,
  Info
};

void msgBox(const std::string& text, MsgType type = MsgType::Info);
QuestionDialog::Response questionBox(const std::string& text, MsgType type = MsgType::Info);

}}

#endif // MESSAGEBOX_H
