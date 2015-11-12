#include "target.h"
#include <actor.h>

namespace amarlon {

Target::Target(std::vector<ActorPtr> actors_, uint32_t x_, uint32_t y_)
  : actors(actors_)
  , x(x_)
  , y(y_)
{}

Target::Target(ActorPtr actor_)
  : actors( {actor_ } )
  , x(0)
  , y(0)
{
  if ( actor_ )
  {
    x = actor_->getX();
    y = actor_->getY();
  }
}

Target::Target(uint32_t x_, uint32_t y_)
  : x(x_)
  , y(y_)
{}

Target::Target()
  : x(0)
  , y(0)
{}

ActorPtr Target::firstActor(std::function<bool (ActorPtr)> *filter) const
{
  if ( filter )
  {
    auto it = std::find_if(actors.begin(), actors.end(), *filter);
    return it != actors.end() ? *it : nullptr;
  }
  return actors.empty() ? nullptr : actors.front();
}

bool Target::operator==(const Target &rhs) const
{
  return x == rhs.x &&
         y == rhs.y &&
      std::equal(actors.begin(), actors.end(), rhs.actors.begin() );
}

bool Target::operator!=(const Target &rhs) const
{
  return !operator==(rhs);
}

Target::operator bool() const
{
  return operator!=(Target());
}

}

