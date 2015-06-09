#include "container.h"
#include <algorithm>
#include <iostream>
#include "actor/actor.h"
#include "amarlon_except.h"

namespace amarlon {

const ActorFeature::Type Container::featureType = ActorFeature::CONTAINER;

Container::Container(size_t maxSize)
  : _slotCount(maxSize)
  , _pushToFront(false)
{
}

Container::~Container()
{
  //std::for_each(_inventory.begin(), _inventory.end(), [](ActorPtr a){ delete a; });
}

ContainerPtr Container::create(DescriptionPtr dsc)
{  
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  ContainerPtr cont;
  ContainerDescriptionPtr contDsc = std::dynamic_pointer_cast<ContainerDescription>(dsc);

  if ( contDsc != nullptr )
  {
    cont.reset( new Container(contDsc->maxSize) );

    std::for_each(contDsc->content.begin(), contDsc->content.end(), [&](ContainerDescription::Content ca)
    {
      ActorType aId = ca.actorType;
      if( aId != ActorType::Null )
      {
        ActorPtr nActor = Actor::create(aId);

        if (ca.container) nActor->insertFeature ( Container::create( ca.container ) );
        if (ca.openable)  nActor->insertFeature ( Openable::create ( ca.openable  ) );
        if (ca.pickable)  nActor->insertFeature ( Pickable::create ( ca.pickable  ) );
        if (ca.character) nActor->insertFeature ( Character::create( ca.character   ) );
        if (ca.ai)        nActor->insertFeature ( Ai::create       ( ca.ai        ) );
        if (ca.wearer)    nActor->insertFeature ( Wearer::create   ( ca.wearer    ) );

        cont->add( nActor );
      }
    });
  }else throw creation_error("Wrong container description!");

  return cont;
}

ActorFeaturePtr Container::clone()
{
  ContainerPtr cloned( new Container( _slotCount ) );

  std::for_each(_inventory.begin(), _inventory.end(), [&](ActorPtr a)
  {
    cloned->add( a->clone() );
  });

  return cloned;
}

bool Container::isEqual(ActorFeaturePtr rhs)
{
  bool equal = false;
  ContainerPtr crhs = std::dynamic_pointer_cast<Container>(rhs);
  if (crhs != nullptr)
  {
    equal = (_slotCount == crhs->_slotCount);    
    equal &= std::equal(_inventory.begin(), _inventory.end(), crhs->_inventory.begin(),
                        [](ActorPtr l, ActorPtr r){ return l->isEqual(r); });
  }

  return equal;
}

bool Container::add(ActorPtr actor)
{
  bool added = false;

  //handle stackable
  if ( actor->hasFeature<Pickable>() && actor->getFeature<Pickable>()->isStackable() )
  {
    auto invIter = find_if(_inventory.begin(), _inventory.end(), [&](ActorPtr iItem)
                   {
                     return iItem->isEqual( actor);
                   });

    if (invIter != _inventory.end()) //merge
    {
      ActorPtr actorToStackWith = *invIter;

      int invAmount = actorToStackWith->getFeature<Pickable>()->getAmount();
      int amountToStack = actor->getFeature<Pickable>()->getAmount();

      actorToStackWith->getFeature<Pickable>()->setAmount( invAmount + amountToStack );
      added = true;
    }
    else
    {
      added = pushNewItem(actor);
    }

  }
  //handle non-stackable
  else
  {
    added = pushNewItem(actor);
  }

  return added;
}

bool Container::addFront(ActorPtr actor)
{
  _pushToFront = true;
  bool r = add(actor);
  _pushToFront = false;

  return r;
}

bool Container::pushNewItem(ActorPtr actor)
{
  bool slotsAvail = (_inventory.size() < _slotCount);

  if (slotsAvail)
  {
    _pushToFront ? _inventory.push_front(actor) : _inventory.push_back(actor);
  }

  return slotsAvail;
}

bool Container::remove(ActorPtr actor)
{
  auto aIter = std::find(_inventory.begin(), _inventory.end(),actor);
  bool found = (aIter != _inventory.end());

  if (found)
  {
    _inventory.erase(aIter);
  }

  return found;
}

std::vector<ActorPtr> Container::content(std::function<bool(ActorPtr)>* filterFun)
{
  std::vector<ActorPtr> items;

  for (auto i : _inventory)
  {
    if ( (filterFun == nullptr) || (filterFun && (*filterFun)(i)))
    {
      items.push_back(i);
    }
  }

  return items;
}

size_t Container::size() const
{
  return _inventory.size();
}

void Container::performActionOnActors(std::function<void(ActorPtr)> fun)
{
  std::for_each(_inventory.begin(), _inventory.end(), fun);
}

void Container::sort(std::function<bool(ActorPtr, ActorPtr)> pred)
{
  _inventory.sort(pred);
}

size_t Container::slotCount() const
{
  return _slotCount;
}

void Container::setSlotCount(const size_t &maxSize)
{
  _slotCount = maxSize;
}

}
