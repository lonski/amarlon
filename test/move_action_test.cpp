#include <gtest/gtest.h>
#include <actor.h>
#include <move_action.h>
#include <map.h>

namespace amarlon {

class MoveActionTest : public ::testing::Test
{
public:
  MoveActionTest()
  {
  }

  virtual void SetUp()
  {
    Actor::DB.loadActors("data/actors.xml");
    Map::Tiles.loadTiles("data/tiles.xml");
  }
  virtual void TearDown()
  {
  }

};

TEST_F(MoveActionTest, actorWithoutMap)
{
  ActorPtr orc = Actor::create(ActorType::Orc);
  EXPECT_FALSE(orc->performAction( std::make_shared<MoveAction>(1, 1)));
}

}
