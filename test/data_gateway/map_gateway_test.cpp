#include "gtest/gtest.h"
#include <memory>
#include <map_db.h>
#include <map.h>
#include <engine.h>
#include <configuration.h>
#include <tile_db.h>
#include <module.h>

namespace amarlon {

typedef std::shared_ptr<Map> MapPtr;

class MapDBTest : public ::testing::Test
{
  virtual void SetUp()
  {
    Engine::instance().prologue();
    Engine::instance().loadModule( Module("testing") );
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
  MapPtr map ( gateway.fetch(0) );

  ASSERT_TRUE(map == nullptr);
}

TEST_F(MapDBTest, fetchExistingMap_givesMap)
{
  MapDB gateway;
  gateway.load( Engine::instance().getModule().getPath() + "data/maps.xml");
  MapPtr map (gateway.fetch(1));

  ASSERT_TRUE(map != nullptr);
  ASSERT_EQ(map->getId(), 1 );
}

TEST_F(MapDBTest, mapHasValidTiles)
{
  MapDB gateway;
  gateway.load( Engine::instance().getModule().getPath() + "data/maps.xml");
  MapPtr map ( gateway.fetch(1) );

  EXPECT_EQ(map->getChar(39,27), Engine::instance().getTileDB().getChar(TileType::PlainFloor));
}

TEST_F(MapDBTest, mapHasValidTiles2)
{
  MapDB gateway;
  gateway.load( Engine::instance().getModule().getPath() + "data/maps.xml");
  MapPtr map ( gateway.fetch(1) );

  EXPECT_EQ(map->getChar(1,1), Engine::instance().getTileDB().getChar(TileType::Tree));
}

TEST_F(MapDBTest, saveMaps)
{
  MapDB gateway;
  gateway.load( Engine::instance().getModule().getPath() + "data/maps.xml");
  ASSERT_TRUE(gateway.store("data/maps_saved.xml"));
}

}

