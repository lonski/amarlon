#include "gtest/gtest.h"
#include "DataGateways/MapGateway.h"
#include "World/map.h"

TEST(MapGatewayTest, fetchOfNonExistingMap_GivesNull)
{
  MapGateway gateway;
  Map* map = gateway.fetch(MapId::Null);

  ASSERT_TRUE(map == nullptr);
}

TEST(MapGatewayTest, fetchExistingMap_givesMap)
{
  MapGateway gateway;
  gateway.loadMaps("d:/maps_saved.xml");
  Map* map = gateway.fetch(MapId::GameStart);

  ASSERT_TRUE(map != nullptr);
  ASSERT_EQ(map->getId(), MapId::GameStart );
}

TEST(MapGatewayTest, mapHasValidTiles)
{
  MapGateway gateway;
  gateway.loadMaps("d:/maps_saved.xml");
  Map* map = gateway.fetch(MapId::GameStart);

  ASSERT_EQ(map->getChar(39,27), '.');
}

TEST(MapGatewayTest, mapHasValidTiles2)
{
  MapGateway gateway;
  gateway.loadMaps("d:/maps_saved.xml");
  Map* map = gateway.fetch(MapId::Test);

  ASSERT_EQ(map->getChar(1,1), '.');
}

TEST(MapGatewayTest, saveMaps)
{
  MapGateway gateway;
  gateway.loadMaps("d:/maps.xml");
  gateway.saveMaps("d:/maps_saved.xml");
}


