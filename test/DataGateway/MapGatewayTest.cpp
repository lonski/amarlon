#include "gtest/gtest.h"
#include "DataGateways/MapGateway.h"
#include "World/map.h"

namespace amarlon {

TEST(MapGatewayTest, fetchOfNonExistingMap_GivesNull)
{
  MapGateway gateway;
  Map* map = gateway.fetch(MapId::Null);

  ASSERT_TRUE(map == nullptr);
}

TEST(MapGatewayTest, fetchExistingMap_givesMap)
{
  MapGateway gateway;
  gateway.loadMaps("../amarlon/maps.xml");
  Map* map = gateway.fetch(MapId::GameStart);

  ASSERT_TRUE(map != nullptr);
  ASSERT_EQ(map->getId(), MapId::GameStart );
}

TEST(MapGatewayTest, mapHasValidTiles)
{
  Map::Tiles.loadTiles("../amarlon/tiles.xml");
  MapGateway gateway;
  gateway.loadMaps("../amarlon/maps.xml");
  Map* map = gateway.fetch(MapId::GameStart);

  ASSERT_EQ(map->getChar(39,27), Map::Tiles.getChar(TileType::PlainFloor));
}

TEST(MapGatewayTest, mapHasValidTiles2)
{
  Map::Tiles.loadTiles("../amarlon/tiles.xml");
  MapGateway gateway;
  gateway.loadMaps("../amarlon/maps.xml");
  Map* map = gateway.fetch(MapId::GameStart);

  ASSERT_EQ(map->getChar(1,1), Map::Tiles.getChar(TileType::Tree));
}

TEST(MapGatewayTest, saveMaps)
{
  MapGateway gateway;
  gateway.loadMaps("../amarlon/maps.xml");
  gateway.saveMaps("../amarlon/maps_saved.xml");
}

}
