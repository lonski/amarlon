#include "cmd_use.h"
#include <target_type.h>
#include <target_selector.h>
#include <engine.h>
#include <message_box.h>
#include <menu_window.h>
#include <use_action.h>
#include <inventory.h>
#include <scroll.h>
#include <spell_book.h>
#include <menu_window.h>
#include <alabel_menu_item.h>
#include <transcribe_action.h>

namespace amarlon {

CmdUse::CmdUse()
{
}

bool CmdUse::accept(const TCOD_key_t& key)
{
  return ( key.vk == TCODK_CHAR && key.c == 'u' );
}

int CmdUse::execute()
{  
  int turns = 0;
  ActorPtr item = acquireItemToUse();
  Engine::instance().render();
  TCODConsole::root->flush();

  if (item != nullptr)
  {
    //For scroll prompt player for action (cast or transcribe)
    ScrollPtr scroll = item->getFeature<Scroll>();
    if ( scroll && !knowSpell( scroll->getSpell() ) )
    {
      gui::ALabelMenuItemPtr castItem( new gui::ALabelMenuItem("Cast") );
      gui::ALabelMenuItemPtr transcribeItem( new gui::ALabelMenuItem("Transcribe") );

      auto& window = Engine::instance().getWindowManager().getWindow<gui::MenuWindow>();
            window.addMenuItem( castItem );
            window.addMenuItem( transcribeItem );
            window.show();

      if ( window.getSelectedItem() == castItem )
      {
        turns = useItem(item);
      }
      else
      {
        turns = transcribeScroll( scroll );
      }
    }
    else
    {
      turns = useItem(item);
    }
  }

  return turns;
}

int CmdUse::useItem(ActorPtr item)
{
  int turns = 0;

  PickablePtr pickable = item->getFeature<Pickable>();
  if ( pickable )
  {
    TargetSelectorPtr tSelector = TargetSelector::create(pickable->getTargetType());

    tSelector->setRange( pickable->getRange() );
    tSelector->setRadius( pickable->getRadius() );

    if ( tSelector != nullptr )
    {
      Engine::instance().getPlayer()->performAction( std::make_shared<UseAction>( tSelector->select(), item) );
      ++turns;
    }
  }

  return turns;
}

bool CmdUse::knowSpell(SpellPtr spell)
{
  bool know = false;

  ActorPtr player = Engine::instance().getPlayer();
  CharacterPtr c = player->getFeature<Character>();
  if ( spell && c && c->getSpellBook() )
  {
    know = c->getSpellBook()->knowSpell( spell  );
  }

  return know;
}

int CmdUse::transcribeScroll(ScrollPtr scroll)
{
  int turns = 0;

  if ( scroll )
  {
    ActorPtr player = Engine::instance().getPlayer();
    if ( player->performAction( new TranscribeAction(scroll) ) == ActorActionResult::Ok )
    {
      turns = 20;
    }
    else
    {
      gui::msgBox("Failed to transcribe spell.", gui::MsgType::Error );
    }
  }

  return turns;
}

ActorPtr CmdUse::acquireItemToUse()
{
  ActorPtr item;

  gui::MenuWindow& window = Engine::instance().getWindowManager().getWindow<gui::MenuWindow>();
                   window . setPosition(gui::AWidget::GAME_SCREEN_CENTER);
                   window . setTitle("Choose item to use");

  auto usableItems = getUsableItems();
  if ( !usableItems.empty() )
  {
    window.fill<Actor>( usableItems, [](ActorPtr a){ return a->getName(); } );
    window.show();
    if ( auto selected = window.getSelectedItem() )
    {
      item = selected->getObject<Actor>();
    }
  }
  else gui::msgBox("You don't have any usable items!", gui::MsgType::Warning);

  if ( item != nullptr && item->getFeature<Pickable>()->isStackable() ) item = item->getFeature<Pickable>()->spilt(1);

  return item;
}

std::vector<ActorPtr> CmdUse::getUsableItems()
{
  auto filter = [&](ActorPtr a){ return a->getFeature<Pickable>()->isUsable(); };
  return Engine::instance().getPlayer()->getFeature<Inventory>()->items(filter);
}

}

