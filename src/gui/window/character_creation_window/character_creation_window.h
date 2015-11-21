#ifndef CHARACTER_CREATION_WINDOW_H
#define CHARACTER_CREATION_WINDOW_H

#include <amultipanel_window.h>
#include <actor_descriptions.h>
#include <memory>

namespace amarlon { namespace gui {

class ASubPanel;
class RaceSelectionPanel;
class ClassSelectionPanel;
class AbilityScoresSelectionPanel;
class ThiefSkillsSelectionPanel;
typedef std::shared_ptr<ASubPanel> ASubPanelPtr;
typedef std::shared_ptr<ThiefSkillsSelectionPanel> ThiefSkillsSelectionPanelPtr;
typedef std::shared_ptr<AbilityScoresSelectionPanel> AbilityScoresSelectionPanelPtr;
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

  void nextStep();
  ActorDescriptionPtr getPlayerDsc() const;
  PlayableCharacterDescriptionPtr getCharacterDsc() const;

private:
  enum Panel
  {
    RACE_SELECTION,
    CLASS_SELECTION,
    ABILITY_SCORE_SELECTION,
    THIEF_SKILLS_SELECTION
  };

  std::map<int, ASubPanelPtr> _panels;
  int _activePanel;
  bool _enterGame;

  RaceSelectionPanelPtr _raceSelection;
  ClassSelectionPanelPtr _classSelection;
  AbilityScoresSelectionPanelPtr _scoresSelection;
  ThiefSkillsSelectionPanelPtr _thiefSkillsSelection;

  ActorDescriptionPtr _player;

  void showActivePanel();

};

}}

#endif // CHARACTER_CREATION_WINDOW_H
