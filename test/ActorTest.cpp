#include <gtest/gtest.h>
#define private public
#include "Actor/actor.h"
#include "World/Map.h"
#include "Actor/Effects/SelfHealEffect.h"
#undef private

class ActorTest : public ::testing::Test
{
  virtual void SetUp()
  {
    Map::Tiles.loadTiles("../amarlon/tiles.xml");
    Actor::DB.loadActors("../amarlon/actors.xml");
    Map::Gateway.loadMaps("../amarlon/maps.xml");
  }

  virtual void TearDown()
  {
  }

};

TEST_F(ActorTest, actorEqual)
{
  std::shared_ptr<Actor> a1 ( new Actor(ActorType::Orc) );
  std::shared_ptr<Actor> a2 ( new Actor(ActorType::Orc) );

  ASSERT_TRUE( a1->isEqual(a2.get()) );
}

TEST_F(ActorTest, actorEqual_diferrent_id)
{
  std::shared_ptr<Actor> a1 ( new Actor(ActorType::Orc) );
  std::shared_ptr<Actor> a2 ( new Actor(ActorType::Orc) );

  a2->changeType( ActorType::Bed );

  ASSERT_FALSE( a1->isEqual(a2.get()) );
}

TEST_F(ActorTest, actorEqual_different_container)
{
  std::shared_ptr<Actor> a1 ( new Actor(ActorType::Orc) );
  std::shared_ptr<Actor> a2 ( new Actor(ActorType::Orc) );

  Container* c1 = new Container(10);
  Container* c2 = new Container(10);

  a1->setAfContainer(c1);
  a2->setAfContainer(c2);

  //same containers
  ASSERT_TRUE( c1->isEqual(c2) );

  //different slot count
  c2->setSlotCount(12);

  ASSERT_FALSE( c1->isEqual(c2) );
  ASSERT_FALSE( a1->isEqual(a2.get()) );

  //existing, same content
  c2->setSlotCount( c1->slotCount() );

  Actor* ca1 = new Actor(ActorType::HealthPotion);
  Actor* ca2 = ca1->clone();

  c1->add(ca1);
  c2->add(ca2);

  ASSERT_TRUE( c1->isEqual(c2) );
  ASSERT_TRUE( a1->isEqual(a2.get()) );

  //existing, different content
  Actor* ca1b = new Actor(ActorType::CookBook);
  Actor* ca2b = new Actor(ActorType::BootleOfWine);

  c1->add(ca1b);
  c2->add(ca2b);

  ASSERT_FALSE( c1->isEqual(c2) );
  ASSERT_FALSE( a1->isEqual(a2.get()) );

  c1->remove( ca1b );
  c2->remove( ca2b );
  delete ca1b;
  delete ca2b;

  //exisrting different content 2
  Actor* ca1c = new Actor(ActorType::CookBook);
  Actor* ca2c = ca1c->clone();

  ca1c->setAfAi( Ai::create( AiType::Monster ));
  c1->add(ca1c);
  c2->add(ca2c);

  ASSERT_FALSE( c1->isEqual(c2) );
  ASSERT_FALSE( a1->isEqual(a2.get()) );
}

TEST_F(ActorTest, actorEqual_different_openable)
{
  std::shared_ptr<Actor> a1 ( new Actor(ActorType::DoorOpen) );
  std::shared_ptr<Actor> a2 ( a1->clone() );

  ASSERT_TRUE( a1->isEqual(a2.get()) );

  a2->afOpenable()->setLockId(666);

  ASSERT_FALSE( a1->isEqual(a2.get()) );
}

TEST_F(ActorTest, actorEqual_different_pickable)
{
  std::shared_ptr<Actor> a1 ( new Actor(ActorType::HealthPotion) );
  std::shared_ptr<Actor> a2 ( a1->clone() );

  ASSERT_TRUE( a1->isEqual(a2.get()) );

  SelfHealEffect* e = dynamic_cast<SelfHealEffect*>(a1->afPickable()->getEffect());
  e->_healAmount = 666;

  ASSERT_FALSE( a1->isEqual(a2.get()) );
}

TEST_F(ActorTest, actorEqual_different_fighter)
{
  std::shared_ptr<Actor> a1 ( new Actor(ActorType::Orc) );
  std::shared_ptr<Actor> a2 ( a1->clone() );

  ASSERT_TRUE( a1->isEqual(a2.get()) );

  a1->afFighter()->_power = 666;

  ASSERT_FALSE( a1->isEqual(a2.get()) );
}
