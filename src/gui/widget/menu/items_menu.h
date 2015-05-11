#ifndef ITEMS_MENU_H
#define ITEMS_MENU_H

#include <algorithm>
#include "gui/widget/menu/menu.h"
#include "actor/actor.h"

namespace amarlon { namespace gui {

class ItemsMenu : public Menu
{
public:
  ItemsMenu(const int &width = 50, const int &height = 1);

  template<typename MenuItem_t>
  std::map<int, Actor *> fillWithItems(const std::vector<Actor *>& items)
  {
    std::map<int, Actor*> mappedItems;
    int id = -1;

    clear();

    std::for_each(items.begin(), items.end(), [&](Actor* i)
    {
      Pickable* item = i->getFeature<Pickable>();
      assert( item );

      std::string category = PickableCategory2Str( item->getCategory() );
      std::string name = i->getName();

      if ( item->getAmount() > 1 && item->isStackable() )
      {
        name += " (" + std::to_string( item->getAmount() ) + ")";
      }

      std::shared_ptr<MenuItem_t> newItem( new MenuItem_t );
      newItem->setValue( name );
      newItem->setProperty<std::string>("category", category);
      newItem->setProperty<int>("id", ++id);

      addItem(newItem);

      mappedItems.insert( std::make_pair(id, i) );
    });

    return mappedItems;
  }

};

typedef std::shared_ptr<ItemsMenu> ItemsMenuPtr;

}}

#endif // ITEMS_MENU_H
