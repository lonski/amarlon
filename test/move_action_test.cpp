#include <gtest/gtest.h>
#include <actor.h>
#include <move_action.h>
#include <map.h>
#include <configuration.h>
#include <engine.h>

namespace amarlon {

class MoveActionTest : public ::testing::Test
{
public:
  MoveActionTest()
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

TEST_F(MoveActionTest, actorWithoutMap)
{
  ActorPtr orc = Actor::create(ActorType::Orc);
  EXPECT_FALSE(orc->performAction(new MoveAction(1, 1)) == ActorActionResult::Ok);
}

}

