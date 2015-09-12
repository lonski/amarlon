#include "actor_container.h"
#include <actor.h>
#include <pickable.h>

namespace amarlon {

ActorContainer::ActorContainer()
{
}

ActorContainer::const_iterator ActorContainer::begin() const
{
  return _collection.begin();
}

ActorContainer::iterator ActorContainer::begin()
{
  return _collection.begin();
}

ActorContainer::const_iterator ActorContainer::end() const
{
  return _collection.end();
}

ActorContainer::iterator ActorContainer::end()
{
  return _collection.end();
}

ActorPtr ActorContainer::front()
{
  return _collection.front();
}

size_t ActorContainer::size() const
{
  return _collection.size();
}

bool ActorContainer::empty() const
{
  return _collection.empty();
}

void ActorContainer::push_back(ActorPtr actor)
{
  insert(actor, false);
}

void ActorContainer::push_front(ActorPtr actor)
{
  insert(actor, true);
}

bool ActorContainer::remove(ActorPtr actor)
{
  auto aIter = std::find(_collection.begin(), _collection.end(),actor);
  bool found = (aIter != _collection.end());

  if (found)
  {
    _collection.erase(aIter);
  }

  return found;
}

void ActorContainer::clear()
{
  _collection.clear();
}

void ActorContainer::sort(std::function<bool(ActorPtr, ActorPtr)> fun)
{
  _collection.sort(fun);
}

ActorContainer ActorContainer::filter(std::function<bool(ActorPtr)> fun)
{
  ActorContainer ac;
  for ( auto a : _collection )
  {
    if ( fun(a) )
    {
      ac.push_back(a);
    }
  }
  return ac;
}

std::vector<ActorPtr> ActorContainer::toVector()
{
  return std::vector<ActorPtr>{ _collection.begin(), _collection.end() };
}

ActorContainerPtr ActorContainer::clone()
{
  ActorContainerPtr cloned( new ActorContainer );

  std::for_each(_collection.begin(), _collection.end(), [&](ActorPtr a)
  {
    cloned->push_back( a->clone() );
  });

  return cloned;
}

void ActorContainer::insert(ActorPtr actor, bool front)
{
  //handle stackable
  if ( actor->hasFeature<Pickable>() && actor->getFeature<Pickable>()->isStackable() )
  {
    auto invIter = find_if(_collection.begin(), _collection.end(), [&](ActorPtr iItem)
                   {
                     return *iItem == *actor;
                   });

    if (invIter != _collection.end()) //merge
    {
      ActorPtr actorToStackWith = *invIter;

      int invAmount = actorToStackWith->getFeature<Pickable>()->getAmount();
      int amountToStack = actor->getFeature<Pickable>()->getAmount();

      actorToStackWith->getFeature<Pickable>()->setAmount( invAmount + amountToStack );
    }
    else
    {
      front ? _collection.push_front(actor) : _collection.push_back(actor);
    }

  }
  //handle non-stackable
  else
  {
    front ? _collection.push_front(actor) : _collection.push_back(actor);
  }
}

ActorContainer::iterator begin(ActorContainer &ac)
{
  return ac.begin();
}

ActorContainer::iterator end(ActorContainer &ac)
{
  return ac.end();
}

}
