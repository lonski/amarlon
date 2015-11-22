#include "class_selection_panel.h"
#include <amenu.h>
#include <engine.h>
#include <rpg_db.h>
#include <aslot_menu_item.h>
#include <alist.h>
#include <character_class.h>
#include <character_creation_window.h>
#include <spell_id.h>

namespace amarlon { namespace gui {

ClassSelectionPanel::ClassSelectionPanel(CharacterCreationWindow* parent)
  : ASubPanel(Engine::screenWidth, Engine::screenHeight)
  , _classes(new AMenu )
  , _dsc( new AList )
  , _parent(parent)
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
  if ( _parent )
  {
    RacePtr race = Engine::instance().
        getRpgDB().
        getRace( (RaceType)*_parent->getCharacterDsc()->race );

    if ( race )
    {
      removeAllWidgets();

      //Classes menu
      _classes->removeAllItems();
      _classes->setPosition(2,2);
      addWidget( _classes );

      for ( auto c : Engine::instance().getRpgDB().getCharacterClasses() )
      {
        if ( c->isPlayable() && race->isClassAllowed( c->getType() ) )
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

      selectNext();
    }
  }

}

void ClassSelectionPanel::handleKey(TCOD_key_t key)
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
      setClass();
      _parent->nextStep();
      break;
    }
    default:;
  }
}

CharacterClassPtr ClassSelectionPanel::getSelectedClass() const
{
  CharacterClassPtr c;

  auto item = _classes->getSelectedItem();
  if ( item )
  {
    c = item->getObject<CharacterClass>();
  }

  return c;
}

void ClassSelectionPanel::setClass()
{
  auto cClass = getSelectedClass();
  if ( cClass && _parent )
  {
    PlayableCharacterDescriptionPtr dsc = _parent->getCharacterDsc();
    if ( dsc )
    {
      dsc->cClass = (int)cClass->getType();

      //Add known spells
      dsc->spellbook = SpellbookDescription();
      if ( cClass->getType() == CharacterClassType::MagicUser )
      {
        (*dsc->spellbook).knownSpells.push_back( (int)SpellId::MagicMissile );
      }
    }
  }
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
