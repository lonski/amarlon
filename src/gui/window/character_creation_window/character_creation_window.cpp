#include "character_creation_window.h"
#include <engine.h>
#include <asub_panel.h>
#include <race_selection_panel.h>
#include <class_selection_panel.h>
#include <ability_scores_selection_panel.h>
#include <actor_db.h>
#include <map_id.h>
#include <world.h>
#include <actor.h>
#include <playable_character.h>

namespace amarlon { namespace gui {

CharacterCreationWindow::CharacterCreationWindow()
  : _enterGame(false)
  , _raceSelection( new RaceSelectionPanel(this) )
  , _classSelection( new ClassSelectionPanel(this) )
  , _scoresSelection( new AbilityScoresSelectionPanel(this) )
{
  setHeight( Engine::screenHeight );
  setWidth( Engine::screenWidth );

  _raceSelection->setPosition(0,0);
  _panels[RACE_SELECTION] = _raceSelection;

  _classSelection->setPosition(0,0);
  _panels[CLASS_SELECTION] = _classSelection;

  _scoresSelection->setPosition(0,0);
  _panels[ABILITY_SCORE_SELECTION] = _scoresSelection;
}

CharacterCreationWindow::~CharacterCreationWindow()
{
}

void CharacterCreationWindow::showActivePanel()
{
  removeAllWidgets();
  _panels [ _activePanel ]->update();
  _panels [ _activePanel ]->selectNext();
  addWidget( _panels [ _activePanel ] );
}

AWindow &CharacterCreationWindow::show()
{
  showActivePanel();

  TCOD_key_t key;

  while( !TCODConsole::isWindowClosed() )
  {
    render(*TCODConsole::root);
    TCODConsole::root->flush();

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);

    _panels[_activePanel]->handleKey(key);

    if ( _enterGame )
    {
      ActorPtr player = Actor::create( _player, false);
      player->setPosition(42, 28);
      PlayableCharacterPtr c = player->getFeature<PlayableCharacter>();
      c->advanceLevel();

      Engine::instance().getWorld().changeMap( MapId::GameStart );
      Engine::instance().getWorld().setPlayer( player );

      Engine::instance().enterGame();
      break;
    }
  }

  return *this;
}

AWindow& CharacterCreationWindow::setDefaults()
{
  _activePanel = RACE_SELECTION;
  _enterGame = false;
  _player = Engine::instance().getActorDB().fetchDescription( ActorType::Player );

  return *this;
}

void CharacterCreationWindow::nextStep()
{
  auto cPanel = _panels.find( _activePanel );
  assert( cPanel != _panels.end());

  _enterGame = ++cPanel == _panels.end();

  if ( !_enterGame )
  {
    _activePanel = cPanel->first;
    showActivePanel();
  }
}

ActorDescriptionPtr CharacterCreationWindow::getPlayerDsc() const
{
  return _player;
}

}}
