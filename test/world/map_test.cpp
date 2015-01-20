#include "gtest/gtest.h"
#include <world/map.h>

namespace amarlon {

TEST(MapTest, mapCreation)
{
  Map map(100, 60);

  ASSERT_EQ(map.getWidth(), (size_t)100);
  ASSERT_EQ(map.getHeight(), (size_t)60);
}

TEST(MapTest, mapHasTiles)
{
  Map map(100, 60);

  ASSERT_FALSE(map.isExplored(10, 5));
}

TEST(MapTest, mapIsInFov_notComputed)
{
  Map map(100, 60);

  ASSERT_FALSE(map.isInFov(10, 5));
}

TEST(MapTest, mapIsInFov_computed)
{
  Map map(100, 60);
  map.computeFov(10, 10, 5);

  ASSERT_TRUE(map.isInFov(10, 10));
}

TEST(MapTest, fillMap)
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

TEST(MapTest, getChar_Color)
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

TEST(MapTest, tilesToStr)
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

TEST(MapTest, tileThatBlocks)
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

}
