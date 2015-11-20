#include <gtest/gtest.h>
#include <engine.h>
#include <actor.h>
#include <pickable.h>

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


}

