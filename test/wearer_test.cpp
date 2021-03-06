#include <gtest/gtest.h>

#define private public
#include <actor.h>
#include <wearer.h>
#undef private
#include <engine.h>
#include <actor_descriptions.h>
#include <actor_container.h>
#include <module.h>
#include <race.h>

namespace amarlon {

typedef std::shared_ptr<Wearer> WearerPtr;

class WearerTest : public ::testing::Test
{
public:
  virtual void SetUp()
  {
    Engine::instance().prologue();
    Engine::instance().loadModule( Module("testing") );

    WearerDescriptionPtr dsc(new WearerDescription);
    dsc->itemSlots.push_back((int)ItemSlotType::Armor);
    dsc->itemSlots.push_back((int)ItemSlotType::Boots);

    wearer = Wearer::create(dsc);
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
  ActorPtr clothArmor = Actor::create( 20 /*LeatherArmor*/ );

  //equip and check if equipped correctly
  EXPECT_TRUE( wearer->hasSlot(ItemSlotType::Armor) );
  ASSERT_TRUE( wearer->equip(clothArmor) );
  ASSERT_TRUE( wearer->isEquipped(ItemSlotType::Armor) );
  ASSERT_EQ( wearer->equipped(ItemSlotType::Armor), clothArmor );
  ASSERT_FALSE( wearer->isEquipped(ItemSlotType::Boots) );

  //try to over-equip
  ActorPtr overeq = Actor::create( 20 /*LeatherArmor*/);
  EXPECT_FALSE( wearer->equip(overeq) );
  EXPECT_EQ( wearer->equipped(ItemSlotType::Armor), clothArmor );
}

TEST_F(WearerTest, unequip_item)
{
  //try to unequip not equipped
  ASSERT_EQ( wearer->unequip(ItemSlotType::Armor ), nullptr );

  //equip and then unequip
  ActorPtr boots = Actor::create( 18 /*LeatherBoots*/ );
  ASSERT_TRUE( wearer->equip(boots) );
  ActorPtr unequipped = wearer->unequip(ItemSlotType::Boots);

  //check if unequipped correctly
  EXPECT_EQ(unequipped, boots);
  EXPECT_FALSE(wearer->isEquipped(ItemSlotType::Boots));
  EXPECT_EQ( wearer->equipped(ItemSlotType::Boots), nullptr);
}

TEST_F(WearerTest, clone_wearer)
{
  WearerDescriptionPtr dsc(new WearerDescription);
  dsc->itemSlots.push_back((int)ItemSlotType::LeftRing);
  dsc->itemSlots.push_back((int)ItemSlotType::Offhand);

  WearerPtr w1 = Wearer::create(dsc);
  WearerPtr wcloned = std::dynamic_pointer_cast<Wearer>(w1->clone());

  ASSERT_TRUE( wcloned->_equippedItems->size() ==  w1->_equippedItems->size() );
  for (auto slot : ItemSlotType())
  {    
    ASSERT_EQ( wcloned->hasSlot(slot), w1->hasSlot(slot) );
  }

  ASSERT_TRUE( wcloned->isEqual(w1) );
}

TEST_F(WearerTest, compare_test)
{
  WearerPtr w1 ( new Wearer );
  WearerPtr w2 ( new Wearer );

  ASSERT_TRUE( w1->isEqual(w2) );

  //compare by slots
  w1->_itemSlots[ ItemSlotType::Armor ] = std::make_pair(nullptr, false);
  ASSERT_FALSE( w1->isEqual(w2) );

  WearerDescriptionPtr dsc(new WearerDescription);
  dsc->itemSlots.push_back((int)ItemSlotType::Armor);
  dsc->itemSlots.push_back((int)ItemSlotType::Boots);

  w1 = Wearer::create(dsc);
  w2 = Wearer::create(dsc);

  //compare by equip - 1. one equipped, second null
  ActorPtr w1armor= Actor::create( 20 );

  ASSERT_TRUE( w1->equip(w1armor) );
  ASSERT_FALSE( w1->isEqual( w2 ) );

  //compare by equip - 2. both equipped same
  ActorPtr w2armor= Actor::create( 20);
  ASSERT_TRUE( w2->equip(w2armor) );
  ASSERT_TRUE( w1->isEqual( w2 ) );

  //compare by equip - 3. both equipped different
  ActorPtr w2boots = Actor::create( 18 );
  ASSERT_TRUE( w2->equip(w2boots) );
  ASSERT_FALSE( w1->isEqual( w2 ) );

}

}

