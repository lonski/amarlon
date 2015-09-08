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
    cfg.load("config.cfg");
    Engine::instance().prologue(&cfg);
  }
  virtual void TearDown()
  {
  }

protected:
  Configuration cfg;
};

TEST_F(MoveActionTest, actorWithoutMap)
{
  ActorPtr orc = Actor::create(ActorType::Orc);
  EXPECT_FALSE(orc->performAction( std::make_shared<MoveAction>(1, 1)));
}

}
