#ifndef TARGET_H
#define TARGET_H

#include <stdint.h>
#include <vector>
#include <memory>

namespace amarlon {

class Actor;
typedef std::shared_ptr<Actor> ActorPtr;

struct Target
{
  Target(std::vector<ActorPtr> actors_, uint32_t x_, uint32_t y_ )
    : actors(actors_)
    , x(x_)
    , y(y_)
  {}

  Target()
    : x(0)
    , y(0)
  {}

  ActorPtr firstActor() const
  {
    return actors.empty() ? nullptr : actors.front();
  }

  std::vector<ActorPtr> actors;
  uint32_t x;
  uint32_t y;
};

}

#endif // TARGET_H

