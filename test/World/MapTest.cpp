#include "gtest/gtest.h"
#include <World/map.h>

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

  ASSERT_EQ(map.getChar(0,0), '#');
  ASSERT_EQ(map.getChar(3,1), '.');
  ASSERT_EQ(map.getChar(2,2), '#');
  ASSERT_EQ(map.getChar(0,2), 'T');
}

TEST(MapTest, getChar_Color)
{
  std::string mapFill =
  "#####\n"
  "#...#\n"
  "T##.#";

  Map map(5 ,3);
  map.fill(mapFill);

  ASSERT_TRUE(map.getColor(0,2) == TCODColor::darkerGreen);
}

TEST(MapTest, tilesToStr)
{
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
  std::string mapFill =
  "#####\n"
  "#...#\n"
  "###.#";

  Map map(5 ,3);
  map.fill(mapFill);

  EXPECT_TRUE(map.isBlocked(0,0));
  EXPECT_FALSE(map.isBlocked(3,2));
}
