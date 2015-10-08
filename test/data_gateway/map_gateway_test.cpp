#include "gtest/gtest.h"
#include <memory>
#include "data_gateways/map_gateway.h"
#include <map.h>
#include <engine.h>
#include <configuration.h>
#include <tile_db.h>

namespace amarlon {

typedef std::shared_ptr<Map> MapPtr;

class MapGatewayTest : public ::testing::Test
{
  virtual void SetUp()
  {
    Engine::instance().prologue();
  }

  virtual void TearDown()
  {
    Engine::instance().epilogue();
  }

};

TEST_F(MapGatewayTest, fetchOfNonExistingMap_GivesNull)
{
  MapGateway gateway;
  MapPtr map ( gateway.fetch(MapId::Null) );

  ASSERT_TRUE(map == nullptr);
}

TEST_F(MapGatewayTest, fetchExistingMap_givesMap)
{
  MapGateway gateway;
  gateway.load("data/maps.xml");
  MapPtr map (gateway.fetch(MapId::GameStart));

  ASSERT_TRUE(map != nullptr);
  ASSERT_EQ(map->getId(), MapId::GameStart );
}

TEST_F(MapGatewayTest, mapHasValidTiles)
{
  MapGateway gateway;
  gateway.load("data/maps.xml");
  MapPtr map ( gateway.fetch(MapId::GameStart) );

  EXPECT_EQ(map->getChar(39,27), Engine::instance().getTileDatabase().getChar(TileType::PlainFloor));
}

TEST_F(MapGatewayTest, mapHasValidTiles2)
{
  MapGateway gateway;
  gateway.load("data/maps.xml");
  MapPtr map ( gateway.fetch(MapId::GameStart) );

  EXPECT_EQ(map->getChar(1,1), Engine::instance().getTileDatabase().getChar(TileType::Tree));
}

TEST_F(MapGatewayTest, saveMaps)
{
  MapGateway gateway;
  gateway.load("data/maps.xml");
  gateway.store("data/maps_saved.xml");
}

}

