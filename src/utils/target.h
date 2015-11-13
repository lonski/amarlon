#ifndef TARGET_H
#define TARGET_H

#include <stdint.h>
#include <vector>
#include <memory>
#include <algorithm>

namespace amarlon {

class Actor;
typedef std::shared_ptr<Actor> ActorPtr;

struct Target
{
  Target(std::vector<ActorPtr> actors_, uint32_t x_, uint32_t y_ );
  Target(ActorPtr actor_);
  Target(uint32_t x_, uint32_t y_ );
  Target();

  ActorPtr firstActor(std::function<bool(ActorPtr)> filter) const;
  ActorPtr firstActor() const;

  bool operator==(const Target& rhs) const;
  bool operator!=(const Target& rhs) const;
  operator bool() const;

  std::vector<ActorPtr> actors;
  uint32_t x;
  uint32_t y;
};

}

#endif // TARGET_H

