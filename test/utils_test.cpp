#include <gtest/gtest.h>
#include "utils/utils.h"
#include "data_gateways/tile_db.h"
#include <dices.h>
#include <set>
#include <thread>
#include <experience_table.h>
#include <damage.h>

namespace amarlon {


TEST(DamageTest, parseValid)
{
  std::string str("3d4+2#3");
  Damage dmg(str);

  ASSERT_EQ(dmg.value, 2);
  ASSERT_EQ(dmg.dice, dices::D4);
  ASSERT_EQ(dmg.diceCount, 3);
  ASSERT_EQ(dmg.type, DamageType::Fire );
}

TEST(DamageTest, parseInvalid)
{
  std::string str("3d4#3");
  Damage dmg(str);

  ASSERT_EQ(dmg, Damage());
}

TEST(DamageTest, serialize)
{
  Damage d(4, 2, dices::D6, DamageType::Lighting);
  ASSERT_EQ( "2d6+4#5", std::string(d) );
}

TEST(ExpDataTable, get)
{
  Experience::getLevelData(CharacterClass::Fighter, 1);
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
  tiles.load("data/tiles.xml");
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
