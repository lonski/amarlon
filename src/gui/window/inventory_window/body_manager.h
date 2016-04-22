#ifndef BODY_MANAGER_H
#define BODY_MANAGER_H

#include <memory>
#include <string>
#include <item_slot_type.h>
#include <asub_panel.h>
#include <amenu.h>

namespace amarlon {
  class Actor;
namespace gui {

class ASlotMenuItem;
typedef std::shared_ptr<ASlotMenuItem> ASlotMenuItemPtr;

class BodyManager : public ASubPanel
{
public:  
  BodyManager(int w, int h);

  void manage();
  void fillBodySlots();
  void selectNext();
  void selectPrevious();
  void activate();
  void deactivate();
  
private:
  AMenuPtr _bodyMenu;

  ActorPtr chooseItemToEquip(ItemSlotType slot);
  bool equipItem(ActorPtr toEquip);
  std::vector<ActorPtr> getEquipableItemsList(ItemSlotType slot);
  bool unequipItem(ItemSlotType slot);
  std::string getSlotValueForItem(ActorPtr item);
  void applySlotColor(ItemSlotType slot, ASlotMenuItemPtr itemSlot);

};

typedef std::shared_ptr<BodyManager> BodyManagerPtr;

}}

#endif // BODY_MANAGER_H
