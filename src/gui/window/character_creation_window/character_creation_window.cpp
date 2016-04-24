#include "character_creation_window.h"
#include <engine.h>
#include <asub_panel.h>
#include <race_selection_panel.h>
#include <class_selection_panel.h>
#include <ability_scores_selection_panel.h>
#include <actor_db.h>
#include <world.h>
#include <actor.h>
#include <playable_character.h>
#include <thief_skills_selection_panel.h>
#include <module.h>

namespace amarlon { namespace gui {

CharacterCreationWindow::CharacterCreationWindow()
  : _activePanel(0)
  , _enterGame(false)
  , _raceSelection( new RaceSelectionPanel(this) )
  , _classSelection( new ClassSelectionPanel(this) )
  , _scoresSelection( new AbilityScoresSelectionPanel(this) )
  , _thiefSkillsSelection( new ThiefSkillsSelectionPanel(this) )
{
  setHeight( Engine::screenHeight );
  setWidth( Engine::screenWidth );

  _raceSelection->setPosition(0,0);
  _panels[RACE_SELECTION] = _raceSelection;

  _classSelection->setPosition(0,0);
  _panels[CLASS_SELECTION] = _classSelection;

  _scoresSelection->setPosition(0,0);
  _panels[ABILITY_SCORE_SELECTION] = _scoresSelection;

  _thiefSkillsSelection->setPosition(0,0);
  _panels[THIEF_SKILLS_SELECTION] = _thiefSkillsSelection;
}

CharacterCreationWindow::~CharacterCreationWindow()
{
}

void CharacterCreationWindow::showActivePanel()
{
  removeAllWidgets();
  _panels [ _activePanel ]->update();
  addWidget( _panels [ _activePanel ] );
}

AWindow &CharacterCreationWindow::show()
{
  TCODConsole* console = Engine::instance().getConsole();
  if ( console )
  {
    showActivePanel();

    TCOD_key_t key;

    while( !TCODConsole::isWindowClosed() )
    {
      render(*console);
      Engine::instance().flush();

      TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);

      _panels[_activePanel]->handleKey(key);

      if ( _enterGame )
      {
        ActorPtr player = Actor::create( _player, false);
        player->setPosition( Engine::instance().getModule().getStartX(),
                             Engine::instance().getModule().getStartY());
        PlayableCharacterPtr c = player->getFeature<PlayableCharacter>();
        c->advanceLevel();

        Engine::instance().getWorld().changeMap( Engine::instance().getModule().getStartMap() );
        Engine::instance().getWorld().setPlayer( player );

        Engine::instance().enterGame();
        break;
      }
    }
  }
  return *this;
}

AWindow& CharacterCreationWindow::setDefaults()
{
  _activePanel = RACE_SELECTION;
  _enterGame = false;
  _player = Engine::instance().getActorDB().fetchDescription( 1 /*Player*/ );

  return *this;
}

void CharacterCreationWindow::nextStep()
{
  auto cPanel = _panels.find( _activePanel );
  assert( cPanel != _panels.end());

  ++cPanel;

  //Skip class-specific panels
  CharacterClassType cId = (CharacterClassType)*getCharacterDsc()->cClass;
  if ( cPanel != _panels.end() )
  {
    if ( (cPanel->first == THIEF_SKILLS_SELECTION && cId != CharacterClassType::Thief) )
    {
      ++cPanel;
    }
  }

  //Proceed with current panel
  if ( cPanel == _panels.end() )
  {
    _enterGame = true;
  }
  else
  {
    _activePanel = cPanel->first;
    showActivePanel();
  }
}

ActorDescriptionPtr CharacterCreationWindow::getPlayerDsc() const
{
  return _player;
}

CharacterDescriptionPtr CharacterCreationWindow::getCharacterDsc() const
{
  auto& f = getPlayerDsc()->features;
  auto it = f.find(ActorFeature::CHARACTER);
  return it != f.end() ? std::dynamic_pointer_cast<CharacterDescription>(it->second) : nullptr;
}

}}
