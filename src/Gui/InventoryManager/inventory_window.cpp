#include "inventory_window.h"
#include <Utils/glodef.h>
#include <Actor/Actor.h>
#include <Actor/ActorFeatures/Wearer/item_slot_type.h>
#include <Gui/Widget/label.h>
#include <Gui/Widget/list.h>
#include <Gui/InventoryManager/body_slots_manager.h>

namespace amarlon { namespace gui {

InventoryWindow::InventoryWindow(const std::vector<Actor *> &items)
  : windowHeight( gloScreenHeight )
  , windowWidth( gloScreenWidth )
  , _bodyPanel( windowWidth / 2, windowHeight )
  , _bagPanel( windowWidth / 2, windowHeight )
  , _items(items)
{
  setupBagPanelWidgets();
  setupBodyPanelWidgets();
}

void InventoryWindow::setupBagPanelWidgets()
{
  _bagPanel.setPosition(windowWidth / 2, 0);
  _bagPanel.setTitle("Inventory");

  _bagMenu.reset( new CategorizedMenu(_bagPanel.getWidth() - 4, _bagPanel.getHeight() - 4) );
  _bagMenu->setPosition(2,2);
  _bagMenu->setFrame(false);

  //temporary for tests, TODO
  _bagMenu->addMenuItem("Dagger +1", "Weapons");
  _bagMenu->addMenuItem("Flaming long sword +1", "Weapons");
  _bagMenu->addMenuItem("Spear", "Weapons");

  _bagMenu->addMenuItem("Kaftan dziewicy","Armors");
  _bagMenu->addMenuItem("Kloczuga","Armors");

  _bagPanel.addWidget(_bagMenu);


}

void InventoryWindow::setupBodyPanelWidgets()
{
  _bodyPanel.setTitle("Equipped items");

  BodySlotsManager* bodySlots = new BodySlotsManager(_bodyPanel.getWidth() - 2, _bodyPanel.getHeight() - 2);
  bodySlots->setPosition(1,1);
  bodySlots->setMargin(1);

  for( int i = (int)ItemSlotType::Null + 1; i != (int)ItemSlotType::End; ++i)
  {
    bodySlots->addSlot(ItemSlotType2Str(i), (ItemSlotType)i);
  }

  _bodyPanel.addWidget(bodySlots);
}

void InventoryWindow::render(TCODConsole &console)
{
  _bodyPanel.render(console);
  _bagPanel.render(console);
}

void InventoryWindow::show(TCODConsole &console)
{
  TCOD_key_t key;

  while( !(key.vk == TCODK_ESCAPE)               &&
         !(key.vk == TCODK_CHAR && key.c == 'i') &&
         !(TCODConsole::isWindowClosed()))
  {      
    render(console);
    console.flush();

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);

    //temporary, TODO
    if ( key.vk == TCODK_DOWN ) _bagMenu->selectNext();
    if ( key.vk == TCODK_UP ) _bagMenu->selectPrevious();
  }
}

}}
