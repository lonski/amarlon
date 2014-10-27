#include "gtest/gtest.h"
#include "DataGateways/MapGateway.h"
#include "World/Map.h"
#include <memory>

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
  gateway.loadMaps("../maps.xml");
  MapPtr map (gateway.fetch(MapId::GameStart));

  ASSERT_TRUE(map != nullptr);
  ASSERT_EQ(map->getId(), MapId::GameStart );
}

TEST(MapGatewayTest, mapHasValidTiles)
{
  Map::Tiles.loadTiles("../tiles.xml");
  MapGateway gateway;
  gateway.loadMaps("../maps.xml");
  MapPtr map ( gateway.fetch(MapId::GameStart) );

  ASSERT_EQ(map->getChar(39,27), Map::Tiles.getChar(TileType::PlainFloor));
}

TEST(MapGatewayTest, mapHasValidTiles2)
{
  Map::Tiles.loadTiles("../tiles.xml");
  MapGateway gateway;
  gateway.loadMaps("../maps.xml");
  MapPtr map ( gateway.fetch(MapId::GameStart) );

  ASSERT_EQ(map->getChar(1,1), Map::Tiles.getChar(TileType::Tree));
}

TEST(MapGatewayTest, saveMaps)
{
  MapGateway gateway;
  gateway.loadMaps("../maps.xml");
  gateway.saveMaps("../maps_saved.xml");
}

}
