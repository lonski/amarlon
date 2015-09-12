#ifndef ACTOR_CONTAINER_H
#define ACTOR_CONTAINER_H

#include <list>
#include <memory>
#include <vector>

namespace amarlon {

class Actor;
class ActorContainer;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<ActorContainer> ActorContainerPtr;

class ActorContainer
{
public:
  ActorContainer();
  ActorContainerPtr clone();

  typedef std::list<ActorPtr>::iterator iterator;
  typedef std::list<ActorPtr>::const_iterator const_iterator;

  const_iterator begin() const;
  iterator begin();
  const_iterator end() const;
  iterator end();
  ActorPtr front();

  size_t size() const;
  bool empty() const;

  void push_back(ActorPtr actor);
  void push_front(ActorPtr actor);

  bool remove(ActorPtr actor);
  void clear();

  void sort(std::function<bool(ActorPtr, ActorPtr)> fun);
  ActorContainer filter(std::function<bool(ActorPtr)> fun);
  std::vector<ActorPtr> toVector();

private:
  std::list<ActorPtr> _collection;

  void insert(ActorPtr actor, bool front = false);

};

ActorContainer::iterator begin(ActorContainer& ac);
ActorContainer::iterator end(ActorContainer& ac);

}

#endif // ACTOR_CONTAINER_H
