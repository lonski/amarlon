#ifndef CHARACTER_CREATION_WINDOW_H
#define CHARACTER_CREATION_WINDOW_H

#include <amultipanel_window.h>
#include <memory>

namespace amarlon { namespace gui {

class ASubPanel;
class RaceSelectionPanel;
class ClassSelectionPanel;
typedef std::shared_ptr<ASubPanel> ASubPanelPtr;
typedef std::shared_ptr<RaceSelectionPanel> RaceSelectionPanelPtr;
typedef std::shared_ptr<ClassSelectionPanel> ClassSelectionPanelPtr;

class CharacterCreationWindow : public AWindow
{
public:
  CharacterCreationWindow();
  virtual ~CharacterCreationWindow();

  static WindowId getId() { return AWindow::CHARACTER_CREATION; }
  virtual AWindow& show();
  virtual AWindow& setDefaults();


  RaceSelectionPanelPtr getRaceSelectionPanel() const;
  ClassSelectionPanelPtr getClassSelectionPanel() const;

private:
  enum Panel
  {
    RACE_SELECTION,
    CLASS_SELECTION
  };

  std::map<int, ASubPanelPtr> _panels;
  int _activePanel;
  bool _enterGame;

  RaceSelectionPanelPtr _raceSelection;
  ClassSelectionPanelPtr _classSelection;

  void handleKey(TCOD_key_t key);
  void nextStep();
  void showActivePanel();

};

}}

#endif // CHARACTER_CREATION_WINDOW_H
