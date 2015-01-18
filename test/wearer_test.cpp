#include <gtest/gtest.h>

#define private public
#include "actor/actor.h"
#include "actor_features/container.h"
#include "wearer/wearer.h"
#undef private

namespace amarlon {

typedef std::shared_ptr<Wearer> WearerPtr;

class WearerTest : public ::testing::Test
{
public:
  virtual void SetUp()
  {
    Actor::DB.loadActors("data/actors.xml");

    WearerDescription dsc;
    dsc.itemSlots.push_back(ItemSlotType::Armor);
    dsc.itemSlots.push_back(ItemSlotType::Boots);

    wearer.reset( Wearer::create(&dsc) );
  }
  virtual void TearDown()
  {

  }

protected:
  WearerPtr wearer;

};

TEST_F(WearerTest, loadsSlots_from_description)
{
  EXPECT_TRUE( wearer->hasSlot(ItemSlotType::Armor) );
  EXPECT_TRUE( wearer->hasSlot(ItemSlotType::Boots) );

  EXPECT_FALSE( wearer->hasSlot(ItemSlotType::Helmet) );
}

TEST_F(WearerTest, equip_item)
{
  //not equipped
  ASSERT_FALSE( wearer->isEquipped(ItemSlotType::Armor) );

  Actor* clothArmor = new Actor( ActorType::LinenClothes );

  //equip and check if equipped correctly
  EXPECT_TRUE( wearer->hasSlot(ItemSlotType::Armor) );

  ASSERT_TRUE( wearer->equip(clothArmor) );
  ASSERT_TRUE( wearer->isEquipped(ItemSlotType::Armor) );
  ASSERT_EQ( wearer->equipped(ItemSlotType::Armor), clothArmor );
  ASSERT_FALSE( wearer->isEquipped(ItemSlotType::Boots) );

  //try to over-equip
  Actor* overeq = new Actor(ActorType::LinenClothes);
  EXPECT_FALSE( wearer->equip(overeq) );
  EXPECT_EQ( wearer->equipped(ItemSlotType::Armor), clothArmor );

  delete overeq;
  overeq = nullptr;
}

TEST_F(WearerTest, unequip_item)
{
  //try to unequip not equipped
  ASSERT_EQ( wearer->unequip(ItemSlotType::Armor ), nullptr );

  //equip and then unequip
  Actor* boots = new Actor( ActorType::LeatherBoots );
  ASSERT_TRUE( wearer->equip(boots) );
  Actor* unequipped = wearer->unequip(ItemSlotType::Boots);

  //check if unequipped correctly
  EXPECT_EQ(unequipped, boots);
  EXPECT_FALSE(wearer->isEquipped(ItemSlotType::Boots));
  EXPECT_EQ( wearer->equipped(ItemSlotType::Boots), nullptr);

  delete boots;
}

TEST_F(WearerTest, clone_wearer)
{
  WearerDescription dsc;
  dsc.eqItems.maxSize = 2;
  dsc.itemSlots.push_back(ItemSlotType::LeftRing);
  dsc.itemSlots.push_back(ItemSlotType::Offhand);

  WearerPtr w1 ( Wearer::create(&dsc) );
  WearerPtr wcloned( dynamic_cast<Wearer*>(w1->clone()) );

  ASSERT_TRUE( wcloned->_equippedItems->isEqual( w1->_equippedItems.get() ) );
  for(int i = (int)ItemSlotType::Null; i != (int)ItemSlotType::End; ++i)
  {
    ItemSlotType slot = (ItemSlotType)i;
    ASSERT_EQ( wcloned->hasSlot(slot), w1->hasSlot(slot) );
  }

  ASSERT_TRUE( wcloned->isEqual(w1.get()) );
}

TEST_F(WearerTest, compare_test)
{
  WearerPtr w1 ( new Wearer );
  WearerPtr w2 ( new Wearer );

  ASSERT_TRUE( w1->isEqual(w2.get()) );

  //compare by slots
  w1->_itemSlots[ ItemSlotType::Armor ] = nullptr;
  ASSERT_FALSE( w1->isEqual(w2.get()) );

  WearerDescription dsc;
  dsc.itemSlots.push_back(ItemSlotType::Armor);
  dsc.itemSlots.push_back(ItemSlotType::Boots);
  dsc.eqItems.maxSize = 2;

  w1.reset( Wearer::create(&dsc) );
  w2.reset( Wearer::create(&dsc) );

  //compare by equip - 1. one equipped, second null
  Actor* w1armor = new Actor( ActorType::LinenClothes );

  ASSERT_TRUE( w1->equip(w1armor) );
  ASSERT_FALSE( w1->isEqual( w2.get() ) );

  //compare by equip - 2. both equipped same
  Actor* w2armor = new Actor( ActorType::LinenClothes );
  ASSERT_TRUE( w2->equip(w2armor) );
  ASSERT_TRUE( w1->isEqual( w2.get() ) );

  //compare by equip - 3. both equipped different
  Actor* w2boots = new Actor( ActorType::LeatherBoots );
  ASSERT_TRUE( w2->equip(w2boots) );
  ASSERT_FALSE( w1->isEqual( w2.get() ) );

}

}
