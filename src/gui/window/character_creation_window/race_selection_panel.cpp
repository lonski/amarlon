#include "race_selection_panel.h"
#include <amenu.h>
#include <engine.h>
#include <rpg_db.h>
#include <aslot_menu_item.h>
#include <alist.h>
#include <message_box.h>

namespace amarlon { namespace gui {

RaceSelectionPanel::RaceSelectionPanel()
  : ASubPanel(Engine::screenWidth, Engine::screenHeight)
  , _races(new AMenu )
  , _dsc( new AList )
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

}}
