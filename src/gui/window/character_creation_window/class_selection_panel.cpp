#include "class_selection_panel.h"
#include <amenu.h>
#include <engine.h>
#include <rpg_db.h>
#include <aslot_menu_item.h>
#include <alist.h>
#include <character_class.h>

namespace amarlon { namespace gui {

ClassSelectionPanel::ClassSelectionPanel()
  : ASubPanel(Engine::screenWidth, Engine::screenHeight)
  , _classes(new AMenu )
  , _dsc( new AList )
{
  setPosition(0,0);
  setFrame(true);
  setTitle("Character class selection");
}

void ClassSelectionPanel::selectNext()
{
  _classes->selectNext();
  showDescription();
}

void ClassSelectionPanel::selectPrevious()
{
  _classes->selectPrevious();
  showDescription();
}

void ClassSelectionPanel::manage()
{

}

void ClassSelectionPanel::update()
{
  removeAllWidgets();

  //Classes menu
  _classes->removeAllItems();
  _classes->setPosition(2,2);
  addWidget( _classes );

  for ( auto c : Engine::instance().getRpgDB().getCharacterClasses() )
  {
    if ( c->isPlayable() )
    {
      AMenuItemPtr item(new ASlotMenuItem(35,c->getName(),"",""));
      item->setObject<CharacterClass>(c);
      _classes->addItem( item );
    }
  }

  //Class description
  _dsc->clear();
  _dsc->setPosition( 40, 2 );
  _dsc->setAutosize(false);
  _dsc->setWidth( Engine::screenWidth - _dsc->getX() - 4 );
  _dsc->setHeight( Engine::screenHeight - 4 );
  addWidget( _dsc );

}

void ClassSelectionPanel::showDescription()
{
  _dsc->clear();
  auto item = _classes->getSelectedItem();
  if ( item )
  {
    CharacterClassPtr cClass = item->getObject<CharacterClass>();
    if ( cClass )
    {
      auto lines = _formater.format( cClass->getDescription(), _dsc->getWidth() );
      for ( auto l : lines )
      {
        _dsc->pushBack( l );
      }
    }
  }
}

}}
