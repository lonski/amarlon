#include "gtest/gtest.h"
#include <memory>
#include <map_db.h>
#include <map.h>
#include <engine.h>
#include <configuration.h>
#include <tile_db.h>

namespace amarlon {

typedef std::shared_ptr<Map> MapPtr;

class MapDBTest : public ::testing::Test
{
  virtual void SetUp()
  {
    Engine::instance().prologue();
    Engine::instance().enterGame();
  }

  virtual void TearDown()
  {
    Engine::instance().epilogue();
  }

};

TEST_F(MapDBTest, fetchOfNonExistingMap_GivesNull)
{
  MapDB gateway;
  MapPtr map ( gateway.fetch(MapId::Null) );

  ASSERT_TRUE(map == nullptr);
}

TEST_F(MapDBTest, fetchExistingMap_givesMap)
{
  MapDB gateway;
  gateway.load("data/maps.xml");
  MapPtr map (gateway.fetch(MapId::GameStart));

  ASSERT_TRUE(map != nullptr);
  ASSERT_EQ(map->getId(), MapId::GameStart );
}

TEST_F(MapDBTest, mapHasValidTiles)
{
  MapDB gateway;
  gateway.load("data/maps.xml");
  MapPtr map ( gateway.fetch(MapId::GameStart) );

  EXPECT_EQ(map->getChar(39,27),
            Engine::instance().getTileDB().fetch_flyweight(TileType::PlainFloor)->character().front());
}

TEST_F(MapDBTest, mapHasValidTiles2)
{
  MapDB gateway;
  gateway.load("data/maps.xml");
  MapPtr map ( gateway.fetch(MapId::GameStart) );

  EXPECT_EQ(map->getChar(1,1),
            Engine::instance().getTileDB().fetch_flyweight(TileType::Tree)->character().front());
}

TEST_F(MapDBTest, saveMaps)
{
  MapDB gateway;
  gateway.load("data/maps.xml");
  gateway.store("data/maps_saved.xml");
}

}

