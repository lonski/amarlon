#include "ability_scores_selection_panel.h"
#include <alabel.h>
#include <character_creation_window.h>
#include <character_class.h>
#include <race.h>
#include <dices.h>
#include <message_box.h>
#include <engine.h>
#include <rpg_db.h>
#include <apanel_button.h>
#include <aslot_menu_item.h>
#include <value_setting_panel.h>

namespace amarlon { namespace gui {

AbilityScoresSelectionPanel::AbilityScoresSelectionPanel(CharacterCreationWindow *parent)
  : ASubPanel(Engine::screenWidth, Engine::screenHeight)
  , _parent(parent)
  , _activePanel(STR)
  , _freePoints(0)
  , _poolLabel( new ALabel )
  , _nextBtn( new APanelButton(12,"Continue") )
{
  setTitle("Ability scores selection");
}

void AbilityScoresSelectionPanel::selectNext()
{
  _panels[_activePanel]->selectNext();
}

void AbilityScoresSelectionPanel::selectPrevious()
{
  _panels[_activePanel]->selectPrevious();
}

void AbilityScoresSelectionPanel::manage()
{
  _panels[_activePanel]->manage();
  updatePoolValue();
}

void AbilityScoresSelectionPanel::update()
{
  removeAllWidgets();
  if ( _parent )
  {
    _race = Engine::instance().
        getRpgDB().
        getRace( (RaceType)*_parent->getCharacterDsc()->race );

    _class = Engine::instance().
        getRpgDB().
        getCharacterClass( (CharacterClassType)*_parent->getCharacterDsc()->cClass );

    if ( _race && _class )
    {
      addValuePanels();
      addPoolPoints();
      addContinueButton();

      _activePanel = (Panel)0;
      _panels[ _activePanel ]->activate();
    }
  }
}

void AbilityScoresSelectionPanel::addValuePanels()
{
  addValuePanel(AbilityScore::STR, 18);
  addValuePanel(AbilityScore::INT, 24);
  addValuePanel(AbilityScore::WIS, 30);
  addValuePanel(AbilityScore::DEX, 36);
  addValuePanel(AbilityScore::CON, 42);
  addValuePanel(AbilityScore::CHA, 48);
}

void AbilityScoresSelectionPanel::addValuePanel(AbilityScore::Type as, int y)
{
  MinMax constrains = _race->getAbilityScoreRestriction( as );
  constrains.merge( _class->getAbilityScoreRestriction( as ) );

  int roll = 0;
  while ( !constrains.allow( roll ) ) roll = dices::roll(dices::D6, 3);

  ValueSettingPanelPtr p(new ValueSettingPanel( AbilityScore::toStr(as), roll, constrains, _freePoints ));
  p->update();
  p->setPosition( AWindow::WINDOW_CENTER );
  p->setY( y );
  _panels[ (Panel)as ] = p;
  addWidget(p);
}

void AbilityScoresSelectionPanel::addContinueButton()
{
  _nextBtn->setPosition( getWidth() - _nextBtn->getWidth() - 2,
                         getHeight() - _nextBtn->getHeight() - 2);

  _nextBtn->setCallBack([&](){next();});
  _nextBtn->deactivate();

  _panels[ NEXT ] = _nextBtn;
  addWidget( _nextBtn );
}

void AbilityScoresSelectionPanel::addPoolPoints()
{
  _freePoints = 0;
  updatePoolValue();
  addWidget(_poolLabel);
}

void AbilityScoresSelectionPanel::handleKey(TCOD_key_t key)
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

void AbilityScoresSelectionPanel::activateNextPanel()
{
  auto cPanel = _panels.find( _activePanel );
  assert( cPanel != _panels.end());

  cPanel->second->deactivate();

  if ( ++cPanel == _panels.end() ) cPanel = _panels.begin();

  _activePanel = cPanel->first;
  cPanel->second->activate();
}

void AbilityScoresSelectionPanel::activatePreviousPanel()
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

void AbilityScoresSelectionPanel::updatePoolValue()
{
  _poolLabel->setValue( "Points left: " + toStr(_freePoints) );
  _poolLabel->setPosition( AWindow::WINDOW_CENTER);
  _poolLabel->setY(55);
}

void AbilityScoresSelectionPanel::next()
{
  if ( _parent )
  {
    if ( (_freePoints > 0 &&
          questionBox("There are still some unassigned points.#Are you sure you want to continue?",
                      MsgType::Warning) == QuestionDialog::Response::YES)
         || _freePoints == 0 )
    {
      setScores();
      _parent->nextStep();
    }

  }
}

void AbilityScoresSelectionPanel::setScores()
{
  PlayableCharacterDescriptionPtr d = _parent->getCharacterDsc();
  if ( d )
    for ( auto as : AbilityScore::Type() )
      d->abilityScores[as] = getValue(as);
}

int AbilityScoresSelectionPanel::getValue(AbilityScore::Type as)
{
  ValueSettingPanelPtr p = std::dynamic_pointer_cast<ValueSettingPanel>(_panels[ (Panel)as ]);
  return p ? p->getValue() : 0;
}

}}
