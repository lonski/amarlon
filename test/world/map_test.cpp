#include "gtest/gtest.h"
#define private public
#include <map.h>
#undef private
#include <actor.h>
#include <map_db.h>
#include <engine.h>

namespace amarlon {

class MapTest : public ::testing::Test
{
  virtual void SetUp()
  {
    Engine::instance().prologue();
    mapDB.load("data/maps.xml");
  }

  virtual void TearDown()
  {
  }

protected:
  MapDB mapDB;

};

TEST_F(MapTest, mapCreation)
{
  MapData data;
  data.set_height(60);
  data.set_width(60);

  Map map(data);

  ASSERT_EQ(map.getWidth(), (size_t)100);
  ASSERT_EQ(map.getHeight(), (size_t)60);
}

TEST_F(MapTest, mapHasTiles)
{
  MapData data;
  data.set_height(60);
  data.set_width(60);

  Map map(data);

  ASSERT_FALSE(map.isExplored(10, 5));
}

TEST_F(MapTest, mapIsInFov_notComputed)
{
  MapData data;
  data.set_height(60);
  data.set_width(60);

  Map map(data);

  ASSERT_FALSE(map.isInFov(10, 5));
}

TEST_F(MapTest, mapIsInFov_computed)
{
  MapData data;
  data.set_height(60);
  data.set_width(60);

  Map map(data);

  map.computeFov(10, 10, 5);

  ASSERT_TRUE(map.isInFov(10, 10));
}

TEST_F(MapTest, addActor)
{
  MapPtr map = mapDB.fetch(MapId::GameStart);

  ActorPtr actor = Actor::create(ActorType::HealthPotion);
  actor->setPosition(1,1);

  map->addActor(actor);
  auto actors = map->getActors(1,1);

  EXPECT_EQ(actors.size(), (size_t)1);
  EXPECT_TRUE( actors.front().get() == actor.get() );
}

}

