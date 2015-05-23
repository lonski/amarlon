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
  int x = orc->getX();
  int y = orc->getY();

  int dx(1);
  int dy(-2);

  EXPECT_TRUE(orc->performAction( std::make_shared<MoveAction>(dx, dy)));
  EXPECT_EQ(orc->getX(), x+dx);
  EXPECT_EQ(orc->getY(), y+dy);
}

TEST_F(MoveActionTest, actorOnMap_notBlocked)
{
  MapPtr map = std::make_shared<Map>(5 ,3);
  map->fill("#####\n"
            "#...#\n"
            "###.#");

  ActorPtr orc = Actor::create(ActorType::Orc, 2, 1);

  int x = orc->getX();
  int y = orc->getY();

  int dx(1);
  int dy(0);

  map->addActor(orc);

  EXPECT_TRUE(orc->performAction( std::make_shared<MoveAction>(dx, dy)));
  EXPECT_EQ(orc->getX(), x+dx);
  EXPECT_EQ(orc->getY(), y+dy);
}

TEST_F(MoveActionTest, actorOnMap_blockedPath)
{
  MapPtr map = std::make_shared<Map>(5 ,3);
  map->fill("#####\n"
            "#...#\n"
            "###.#");

  ActorPtr orc = Actor::create(ActorType::Orc, 2, 1);

  int x = orc->getX();
  int y = orc->getY();

  int dx(2);
  int dy(1);

  map->addActor(orc);

  EXPECT_FALSE(orc->performAction( std::make_shared<MoveAction>(dx, dy)));
  EXPECT_EQ(orc->getX(), x);
  EXPECT_EQ(orc->getY(), y);
}

}
