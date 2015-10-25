#ifndef THIEF_SKILLS_SELECTION_PANEL_H
#define THIEF_SKILLS_SELECTION_PANEL_H

#include <asub_panel.h>
#include <skill_id.h>

namespace amarlon { namespace gui {

class APanelButton;
class CharacterCreationWindow;
class ValueSettingPanel;
class ALabel;
typedef std::shared_ptr<ALabel> ALabelPtr;
typedef std::shared_ptr<APanelButton> PanelButtonPtr;
typedef std::shared_ptr<ValueSettingPanel> ValueSettingPanelPtr;

class ThiefSkillsSelectionPanel : public ASubPanel
{
public:
  ThiefSkillsSelectionPanel(CharacterCreationWindow* parent);

  virtual void selectNext();
  virtual void selectPrevious();

  virtual void manage();
  virtual void update();
  virtual void handleKey(TCOD_key_t key);

private:
  enum Panel
  {
    OpenLocks,
    DisarmTraps,
    Hide,
    PickPockets,
    SilentMove,
    FindTraps,
    NEXT
  };

  CharacterCreationWindow* _parent;

  std::map<Panel, ASubPanelPtr> _panels;
  Panel _activePanel;

  int _freePoints;
  ALabelPtr _poolLabel;
  PanelButtonPtr _nextBtn;

  void updatePoolValue();
  void addPoolPoints();
  void addContinueButton();
  void addValuePanels();
  void activateNextPanel();
  void activatePreviousPanel();
  void addValuePanel(const std::string& skill, Panel panel, int y);
  int getValue(Panel panel);

  void next();
  void setSkills();

};

}}

#endif // THIEF_SKILLS_SELECTION_PANEL_H
