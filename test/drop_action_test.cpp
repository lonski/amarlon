#include <gtest/gtest.h>
#include <actor.h>
#include <drop_action.h>
#include <inventory.h>
#include <map.h>
#include <engine.h>
#include <world.h>
#include <die_action.h>
#include <pickup_action.h>

namespace amarlon {

class DropActionTest : public ::testing::Test
{
public:
  DropActionTest()
  {
  }

  virtual void SetUp()
  {
    Engine::instance().prologue();
    Engine::instance().enterGame();

    guy = Actor::create(ActorType::Orc);

    //fill inventory
    guy->getFeature<Inventory>()->clear();
    guy->getFeature<Inventory>()->add( Actor::create(ActorType::LeatherArmor) );
    guy->getFeature<Inventory>()->add( Actor::create(ActorType::Corpse) );

    //put guy on map
    guy->setPosition( 1,1);

    map = Engine::instance().getWorld().getCurrentMap();
    map->addActor( guy );

  }
  virtual void TearDown()
  {
  }

protected:
  ActorPtr guy;
  MapPtr map;

};

TEST_F(DropActionTest, dropOnMap)
{
  auto items = guy->getFeature<Inventory>()->items();
  for ( ActorPtr a : items )
  {
    EXPECT_EQ( map->getActors( guy->getX(), guy->getY()).size(), (size_t)1 );
    EXPECT_TRUE( guy->performAction( std::make_shared<DropAction>(a) ) );
    EXPECT_EQ( map->getActors( guy->getX(), guy->getY()).size(), (size_t)2 );
    map->removeActor( a );
  }
}

TEST_F(DropActionTest, dropGoblinCorpse)
{
  //kill a goblin on map to generate corpse
  ActorPtr goblin = Actor::create(ActorType::Goblin, 1, 2 );
  map->addActor( goblin );
  goblin->performAction( std::make_shared<DieAction>() );

  //pickup the corpse
  guy->setPosition( 1, 2 );
  EXPECT_TRUE( guy->performAction( std::make_shared<PickUpAction>(goblin) ) );

  guy->setPosition( 11, 11 );

  //drop it
  EXPECT_EQ( map->getActors( guy->getX(), guy->getY()).size(), (size_t)1 );
  EXPECT_TRUE( guy->performAction( std::make_shared<DropAction>(goblin) ) );
  EXPECT_EQ( map->getActors( guy->getX(), guy->getY()).size(), (size_t)2 );

}


}

