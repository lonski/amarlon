#ifndef EVENT
#define EVENT

#include <event_id.h>
#include <map>
#include <string>

namespace amarlon {

typedef std::map<std::string, std::string> Params;

struct Event
{
  Event(EventId id = EventId::Null,  Params params = {} )
    : id(id)
    , params(params)
  {}

  EventId id;
  Params params;
};

}

#endif // EVENT

