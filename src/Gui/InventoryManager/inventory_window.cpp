#include "inventory_window.h"
#include <Utils/glodef.h>
#include <Actor/ActorFeatures/Wearer/item_slot_type.h>
#include <Gui/Widget/label.h>
#include <Gui/Widget/list.h>
#include <Gui/InventoryManager/body_slots_manager.h>
#include <Gui/InventoryManager/bag_category.h>

namespace amarlon { namespace gui {

InventoryWindow::InventoryWindow()
  : windowHeight( gloScreenHeight )
  , windowWidth( gloScreenWidth )
  , _bodyPanel( windowWidth / 2, windowHeight )
  , _bagPanel( windowWidth / 2, windowHeight )
{
  setupBagPanelWidgets();
  setupBodyPanelWidgets();
}

void InventoryWindow::setupBagPanelWidgets()
{
  _bagPanel.setPosition(windowWidth / 2, 0);
  _bagPanel.setTitle("Inventory");

  // === Weapons
  BagCategory* wpnCat = new BagCategory( _bagPanel.getWidth() - 4, "Weapons" );
  wpnCat->setPosition(2,2);
  _bagPanel.addWidget(wpnCat);

  wpnCat->addItem("Dagger +1");
  wpnCat->addItem("Flaming long sword +1");
  wpnCat->addItem("Spear");

  // === Armors
  BagCategory* armCat = new BagCategory( _bagPanel.getWidth() - 4, "Armors" );
  armCat->setPosition(2, wpnCat->getY() + wpnCat->getHeight() + 1);
  _bagPanel.addWidget(armCat);

  armCat->addItem("Chainmail of the Sun +3");

  // === Misc
  BagCategory* miscCat = new BagCategory( _bagPanel.getWidth() - 4, "Miscellaneous" );
  miscCat->setPosition(2, armCat->getY() + armCat->getHeight() + 1);
  _bagPanel.addWidget(miscCat);

  miscCat->addItem("Pantry key");
  miscCat->addItem("Love letter");
  miscCat->addItem("Gold pieces (666)");
  miscCat->addItem("Arrow of ice (20)");

  miscCat->select(1);
  miscCat->select(2);
  miscCat->unselect(2);

}

void InventoryWindow::setupBodyPanelWidgets()
{
  _bodyPanel.setTitle("Equipped items");

  BodySlotsManager* bodySlots = new BodySlotsManager(_bodyPanel.getWidth() - 2, _bodyPanel.getHeight() - 2);
  bodySlots->setPosition(1,1);
  bodySlots->setMargin(1);

  bodySlots->addSlot("Main hand", ItemSlotType::MainHand, "Short sword");
  bodySlots->addSlot("Armor", ItemSlotType::Armor, "Leather armor");
  bodySlots->addSlot("Off-hand", ItemSlotType::Offhand);
  bodySlots->addSlot("Helmet", ItemSlotType::Helmet);
  bodySlots->addSlot("Hands", ItemSlotType::Hands);
  bodySlots->addSlot("Cloak", ItemSlotType::Cloak, "Cloak of protection +1");
  bodySlots->addSlot("Boots", ItemSlotType::Boots);
  bodySlots->addSlot("Belt", ItemSlotType::Belt);

  bodySlots->addSlot("Amulet", ItemSlotType::Amulet);
  bodySlots->addSlot("Left ring", ItemSlotType::LeftRing, "Ring of invisibility");
  bodySlots->addSlot("Right ring", ItemSlotType::RightRing);

  bodySlots->addSlot("Arrows", ItemSlotType::Arrows, "Arrow (40)");
  bodySlots->addSlot("Bolts", ItemSlotType::Bolts);
  bodySlots->addSlot("Bullets", ItemSlotType::Bullets);

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

  while(key.vk != TCODK_ESCAPE && !TCODConsole::isWindowClosed())
  {
    render(console);
    console.flush();

    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL,true);
  }
}

}}
