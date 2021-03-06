#include <gtest/gtest.h>
#include <actor.h>
#include <drop_action.h>
#include <inventory.h>
#include <map.h>
#include <engine.h>
#include <world.h>
#include <die_action.h>
#include <pickup_action.h>
#include <module.h>

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
    Engine::instance().loadModule( Module("testing") );
    Engine::instance().enterGame();

    guy = Actor::create(2);

    //fill inventory
    guy->getFeature<Inventory>()->clear();
    guy->getFeature<Inventory>()->add( Actor::create(20) );
    guy->getFeature<Inventory>()->add( Actor::create(15) );

    //put guy on map
    guy->setPosition( 1,1);

    Engine::instance().getWorld().changeMap( 1 );
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
    EXPECT_TRUE( guy->performAction( new DropAction(a) ) == ActorActionResult::Ok );
    EXPECT_EQ( map->getActors( guy->getX(), guy->getY()).size(), (size_t)2 );
    map->removeActor( a );
  }
}

TEST_F(DropActionTest, dropGoblinCorpse)
{
  //kill a goblin on map to generate corpse
  ActorPtr goblin = Actor::create(25, 1, 2 );
  map->addActor( goblin );
  goblin->performAction( new DieAction );

  //pickup the corpse
  guy->setPosition( 1, 2 );
  EXPECT_TRUE( guy->performAction( new PickUpAction(goblin) ) == ActorActionResult::Ok );

  guy->setPosition( 11, 11 );

  //drop it
  EXPECT_EQ( map->getActors( guy->getX(), guy->getY()).size(), (size_t)1 );
  EXPECT_TRUE( guy->performAction( new DropAction(goblin) ) == ActorActionResult::Ok );
  EXPECT_EQ( map->getActors( guy->getX(), guy->getY()).size(), (size_t)2 );

}


}

