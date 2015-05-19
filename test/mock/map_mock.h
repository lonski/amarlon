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

  MOCK_METHOD1(addActor, void(ActorPtr));

  MapMock()
   : Map(0,0)
  {
  }

};

}

#endif // MAP_MOCK

