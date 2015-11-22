#include <gtest/gtest.h>
#include <engine.h>
#include <actor.h>
#include <pickable.h>
#include <actor_db.h>
#include <actor_descriptions.h>
#include <pickable_description.h>

namespace amarlon {

typedef std::shared_ptr<Wearer> WearerPtr;

class PickableTest : public ::testing::Test
{
public:
  virtual void SetUp()
  {
    Engine::instance().prologue();
  }
  virtual void TearDown()
  {

  }

};

TEST_F(PickableTest, equality)
{
  PickablePtr p1 = Actor::create(ActorType::Arrow)->getFeature<Pickable>();
  PickablePtr p2 = Actor::create(ActorType::Arrow_P1)->getFeature<Pickable>();
  EXPECT_FALSE( p1->isEqual(p2) );
}

TEST_F(PickableTest, upgrade)
{
  //create regular coin
  ActorPtr gold = Actor::create(ActorType::GoldCoin);
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


}

