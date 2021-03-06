#include <gtest/gtest.h>
#include <actor.h>
#include <map.h>
#include <engine.h>
#include <actor_descriptions.h>
#include <character_type.h>
#include <module.h>

namespace amarlon {

class ActorTest : public ::testing::Test
{
  virtual void SetUp()
  {
    Engine::instance().prologue();
    Engine::instance().loadModule( Module("testing") );
  }

  virtual void TearDown()
  {
    Engine::instance().epilogue();
  }

};

TEST_F(ActorTest, playerControlled)
{
  ActorPtr p = Actor::create(1 /*Player*/);
  ASSERT_TRUE( p->isPlayerControlled() );
}

TEST_F(ActorTest, actorEqual)
{
  std::shared_ptr<Actor> a1 = Actor::create( 2 /*Orc*/ );
  std::shared_ptr<Actor> a2 = Actor::create( 2 /*Orc*/ );

  ASSERT_TRUE( *a1 == *a2 );
}

TEST_F(ActorTest, actorEqual_diferrent_id)
{
  std::shared_ptr<Actor> a1 = Actor::create( 2 /*Orc*/ );
  std::shared_ptr<Actor> a2 = Actor::create( 2 /*Orc*/ );

  a2->setType( 5 /* Bed */ );

  ASSERT_FALSE( *a1 == *a2 );
}

TEST_F(ActorTest, actorEqual_different_container)
{
  std::shared_ptr<Actor> a1 = Actor::create( 2 /*Orc*/ );
  std::shared_ptr<Actor> a2 = Actor::create( 2 /*Orc*/ );

  InventoryDescriptionPtr iDsc(new InventoryDescription);
  iDsc->maxSize = 10;

  InventoryPtr c1( new Inventory(iDsc) );
  InventoryPtr c2( new Inventory(iDsc) );

  a1->insertFeature(c1);
  a2->insertFeature(c2);

  //same containers
  ASSERT_TRUE( c1->isEqual(c2) );

  //different slot count
  c2->setSlotCount(12);

  ASSERT_FALSE( c1->isEqual(c2) );
  ASSERT_FALSE( *a1 == *a2 );

  //existing, same content
  c2->setSlotCount( c1->slotCount() );

  ActorPtr ca1 = Actor::create( 13 /*HealthPotion*/);
  ActorPtr ca2 = ca1->clone();

  c1->add(ca1);
  c2->add(ca2);

  ASSERT_TRUE( c1->isEqual(c2) );
  ASSERT_TRUE( *a1 == *a2 );

  //existing, different content
  ActorPtr ca1b = Actor::create(14 /*CookBook*/);
  ActorPtr ca2b = Actor::create(12 /*BootleOfWine*/);

  c1->add(ca1b);
  c2->add(ca2b);

  ASSERT_FALSE( c1->isEqual(c2) );
  ASSERT_FALSE( *a1 == *a2 );

  c1->remove( ca1b );
  c2->remove( ca2b );

  //exisrting different content 2
  ActorPtr ca1c = Actor::create(14 /*CookBook*/);
  ActorPtr ca2c = ca1c->clone();

  AiDescriptionPtr dsc = std::make_shared<AiDescription>();
  dsc->type = (int)AiType::GenericAi;
  ca1c->insertFeature( Ai::create( dsc ));
  c1->add(ca1c);
  c2->add(ca2c);

  ASSERT_FALSE( c1->isEqual(c2) );
  ASSERT_FALSE( *a1 == *a2 );
}

TEST_F(ActorTest, actorEqual_different_openable)
{
  std::shared_ptr<Actor> a1 = Actor::create( 4 /*DoorOpen*/);
  std::shared_ptr<Actor> a2 ( a1->clone() );

  ASSERT_TRUE( *a1 == *a2 );

  a2->getFeature<Openable>()->lock();

  ASSERT_FALSE( *a1 == *a2 );
}

TEST_F(ActorTest, actorEqual_different_pickable)
{
  std::shared_ptr<Actor> a1 = Actor::create(13 /*HealthPotion*/);
  std::shared_ptr<Actor> a2 ( a1->clone() );

  ASSERT_TRUE( *a1 == *a2 );

  PickablePtr p = a1->getFeature<Pickable>();
  p->setItemSlot(ItemSlotType::Amunition);

  ASSERT_FALSE( *a1 == *a2 );
}

TEST_F(ActorTest, actorEqual_different_fighter)
{
  std::shared_ptr<Actor> a1 = Actor::create( 2 /*Orc*/ );
  std::shared_ptr<Actor> a2 ( a1->clone() );

  ASSERT_TRUE( *a1 == *a2 );

  CharacterDescriptionPtr mobDsc(new CharacterDescription );
  mobDsc->level = 123;
  mobDsc->experience = 666;
  mobDsc->type = (int)CharacterType::Generic;

  a1->insertFeature( Character::create(mobDsc) );

  ASSERT_FALSE( *a1 == *a2 );
}

TEST_F(ActorTest, spilt)
{
  ActorPtr actor = Actor::create(12 /*BootleOfWine*/);
  PickablePtr p = actor->getFeature<Pickable>();
  p->setAmount(5);

  ActorPtr splited = actor->getFeature<Pickable>()->spilt(2);
  PickablePtr p2 = splited->getFeature<Pickable>();

  EXPECT_EQ( p->getAmount(), 3 );
  EXPECT_EQ( p2->getAmount(), 2 );
}

}

