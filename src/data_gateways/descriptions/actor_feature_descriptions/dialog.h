#ifndef DIALOG
#define DIALOG

#include <string>
#include <vector>

namespace amarlon {

struct Choice
{
  Choice(int id = 0, int jump = 0)
    : id(id)
    , jump(jump)
  {}

  int id;
  int jump;
  std::string text;

  operator bool() const
  {
    return id != 0;
  }

  bool operator==(const Choice& rhs) const
  {
    return rhs.id == id &&
           rhs.text == text &&
           rhs.jump == jump;
  }
};

struct Dialog
{
  Dialog(int id = 0)
    : id(id)
  {}

  int id;
  std::string text;
  std::vector<Choice> choices;

  operator bool() const
  {
    return id != 0;
  }

  bool operator==(const Dialog& rhs) const
  {
    return id == rhs.id
           && text == rhs.text
           && choices.size() == rhs.choices.size()
           && std::equal( choices.begin(), choices.end(), rhs.choices.begin());
  }
};

}

#endif // DIALOG

