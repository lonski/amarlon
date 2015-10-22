#ifndef CHARACTER_CREATION_WINDOW_H
#define CHARACTER_CREATION_WINDOW_H

#include <amultipanel_window.h>
#include <memory>

namespace amarlon { namespace gui {

class ASubPanel;
class RaceSelectionPanel;
typedef std::shared_ptr<ASubPanel> ASubPanelPtr;
typedef std::shared_ptr<RaceSelectionPanel> RaceSelectionPanelPtr;

class CharacterCreationWindow : public AMultiPanelWIndow
{
public:
  CharacterCreationWindow();
  virtual ~CharacterCreationWindow();

  static WindowId getId() { return AWindow::CHARACTER_CREATION; }
  virtual AWindow& show();

private:
  enum Panel
  {
    CURRENT_STEP
  };

  RaceSelectionPanelPtr _raceSelection;

protected:
  void managePanel(int panel);
  bool exitWindow(TCOD_key_t key);

};

}}

#endif // CHARACTER_CREATION_WINDOW_H
