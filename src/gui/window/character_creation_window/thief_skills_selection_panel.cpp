#include "thief_skills_selection_panel.h"
#include <alabel.h>
#include <engine.h>
#include <apanel_button.h>
#include <message_box.h>
#include <character_creation_window.h>
#include <skill_db.h>
#include <value_setting_panel.h>

namespace amarlon { namespace gui {

ThiefSkillsSelectionPanel::ThiefSkillsSelectionPanel(CharacterCreationWindow *parent)
  : ASubPanel(Engine::screenWidth, Engine::screenHeight)
  , _parent(parent)
  , _activePanel(OpenLocks)
  , _freePoints(0)
  , _poolLabel( new ALabel )
  , _nextBtn( new APanelButton(12,"Continue") )
{
  setTitle("Thief skills selection");
}

void ThiefSkillsSelectionPanel::selectNext()
{
  _panels[_activePanel]->selectNext();
}

void ThiefSkillsSelectionPanel::selectPrevious()
{
  _panels[_activePanel]->selectPrevious();
}

void ThiefSkillsSelectionPanel::manage()
{
  _panels[_activePanel]->manage();
  updatePoolValue();
}

void ThiefSkillsSelectionPanel::update()
{
  removeAllWidgets();
  if ( _parent )
  {
    addValuePanels();
    addPoolPoints();
    addContinueButton();

    _activePanel = (Panel)0;
    _panels[ _activePanel ]->activate();
  }
}

void ThiefSkillsSelectionPanel::handleKey(TCOD_key_t key)
{
  switch ( key.vk )
  {
    case TCODK_RIGHT:
    case TCODK_KP6:
    {
      selectNext();
      break;
    }
    case TCODK_LEFT:
    case TCODK_KP4:
    {
      selectPrevious();
      break;
    }
    case TCODK_UP:
    case TCODK_KP8:
    {
      activatePreviousPanel();
      break;
    }
    case TCODK_DOWN:
    case TCODK_KP2:
    {
      activateNextPanel();
      break;
    }
    case TCODK_TAB:
    {
      activateNextPanel();
      break;
    }
    case TCODK_ENTER:
    case TCODK_KPENTER:
    {
      manage();
      break;
    }
    default:;
  }
}

void ThiefSkillsSelectionPanel::updatePoolValue()
{
  _poolLabel->setValue( "Points left: " + toStr(_freePoints) );
  _poolLabel->setPosition( AWindow::WINDOW_CENTER);
  _poolLabel->setY(55);
}

void ThiefSkillsSelectionPanel::addPoolPoints()
{
  _freePoints = 0;
  updatePoolValue();
  addWidget(_poolLabel);
}

void ThiefSkillsSelectionPanel::addContinueButton()
{
  _nextBtn->setPosition( getWidth() - _nextBtn->getWidth() - 2,
                         getHeight() - _nextBtn->getHeight() - 2);

  _nextBtn->setCallBack([&](){next();});
  _nextBtn->deactivate();

  _panels[ NEXT ] = _nextBtn;
  addWidget( _nextBtn );
}

void ThiefSkillsSelectionPanel::addValuePanels()
{
  addValuePanel( Engine::instance().getSkillDB().getName( SkillId::OpenLocks )   ,OpenLocks,   18);
  addValuePanel( Engine::instance().getSkillDB().getName( SkillId::DisarmTraps ) ,DisarmTraps, 24);
  addValuePanel( Engine::instance().getSkillDB().getName( SkillId::Hide )        ,Hide,        30);
  addValuePanel( Engine::instance().getSkillDB().getName( SkillId::PickPockets ) ,PickPockets, 36);
  addValuePanel( Engine::instance().getSkillDB().getName( SkillId::SilentMove )  ,SilentMove,  42);
  addValuePanel( Engine::instance().getSkillDB().getName( SkillId::FindTraps )   ,FindTraps,   48);
}

void ThiefSkillsSelectionPanel::activateNextPanel()
{
  auto cPanel = _panels.find( _activePanel );
  assert( cPanel != _panels.end());

  cPanel->second->deactivate();

  if ( ++cPanel == _panels.end() ) cPanel = _panels.begin();

  _activePanel = cPanel->first;
  cPanel->second->activate();
}

void ThiefSkillsSelectionPanel::activatePreviousPanel()
{
  auto cPanel = _panels.find( _activePanel );
  assert( cPanel != _panels.end());

  cPanel->second->deactivate();

  if ( cPanel != _panels.begin()  )
    --cPanel;
  else
    std::advance(cPanel, _panels.size() - 1 );

  _activePanel = cPanel->first;
  cPanel->second->activate();
}

void ThiefSkillsSelectionPanel::addValuePanel(const std::string& skill, Panel panel, int y)
{
  MinMax constrains(10,40);
  int startingValue = 20;

  ValueSettingPanelPtr p(new ValueSettingPanel( skill, startingValue, constrains, _freePoints ));
  p->setWidth( 30 );
  p->update();
  p->setPosition( AWindow::WINDOW_CENTER );
  p->setY( y );
  _panels[ panel ] = p;
  addWidget(p);
}

int ThiefSkillsSelectionPanel::getValue(ThiefSkillsSelectionPanel::Panel panel)
{
  ValueSettingPanelPtr p = std::dynamic_pointer_cast<ValueSettingPanel>(_panels[ panel ]);
  return p ? p->getValue() : 0;
}

void ThiefSkillsSelectionPanel::next()
{
  if ( _parent )
  {
    if ( (_freePoints > 0 &&
          questionBox("There are still some unassigned points.#Are you sure you want to continue?",
                      MsgType::Warning) == QuestionDialog::Response::YES)
         || _freePoints == 0 )
    {
      setSkills();
      _parent->nextStep();
    }

  }
}

void ThiefSkillsSelectionPanel::setSkills()
{
  if ( _parent )
  {
    CharacterDescriptionPtr dsc = _parent->getCharacterDsc();
    if ( dsc )
    {
      dsc->skills.push_back( SkillDescription( (int)SkillId::OpenLocks,   getValue(OpenLocks)) );
      dsc->skills.push_back( SkillDescription( (int)SkillId::DisarmTraps, getValue(DisarmTraps)) );
      dsc->skills.push_back( SkillDescription( (int)SkillId::Hide,        getValue(Hide)) );
      dsc->skills.push_back( SkillDescription( (int)SkillId::PickPockets, getValue(PickPockets)) );
      dsc->skills.push_back( SkillDescription( (int)SkillId::SilentMove,  getValue(SilentMove)) );
      dsc->skills.push_back( SkillDescription( (int)SkillId::FindTraps,   getValue(FindTraps)) );
    }
  }
}

}}
