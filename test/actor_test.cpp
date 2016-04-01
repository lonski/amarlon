#include <gtest/gtest.h>
#include <actor.h>
#include <map.h>
#include <engine.h>
#include <character_type.h>

namespace amarlon {

class ActorTest : public ::testing::Test
{
  virtual void SetUp()
  {
    Engine::instance().prologue();
    //Engine::instance().enterGame();
  }

  virtual void TearDown()
  {
    Engine::instance().epilogue();
  }

};

TEST_F(ActorTest, playerControlled)
{
  ActorPtr p = Actor::create(ActorType::Player);
  ASSERT_TRUE( p->isPlayerControlled() );
}

TEST_F(ActorTest, actorEqual)
{
  std::shared_ptr<Actor> a1 = Actor::create( ActorType::Orc );
  std::shared_ptr<Actor> a2 = Actor::create( ActorType::Orc );

  ASSERT_TRUE( *a1 == *a2 );
}

TEST_F(ActorTest, actorEqual_diferrent_id)
{
  std::shared_ptr<Actor> a1 = Actor::create( ActorType::Orc );
  std::shared_ptr<Actor> a2 = Actor::create( ActorType::Orc );

  a2->setType( ActorType::Bed );

  ASSERT_FALSE( *a1 == *a2 );
}

TEST_F(ActorTest, actorEqual_different_container)
{
  std::shared_ptr<Actor> a1 = Actor::create( ActorType::Orc );
  std::shared_ptr<Actor> a2 = Actor::create( ActorType::Orc );

  InventoryData iDsc;
  iDsc.set_slotcount( 10 );

  InventoryPtr c1 = Inventory::create(iDsc);
  InventoryPtr c2 = Inventory::create(iDsc);

  a1->insertFeature(c1);
  a2->insertFeature(c2);

  //same containers
  ASSERT_TRUE( *c1 == *c2 );

  //different slot count
  c2->setSlotCount(12);

  ASSERT_FALSE( *c1 == *c2 );
  ASSERT_FALSE( *a1 == *a2 );

  //existing, same content
  c2->setSlotCount( c1->slotCount() );

  ActorPtr ca1 = Actor::create(ActorType::HealthPotion);
  ActorPtr ca2 = ca1->clone();

  c1->add(ca1);
  c2->add(ca2);

  ASSERT_TRUE( *c1 == *c2 );
  ASSERT_TRUE( *a1 == *a2 );

  //existing, different content
  ActorPtr ca1b = Actor::create(ActorType::CookBook);
  ActorPtr ca2b = Actor::create(ActorType::BootleOfWine);

  c1->add(ca1b);
  c2->add(ca2b);

  ASSERT_FALSE( *c1 == *c2 );
  ASSERT_FALSE( *a1 == *a2 );

  c1->remove( ca1b );
  c2->remove( ca2b );

  //exisrting different content 2
  ActorPtr ca1c = Actor::create(ActorType::CookBook);
  ActorPtr ca2c = ca1c->clone();

  AiData dsc;
  dsc.set_type( (int)AiType::GenericAi );
  ca1c->insertFeature( Ai::create( dsc ));
  c1->add(ca1c);
  c2->add(ca2c);

  ASSERT_FALSE( *c1 == *c2 );
  ASSERT_FALSE( *a1 == *a2 );
}

TEST_F(ActorTest, actorEqual_different_openable)
{
  std::shared_ptr<Actor> a1 = Actor::create(ActorType::DoorOpen);
  std::shared_ptr<Actor> a2 ( a1->clone() );

  ASSERT_TRUE( *a1 == *a2 );

  a2->getFeature<Openable>()->lock();

  ASSERT_FALSE( *a1 == *a2 );
}

TEST_F(ActorTest, actorEqual_different_pickable)
{
  std::shared_ptr<Actor> a1 = Actor::create(ActorType::HealthPotion);
  std::shared_ptr<Actor> a2 ( a1->clone() );

  ASSERT_TRUE( *a1 == *a2 );

  PickablePtr p = a1->getFeature<Pickable>();
  p->setItemSlot(ItemSlotType::Amunition);

  ASSERT_FALSE( *a1 == *a2 );
}

TEST_F(ActorTest, actorEqual_different_fighter)
{
  std::shared_ptr<Actor> a1 = Actor::create( ActorType::Orc );
  std::shared_ptr<Actor> a2 ( a1->clone() );

  ASSERT_TRUE( *a1 == *a2 );

  CharacterData mobDsc;
  mobDsc.set_level(123);
  mobDsc.set_experience(666);
  mobDsc.set_charactertype( (int)CharacterType::Generic );

  a1->insertFeature( Character::create(mobDsc) );

  ASSERT_FALSE( *a1 == *a2 );
}

TEST_F(ActorTest, spilt)
{
  ActorPtr actor = Actor::create(ActorType::BootleOfWine);
  PickablePtr p = actor->getFeature<Pickable>();
  p->setAmount(5);

  ActorPtr splited = actor->getFeature<Pickable>()->spilt(2);
  PickablePtr p2 = splited->getFeature<Pickable>();

  EXPECT_EQ( p->getAmount(), 3 );
  EXPECT_EQ( p2->getAmount(), 2 );
}

}

