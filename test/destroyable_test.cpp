#include <gtest/gtest.h>

#define private public
#include <destroyable.h>
#include <actor.h>
#undef private
#include <engine.h>
#include <actor.pb.h>

namespace amarlon {


class DestroyableTest : public ::testing::Test
{
public:
  DestroyableTest()
  {
  }

  virtual void SetUp()
  {
    Engine::instance().prologue();
  }
  virtual void TearDown()
  {
  }

};

TEST_F(DestroyableTest, orcIsDestroyable)
{
  ActorPtr orc( Actor::create(ActorType::Orc) );

  DestroyablePtr destr = orc->getFeature<Destroyable>();

  EXPECT_TRUE( destr != nullptr );
}

TEST_F(DestroyableTest, ownerIsSet)
{
  ActorPtr orc = Actor::create(ActorType::Orc);
  DestroyablePtr destr = orc->getFeature<Destroyable>();

  ASSERT_TRUE( destr != nullptr );
  EXPECT_TRUE( destr->getOwner().lock() != nullptr );
}

TEST_F(DestroyableTest, isEqual)
{
  DestroyablePtr d1( new Destroyable );
  DestroyablePtr d2( new Destroyable );

  EXPECT_TRUE( *d1 == *d2 );

  //create description with some rule
  DestroyableData data;

  DropRule* rule = data.add_droprules();
  rule->set_actor_id( (int)ActorType::GoldCoin );
  rule->set_min(2);
  rule->set_max(6);
  rule->set_chance(1);

  //create destryable based on the description
  d1 = Destroyable::create(data);

  EXPECT_FALSE( *d1 == *d2 );

  *d2 = *d1;

  EXPECT_TRUE( *d1 == *d2 );
}

}

