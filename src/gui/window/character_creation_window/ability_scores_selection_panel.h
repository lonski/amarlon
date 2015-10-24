#ifndef ABILITY_SCORES_SELECTION_PANEL_H
#define ABILITY_SCORES_SELECTION_PANEL_H

#include <map>
#include <memory>
#include <ability_scores.h>
#include <asub_panel.h>

namespace amarlon {

class Race;
class CharacterClass;
typedef std::shared_ptr<Race> RacePtr;
typedef std::shared_ptr<CharacterClass> CharacterClassPtr;

namespace gui {

class APanelButton;
class CharacterCreationWindow;
class ASlotMenuItem;
class ValueSettingPanel;
class ALabel;
typedef std::shared_ptr<ASlotMenuItem> ASlotMenuItemPtr;
typedef std::shared_ptr<ALabel> ALabelPtr;
typedef std::shared_ptr<APanelButton> PanelButtonPtr;
typedef std::shared_ptr<ValueSettingPanel> ValueSettingPanelPtr;

class AbilityScoresSelectionPanel : public ASubPanel
{
public:
  AbilityScoresSelectionPanel(CharacterCreationWindow* parent);

  virtual void selectNext();
  virtual void selectPrevious();

  virtual void manage();
  virtual void update();
  virtual void handleKey(TCOD_key_t key);


private:
  enum Panel
  {
    STR,
    INT,
    WIS,
    DEX,
    CON,
    CHA,
    NEXT
  };

  CharacterCreationWindow* _parent;

  std::map<Panel, ASubPanelPtr> _panels;
  Panel _activePanel;

  RacePtr _race;
  CharacterClassPtr _class;

  int _freePoints;
  ALabelPtr _poolLabel;
  PanelButtonPtr _nextBtn;

  void addContinueButton();
  void addPoolPoints();
  void addValuePanels();
  void addValuePanel(amarlon::AbilityScore::Type as, int y);
  void activateNextPanel();
  void activatePreviousPanel();
  void updatePoolValue();

  void next();
  void setScores();
  virtual int getValue(AbilityScore::Type as);

};

}}

#endif // ABILITY_SCORES_SELECTION_PANEL_H
