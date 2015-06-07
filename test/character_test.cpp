#include <gtest/gtest.h>
#include <actor.h>
#include "mock/map_mock.h"

namespace amarlon {

//using ::testing::_;

//class CharacterTest : public ::testing::Test
//{
//public:
//  CharacterTest()
//    : mapMock( new MapMock )
//  {
//  }

//  virtual void SetUp()
//  {
//    Actor::DB.loadActors("data/actors.xml");

//    CharacterDescriptionPtr dsc( new CharacterDescription );
//    dsc->maxHp = 10;
//    dsc->power = 2;

//    fighter = Character::create(dsc);
//  }
//  virtual void TearDown()
//  {
//  }

//protected:
//  CharacterPtr fighter;
//  std::shared_ptr<MapMock> mapMock;


//};

//TEST_F(CharacterTest, statsCheck)
//{
//  EXPECT_EQ(fighter->getHp(), 10);
//  EXPECT_EQ(fighter->getPower(), 2);
//}

//TEST_F(CharacterTest, heal)
//{
//  fighter->setHp(2);
//  EXPECT_EQ(fighter->getHp(), 2);

//  //heal less than 100%
//  EXPECT_EQ(fighter->heal(5), 5);
//  EXPECT_EQ(fighter->getHp(), 7);

//  //overheal
//  EXPECT_EQ(fighter->heal(5), 3);
//  EXPECT_EQ(fighter->getHp(), 10);
//}

//TEST_F(CharacterTest, die)
//{
//  EXPECT_TRUE(fighter->isAlive());
//  fighter->die();
//  EXPECT_FALSE(fighter->isAlive());
//  EXPECT_EQ(fighter->getHp(), 0);
//}

//void clearInventory(ActorPtr actor)
//{
//  ContainerPtr inv = actor->getFeature<Container>();
//  ASSERT_TRUE( inv != nullptr );
//  for ( auto i : inv->content() )
//    inv->remove(i);
//}

//void clearBody(ActorPtr actor)
//{
//  WearerPtr wearer = actor->getFeature<Wearer>();
//  ASSERT_TRUE( wearer != nullptr );
//  for ( auto s : ItemSlotType() )
//    wearer->unequip(s);
//}

//void clearDropRules(ActorPtr actor)
//{
//  DestroyablePtr destr( new Destroyable );
//  actor->insertFeature(destr);
//}

//TEST_F(CharacterTest, dropInventoryOndie)
//{
//  //create an orc
//  ActorPtr orc( Actor::create(ActorType::Orc, 0,0, mapMock) );

//  clearInventory(orc);
//  clearBody(orc);
//  clearDropRules(orc);

//  //insert some item to inventory
//  ContainerPtr inv = orc->getFeature<Container>();
//  EXPECT_TRUE( inv != nullptr );
//  EXPECT_TRUE( inv->add( Actor::create(ActorType::CookBook) ) );

//  //kill actor
//  EXPECT_CALL(*mapMock, addActor(_));
//  orc->getFeature<Character>()->die();
//}

//TEST_F(CharacterTest, dropWearedItemsOndie)
//{
//  //create an orc
//  ActorPtr orc( Actor::create(ActorType::Orc, 0,0, mapMock) );

//  clearInventory(orc);
//  clearBody(orc);
//  clearDropRules(orc);

//  //wear an item
//  WearerPtr wearer = orc->getFeature<Wearer>();
//  EXPECT_TRUE( wearer != nullptr );
//  EXPECT_TRUE( wearer->equip( Actor::create(ActorType::LinenClothes) ) );

//  //kill actor
//  EXPECT_CALL(*mapMock, addActor(_));
//  orc->getFeature<Character>()->die();
//}

}
