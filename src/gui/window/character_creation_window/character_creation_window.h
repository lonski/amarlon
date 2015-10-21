#ifndef CHARACTER_CREATION_WINDOW_H
#define CHARACTER_CREATION_WINDOW_H

#include <awindow.h>

namespace amarlon { namespace gui {

class CharacterCreationWindow : public AWindow
{
public:
  CharacterCreationWindow();
  virtual ~CharacterCreationWindow();

  static WindowId getId() { return AWindow::CHARACTER_CREATION; }

  virtual AWindow& show();

};

}}

#endif // CHARACTER_CREATION_WINDOW_H
