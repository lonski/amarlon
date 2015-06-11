#include <gtest/gtest.h>
#include "utils/utils.h"
#include "data_gateways/tile_db.h"
#include <dices.h>
#include <set>
#include <thread>
#include <experience_table.h>

namespace amarlon {

TEST(ExpDataTable, get)
{
  experience_table::getLevelData(CharacterClass::FIGHTER, 1);
}

TEST(UtilsTest, color2str)
{
  TCODColor color(255,0,0);
  std::string s = colorToStr(color);

  ASSERT_EQ(s, "ff0000");
}

TEST(UtilsTest, str2color)
{
  std::string s = "0910FF";

  TCODColor col = strToColor(s);

  EXPECT_EQ((int)col.r, (int)0x09);
  EXPECT_EQ((int)col.g, (int)0x10);
  EXPECT_EQ((int)col.b, (int)0xFF);
}

TEST(UtilsTest, loadTiles)
{
  TileDB tiles;
  tiles.loadTiles("data/tiles.xml");
}

TEST(UtilsTest, tolowers)
{
  std::string str = "Cycki";
  ASSERT_EQ(tolowers(str), "cycki");
}

TEST(UtilsTest, diceTest)
{
  std::set<int> rolls;
  for(int i=0; i<100; ++i)
  {
    int r = dices::roll(dices::D4);
    rolls.insert( r );
    std::cout << r << " ";
  }

  for ( int i=1; i<=4; ++i)
  {
    EXPECT_TRUE( rolls.find(i) != rolls.end() ) << i;
  }
}

}
