#include "gtest/gtest.h"
#include <map.h>
#include <actor.h>

namespace amarlon {

class MapTest : public ::testing::Test
{
  virtual void SetUp()
  {
    Map::Tiles.loadTiles("data/tiles.xml");
    Actor::DB.loadActors("data/actors.xml");
    Map::Gateway.load("data/maps.xml");
  }

  virtual void TearDown()
  {
  }
};

TEST_F(MapTest, mapCreation)
{
  Map map(100, 60);

  ASSERT_EQ(map.getWidth(), (size_t)100);
  ASSERT_EQ(map.getHeight(), (size_t)60);
}

TEST_F(MapTest, mapHasTiles)
{
  Map map(100, 60);

  ASSERT_FALSE(map.isExplored(10, 5));
}

TEST_F(MapTest, mapIsInFov_notComputed)
{
  Map map(100, 60);

  ASSERT_FALSE(map.isInFov(10, 5));
}

TEST_F(MapTest, mapIsInFov_computed)
{
  Map map(100, 60);
  map.computeFov(10, 10, 5);

  ASSERT_TRUE(map.isInFov(10, 10));
}

TEST_F(MapTest, fillMap)
{
  std::string mapFill =
  "#####\n"
  "#...#\n"
  "T##.#";

  Map map(5 ,3);
  map.fill(mapFill);

  ASSERT_EQ(map.getChar(0,0), Map::Tiles.getChar(TileType::PlainWall));
  ASSERT_EQ(map.getChar(3,1), Map::Tiles.getChar(TileType::PlainFloor));
  ASSERT_EQ(map.getChar(2,2), Map::Tiles.getChar(TileType::PlainWall));
  ASSERT_EQ(map.getChar(0,2), Map::Tiles.getChar(TileType::Tree));
}

TEST_F(MapTest, getChar_Color)
{
  Map::Tiles.loadTiles("data/tiles.xml");
  std::string mapFill =
  "#####\n"
  "#...#\n"
  "T##.#";

  Map map(5 ,3);
  map.fill(mapFill);

  ASSERT_TRUE(map.getColor(0,2) == Map::Tiles.getColor(TileType::Tree));
}

TEST_F(MapTest, tilesToStr)
{
  Map::Tiles.loadTiles("data/tiles.xml");
  std::string mapFill =
  "#####\n"
  "#...#\n"
  "###.#";

  Map map(5 ,3);
  map.fill(mapFill);

  std::string dumped = map.tilesToStr();

  ASSERT_EQ(mapFill, dumped);
}

TEST_F(MapTest, tileThatBlocks)
{
  Map::Tiles.loadTiles("data/tiles.xml");
  std::string mapFill =
  "#####\n"
  "#...#\n"
  "###.#";

  Map map(5 ,3);
  map.fill(mapFill);

  EXPECT_TRUE(map.isBlocked(0,0));
  EXPECT_FALSE(map.isBlocked(3,2));
}

TEST_F(MapTest, addActor)
{
  MapPtr map = Map::Gateway.fetch(MapId::GameStart);
  ActorPtr actor = Actor::create(ActorType::HealthPotion,1,1);

  map->addActor(actor);

  auto actors = map->getActors(1,1);

  EXPECT_EQ(actors.size(), (size_t)1);
  EXPECT_TRUE( actors.front().get() == actor.get() );
}

}
