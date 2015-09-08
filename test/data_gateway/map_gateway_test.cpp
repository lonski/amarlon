#include "gtest/gtest.h"
#include <memory>
#include "data_gateways/map_gateway.h"
#include <map.h>
#include <engine.h>
#include <configuration.h>
#include <tile_db.h>

namespace amarlon {

typedef std::shared_ptr<Map> MapPtr;

TEST(MapGatewayTest, fetchOfNonExistingMap_GivesNull)
{
  MapGateway gateway;
  MapPtr map ( gateway.fetch(MapId::Null) );

  ASSERT_TRUE(map == nullptr);
}

TEST(MapGatewayTest, fetchExistingMap_givesMap)
{
  MapGateway gateway;
  gateway.load("data/maps.xml");
  MapPtr map (gateway.fetch(MapId::GameStart));

  ASSERT_TRUE(map != nullptr);
  ASSERT_EQ(map->getId(), MapId::GameStart );
}

TEST(MapGatewayTest, mapHasValidTiles)
{
  Configuration cfg;
  ASSERT_TRUE( cfg.load("config.cfg") );

  Engine::instance().prologue(&cfg);

  MapGateway gateway;
  gateway.load("data/maps.xml");
  MapPtr map ( gateway.fetch(MapId::GameStart) );

  ASSERT_EQ(map->getChar(39,27), Engine::instance().getTileDB().getChar(TileType::PlainFloor));
}

TEST(MapGatewayTest, mapHasValidTiles2)
{
  Configuration cfg;
  ASSERT_TRUE( cfg.load("config.cfg") );

  Engine::instance().prologue(&cfg);

  MapGateway gateway;
  gateway.load("data/maps.xml");
  MapPtr map ( gateway.fetch(MapId::GameStart) );

  ASSERT_EQ(map->getChar(1,1), Engine::instance().getTileDB().getChar(TileType::Tree));
}

TEST(MapGatewayTest, saveMaps)
{
  MapGateway gateway;
  gateway.load("data/maps.xml");
  gateway.store("data/maps_saved.xml");
}

}
