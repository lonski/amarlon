#include "race_selection_panel.h"
#include <amenu.h>
#include <engine.h>
#include <race.h>
#include <rpg_db.h>
#include <aslot_menu_item.h>
#include <alist.h>
#include <character_creation_window.h>
#include <skill.h>
#include <actor_feature.h>

namespace amarlon { namespace gui {

RaceSelectionPanel::RaceSelectionPanel(CharacterCreationWindow *parent)
  : ASubPanel(Engine::screenWidth, Engine::screenHeight)
  , _races(new AMenu )
  , _dsc( new AList )
  , _parent(parent)
{
  setPosition(0,0);
  setFrame(true);
  setTitle("Character race selection");
}

void RaceSelectionPanel::selectNext()
{
  _races->selectNext();
  showDescription();
}

void RaceSelectionPanel::selectPrevious()
{
  _races->selectPrevious();
  showDescription();
}

void RaceSelectionPanel::manage()
{

}

void RaceSelectionPanel::update()
{
  removeAllWidgets();

  //Races menu
  _races->removeAllItems();
  _races->setPosition(2,2);
  addWidget( _races );

  for ( auto r : Engine::instance().getRpgDB().getRaces() )
  {
    if ( r->isPlayable() )
    {
      AMenuItemPtr item(new ASlotMenuItem(35,r->getName(),"",""));
      item->setObject<Race>(r);
      _races->addItem( item );
    }
  }

  //Race description
  _dsc->clear();
  _dsc->setPosition( 40, 2 );
  _dsc->setAutosize(false);
  _dsc->setWidth( Engine::screenWidth - _dsc->getX() - 4 );
  _dsc->setHeight( Engine::screenHeight - 4 );
  addWidget( _dsc );

  selectNext();

}

void RaceSelectionPanel::handleKey(TCOD_key_t key)
{
  switch ( key.vk )
  {
    case TCODK_DOWN:
    case TCODK_KP2:
    {
      selectNext();
      break;
    }
    case TCODK_UP:
    case TCODK_KP8:
    {
      selectPrevious();
      break;
    }
    case TCODK_ENTER:
    case TCODK_KPENTER:
    {
      setRace();
      _parent->nextStep();
      break;
    }
    default:;
  }
}

RacePtr RaceSelectionPanel::getSelectedRace() const
{
  RacePtr race;

  auto item = _races->getSelectedItem();
  if ( item )
  {
    race = item->getObject<Race>();
  }

  return race;
}

void RaceSelectionPanel::showDescription()
{
  _dsc->clear();
  auto item = _races->getSelectedItem();
  if ( item )
  {
    RacePtr race = item->getObject<Race>();
    if ( race )
    {
      auto lines = _formater.format( race->getDescription(), _dsc->getWidth() );
      for ( auto l : lines )
      {
        _dsc->pushBack( l );
      }
    }
  }
}

void RaceSelectionPanel::setRace()
{
  auto race = getSelectedRace();
  if ( race )
  {
    CharacterDescriptionPtr dsc =
        std::dynamic_pointer_cast<CharacterDescription>
        (_parent->getPlayerDsc()->features[ActorFeature::CHARACTER]);

    if ( dsc )
    {
      dsc->race = (int)race->getType();
      for( auto s : race->getSkills() )
      {
        dsc->skills.push_back(
              std::make_pair( static_cast<int>(s->getId()), s->getLevel() ) );
      }
    }
  }
}

}}
