#include "gtest/gtest.h"
#include <memory>
#include "data_gateways/map_gateway.h"
#include "world/map.h"

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
  Map::Tiles.loadTiles("data/tiles.xml");
  MapGateway gateway;
  gateway.load("data/maps.xml");
  MapPtr map ( gateway.fetch(MapId::GameStart) );

  ASSERT_EQ(map->getChar(39,27), Map::Tiles.getChar(TileType::PlainFloor));
}

TEST(MapGatewayTest, mapHasValidTiles2)
{
  Map::Tiles.loadTiles("data/tiles.xml");
  MapGateway gateway;
  gateway.load("data/maps.xml");
  MapPtr map ( gateway.fetch(MapId::GameStart) );

  ASSERT_EQ(map->getChar(1,1), Map::Tiles.getChar(TileType::Tree));
}

TEST(MapGatewayTest, saveMaps)
{
  MapGateway gateway;
  gateway.load("data/maps.xml");
  gateway.store("data/maps_saved.xml");
}

}
