#include <gtest/gtest.h>

#define private public
#include <destroyable.h>
#include <actor.h>
#undef private
#include <engine.h>
#include <actor_descriptions.h>

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

  EXPECT_TRUE( d1->isEqual(d2) );

  //create description with some rule
  DestroyableDescriptionPtr dsc( new DestroyableDescription);

  DropRule rule;
  rule.dropActorId = ActorType::GoldCoin;
  rule.amountMin = 2;
  rule.amountMax = 6;
  rule.chance = 1;

  dsc->dropRules.push_back( rule );

  //create destryable based on the description
  d1 = std::dynamic_pointer_cast<Destroyable>( ActorFeature::create(Destroyable::featureType, dsc) );

  EXPECT_FALSE( d1->isEqual(d2) );

  //add modified rule
  DestroyableDescriptionPtr dsc2( new DestroyableDescription);

  DropRule rule2;
  rule2.dropActorId = ActorType::GoldCoin;
  rule2.amountMin = 1;
  rule2.amountMax = 3;
  rule2.chance = 4;

  dsc2->dropRules.push_back( rule2 );

  d2->_dropRules.push_back( rule2 );
  EXPECT_FALSE( d1->isEqual(d2) );

  //add the same rule to the second destroyable
  d2->_dropRules.clear();
  d2->_dropRules.push_back( rule );
  EXPECT_TRUE( d1->isEqual(d2) );
}

}

