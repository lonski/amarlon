#include <gtest/gtest.h>
#include <amenu.h>
#include <alabel_menu_item.h>
#include <aslot_menu_item.h>

namespace amarlon { namespace gui {

class AMenuTest : public ::testing::Test
{
protected:
  AMenu _menu;

};

TEST_F(AMenuTest, addItem)
{
  ASSERT_EQ(_menu.getItemCount(), (size_t)0);

  _menu.addItem( AMenuItemPtr(new ALabelMenuItem) );
  ASSERT_EQ(_menu.getItemCount(), (size_t)1);

  _menu.addItem( AMenuItemPtr(new ASlotMenuItem) );
  ASSERT_EQ(_menu.getItemCount(), (size_t)2);
}

TEST_F(AMenuTest, removeItem)
{
  AMenuItemPtr item(new ALabelMenuItem);

  _menu.addItem( item );
  ASSERT_EQ(_menu.getItemCount(), (size_t)1);

  _menu.removeItem( item );
  ASSERT_EQ(_menu.getItemCount(), (size_t)0);
}

TEST_F(AMenuTest, getHeight_noItems)
{
  ASSERT_EQ( _menu.getHeight(), 0 );
}

TEST_F(AMenuTest, getHeight_labelItems)
{
  AMenuItemPtr item(new ALabelMenuItem);
  _menu.addItem( item );

  ASSERT_EQ( _menu.getHeight(), item->getHeight() );

  _menu.addItem( AMenuItemPtr(new ALabelMenuItem) );

  ASSERT_EQ( _menu.getHeight(), item->getHeight()*2 );
}

TEST_F(AMenuTest, getHeight_differentItems)
{
  AMenuItemPtr item1(new ALabelMenuItem);
  AMenuItemPtr item2(new ASlotMenuItem);

  _menu.addItem( item1 );
  _menu.addItem( item2 );

  ASSERT_EQ( _menu.getHeight(), item1->getHeight() + item2->getHeight() );
}

TEST_F(AMenuTest, getSelectedItem_noItems)
{
  auto ptr = _menu.getSelectedItem();
  ASSERT_FALSE(ptr);
}

TEST_F(AMenuTest, selectNext)
{
  AMenuItemPtr item1(new ALabelMenuItem);
  AMenuItemPtr item2(new ASlotMenuItem);
  AMenuItemPtr item3(new ASlotMenuItem);

  _menu.addItem(item1);
  _menu.addItem(item2);
  _menu.addItem(item3);

  //none selected, should select first
  _menu.selectNext();
  ASSERT_TRUE(item1->isSelected());
  ASSERT_FALSE(item2->isSelected());
  ASSERT_FALSE(item3->isSelected());

  _menu.selectNext();
  ASSERT_FALSE(item1->isSelected());
  ASSERT_TRUE(item2->isSelected());
  ASSERT_FALSE(item3->isSelected());

  _menu.selectNext();
  ASSERT_FALSE(item1->isSelected());
  ASSERT_FALSE(item2->isSelected());
  ASSERT_TRUE(item3->isSelected());

  _menu.selectNext();
  ASSERT_TRUE(item1->isSelected());
  ASSERT_FALSE(item2->isSelected());
  ASSERT_FALSE(item3->isSelected());

}

TEST_F(AMenuTest, selecPrevious)
{
  AMenuItemPtr item1(new ALabelMenuItem);
  AMenuItemPtr item2(new ASlotMenuItem);
  AMenuItemPtr item3(new ASlotMenuItem);

  _menu.addItem(item1);
  _menu.addItem(item2);
  _menu.addItem(item3);

  //none selected, should select first
  _menu.selectPrevious();
  ASSERT_TRUE(item1->isSelected());
  ASSERT_FALSE(item2->isSelected());
  ASSERT_FALSE(item3->isSelected());

  _menu.selectPrevious();
  ASSERT_FALSE(item1->isSelected());
  ASSERT_FALSE(item2->isSelected());
  ASSERT_TRUE(item3->isSelected());

  _menu.selectPrevious();
  ASSERT_FALSE(item1->isSelected());
  ASSERT_TRUE(item2->isSelected());
  ASSERT_FALSE(item3->isSelected());

}

TEST_F(AMenuTest, getWidth_noItems)
{
  ASSERT_EQ(_menu.getWidth(), 0);
}

TEST_F(AMenuTest, getWidth)
{
  AMenuItemPtr item1(new ALabelMenuItem);
  AMenuItemPtr item2(new ASlotMenuItem);

  _menu.addItem(item1);
  _menu.addItem(item2);

  ASSERT_EQ(_menu.getWidth(), std::max(item1->getWidth(), item2->getWidth()) );
}


}}

