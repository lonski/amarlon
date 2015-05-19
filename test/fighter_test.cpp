#include <gtest/gtest.h>
#include <actor.h>
#include "mock/map_mock.h"

namespace amarlon {

using ::testing::_;

class FighterTest : public ::testing::Test
{
public:
  FighterTest()
  {
  }

  virtual void SetUp()
  {
    Actor::DB.loadActors("data/actors.xml");

    FighterDescriptionPtr dsc( new FighterDescription );
    dsc->maxHp = 10;
    dsc->power = 2;

    fighter = Fighter::create(dsc);
  }
  virtual void TearDown()
  {
  }

protected:
  FighterPtr fighter;
  MapMock mapMock;


};

TEST_F(FighterTest, statsCheck)
{
  EXPECT_EQ(fighter->getHp(), 10);
  EXPECT_EQ(fighter->getPower(), 2);
}

TEST_F(FighterTest, heal)
{
  fighter->setHp(2);
  EXPECT_EQ(fighter->getHp(), 2);

  //heal less than 100%
  EXPECT_EQ(fighter->heal(5), 5);
  EXPECT_EQ(fighter->getHp(), 7);

  //overheal
  EXPECT_EQ(fighter->heal(5), 3);
  EXPECT_EQ(fighter->getHp(), 10);
}

TEST_F(FighterTest, die)
{
  EXPECT_TRUE(fighter->isAlive());
  fighter->die();
  EXPECT_FALSE(fighter->isAlive());
  EXPECT_EQ(fighter->getHp(), 0);
}

TEST_F(FighterTest, drpItemsOndie)
{
  //create an orc
  ActorPtr orc( Actor::create(ActorType::Orc, 0,0, &mapMock) );

  //insert some item to inventory
  ContainerPtr inv = orc->getFeature<Container>();
  inv->add( Actor::create(ActorType::CookBook) );

  //kill actor
  EXPECT_CALL(mapMock, addActor(_));
  orc->getFeature<Fighter>()->die();


}

}
