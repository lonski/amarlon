#include <gtest/gtest.h>
#include <engine.h>
#include <module.h>

#define private public
#include <treasure_generator.h>
#include <magic_weapon_generator.h>
#undef private

namespace amarlon {

typedef std::shared_ptr<Wearer> WearerPtr;

class TreasureGeneratorTest : public ::testing::Test
{
public:
  virtual void SetUp()
  {
    Engine::instance().prologue();
    Engine::instance().loadModule( Module("testing") );
  }
  virtual void TearDown()
  {

  }

protected:
  TreasureGenerator _generator;
  MagicWeaponGenerator _wpnGenerator;

};

class GetMeleeDamageBonusTest : public TreasureGeneratorTest
                         , public ::testing::WithParamInterface< std::pair<int, std::pair<int,int> > >
{
};

INSTANTIATE_TEST_CASE_P(MeleeDamageBonus,
                        GetMeleeDamageBonusTest,
                        ::testing::Values( std::make_pair(58,  std::make_pair(5,0) ),
                                           std::make_pair(100, std::make_pair(-2,0) ),
                                           std::make_pair(99,  std::make_pair(-2,0) ),
                                           std::make_pair(80,  std::make_pair(1,3) ),
                                           std::make_pair(60,  std::make_pair(1,2) ),
                                           std::make_pair(57,  std::make_pair(4,0) ),
                                           std::make_pair(56,  std::make_pair(4,0) ),
                                           std::make_pair(42,  std::make_pair(2,0) ),
                                           std::make_pair(50,  std::make_pair(2,0) ),
                                           std::make_pair(40,  std::make_pair(1,0) ),
                                           std::make_pair(0,   std::make_pair(1,0) ),
                                           std::make_pair(86,  std::make_pair(0,0) ),
                                           std::make_pair(90,  std::make_pair(0,0) ),
                                           std::make_pair(95,  std::make_pair(0,0) )
                                           ));

TEST_P(GetMeleeDamageBonusTest, getMeleeDamageBonus)
{
  ASSERT_EQ( _wpnGenerator.getMeleeDamageBonus(GetParam().first), GetParam().second);
}

class GetRangedDamageBonusTest : public TreasureGeneratorTest
                               , public ::testing::WithParamInterface< std::pair<int, std::pair<int,int> > >
{
};

INSTANTIATE_TEST_CASE_P(RangedDamageBonus,
                        GetRangedDamageBonusTest,
                        ::testing::Values( std::make_pair(100, std::make_pair(-2,0) ),
                                           std::make_pair(99,  std::make_pair(-2,0) ),
                                           std::make_pair(98,  std::make_pair(-1,0) ),
                                           std::make_pair(97,  std::make_pair(-1,0) ),
                                           std::make_pair(85,  std::make_pair(1,3) ),
                                           std::make_pair(70,  std::make_pair(1,2) ),
                                           std::make_pair(64,  std::make_pair(3,0) ),
                                           std::make_pair(61,  std::make_pair(3,0) ),
                                           std::make_pair(59,  std::make_pair(3,0) ),
                                           std::make_pair(47,  std::make_pair(2,0) ),
                                           std::make_pair(55,  std::make_pair(2,0) )
                                           ));

TEST_P(GetRangedDamageBonusTest, getRangedDamageBonus)
{
  ASSERT_EQ( _wpnGenerator.getRangedDamageBonus(GetParam().first), GetParam().second);
}
}
