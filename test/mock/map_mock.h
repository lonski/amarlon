#ifndef MAP_MOCK
#define MAP_MOCK

#include <memory>
#include <gmock/gmock.h>
#include <map.h>

namespace amarlon {

class Actor;
typedef std::shared_ptr<Actor> ActorPtr;

class MapMock : public Map
{
public:
  MOCK_METHOD2(isExplored, bool(int,int));
  MOCK_METHOD2(isInFov, bool(int,int));
  MOCK_METHOD2(isBlocked, bool(int,int));

  MOCK_METHOD1(addActor, void(ActorPtr));
  MOCK_METHOD1(removeActor, bool(ActorPtr));
  MOCK_METHOD2(getFirstActor, ActorPtr(int,int));
  MOCK_METHOD3(getActors, std::vector<ActorPtr>(int,int,std::function<bool (amarlon::ActorPtr)>*));
  MOCK_METHOD1(getActors, std::vector<ActorPtr>(std::function<bool(ActorPtr)>*));
  MOCK_METHOD2(getActorsContainer, InventoryPtr(u32,u32));
  MOCK_METHOD1(performActionOnActors, void(std::function<void(ActorPtr)>));
  MOCK_METHOD1(render, void(TCODConsole*));
  MOCK_METHOD1(updateActorCell, void(ActorPtr));

  MOCK_METHOD3(computeFov, void(int,int,int));
  MOCK_METHOD1(fill, void(std::string));
  MOCK_METHOD0(tilesToStr, std::string());

  MOCK_METHOD2(getColor, TCODColor(u32,u32));
  MOCK_METHOD2(getChar, char(u32,u32));
  MOCK_CONST_METHOD0(getWidth, u32());
  MOCK_METHOD1(setWidth, void(const u32));
  MOCK_CONST_METHOD0(getHeight, u32());
  MOCK_METHOD1(setHeight, void(const u32));
  MOCK_CONST_METHOD0(getId, MapId());
  MOCK_METHOD1(setId, void(const MapId));

  MapMock()
   : Map(100,100)
  {
  }

};

}

#endif // MAP_MOCK

