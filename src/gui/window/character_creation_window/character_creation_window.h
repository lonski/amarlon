#ifndef CHARACTER_CREATION_WINDOW_H
#define CHARACTER_CREATION_WINDOW_H

#include <amultipanel_window.h>

namespace amarlon { namespace gui {

class ASubPanel;
typedef std::shared_ptr<ASubPanel> ASubPanelPtr;

class CharacterCreationWindow : public AMultiPanelWIndow
{
public:
  CharacterCreationWindow();
  virtual ~CharacterCreationWindow();

  static WindowId getId() { return AWindow::CHARACTER_CREATION; }

private:
  enum Panel
  {
    MAIN
  };

protected:
  void managePanel(int panel);
  bool exitWindow(TCOD_key_t key);

};

}}

#endif // CHARACTER_CREATION_WINDOW_H
