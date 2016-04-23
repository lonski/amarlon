#include <gtest/gtest.h>
#include <engine.h>
#include <actor.h>
#include <pickable.h>
#include <actor_db.h>
#include <actor_descriptions.h>
#include <pickable_description.h>
#include <module.h>
#include <use_action.h>
#include <pickup_action.h>

namespace amarlon {

typedef std::shared_ptr<Wearer> WearerPtr;

class PickableTest : public ::testing::Test
{
public:
  virtual void SetUp()
  {
    Engine::instance().prologue();
    Engine::instance().loadModule( Module("testing") );
  }
  virtual void TearDown()
  {

  }

};

TEST_F(PickableTest, equality)
{
  PickablePtr p1 = Actor::create(30)->getFeature<Pickable>();
  PickablePtr p2 = Actor::create(34)->getFeature<Pickable>();
  EXPECT_FALSE( p1->isEqual(p2) );
}

TEST_F(PickableTest, upgrade)
{
  //create regular coin
  ActorPtr gold = Actor::create(22);
  ASSERT_TRUE(gold != nullptr );
  PickablePtr coin = gold->getFeature<Pickable>();
  PickablePtr originalCoin
      = std::dynamic_pointer_cast<Pickable>(coin->clone());
  ASSERT_TRUE(coin != nullptr );
  ASSERT_TRUE( coin->getItemSlot() == ItemSlotType::Null );

  //create pickable dsc with only amount changed
  PickableDescriptionPtr pDsc(new PickableDescription);
  pDsc->itemSlot = (int)ItemSlotType::Armor;

  //and apply it to the coin
  coin->upgrade( pDsc );

  //amount shoud change
  ASSERT_TRUE(coin->getItemSlot() == ItemSlotType::Armor );
  ASSERT_FALSE( coin->isEqual(originalCoin) );

  //after amount change still the same coin
  coin->setItemSlot( originalCoin->getItemSlot() );
  ASSERT_TRUE( coin->isEqual(originalCoin) );
}

TEST_F(PickableTest, dailyUse)
{
  ActorPtr potion = Actor::create(13);
  ASSERT_TRUE( potion != nullptr );

  PickablePtr p = potion->getFeature<Pickable>();
  p->setUseType( UseType::DailyUse );
  p->setUsesCount( 1 );

  ASSERT_TRUE( p->isUsable() );
  ASSERT_EQ( p->getUsesCount(), 1 );

  //Create an owner of this item
  ActorPtr orc = Actor::create(2);

  ASSERT_EQ( orc->performAction( new PickUpAction(potion) ),
             ActorActionResult::Ok );

  //Use item
  ASSERT_EQ( orc->performAction( new UseAction(orc, potion) ),
             ActorActionResult::Ok );

  //Check if item is still in inventory
  bool itemPresent = false;
  InventoryPtr inv = orc->getFeature<Inventory>();
  for ( ActorPtr a : inv->items() )
  {
    if ( a.get() == potion.get() )
    {
      itemPresent = true;
      break;
    }
  }

  ASSERT_TRUE(itemPresent);

  //No charges, but still is usable
  ASSERT_EQ( p->getUsesCount(), 0 );
  ASSERT_TRUE( p->isUsable() );

  //Tick a day to recharge
  potion->tickDay();

  //Item should be charged and rady to use
  ASSERT_EQ( p->getUsesCount(), 1 );
  ASSERT_EQ( orc->performAction( new UseAction(orc, potion) ),
             ActorActionResult::Ok );


}

}

