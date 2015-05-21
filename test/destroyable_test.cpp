#include <gtest/gtest.h>
#include <actor.h>

namespace amarlon {


class DestroyableTest : public ::testing::Test
{
public:
  DestroyableTest()
  {
  }

  virtual void SetUp()
  {
    Actor::DB.loadActors("data/actors.xml");
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

}
