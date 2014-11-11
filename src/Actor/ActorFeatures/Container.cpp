#include "Container.h"
#include <algorithm>
#include <iostream>
#include "Actor/Actor.h"
#include <memory>

namespace amarlon {

Container::Container(size_t maxSize)
  : _slotCount(maxSize)
  , _pushToFront(false)
{
}

Container::~Container()
{
  std::for_each(_inventory.begin(), _inventory.end(), [](Actor* a){ delete a; });
}

Container* Container::create(const ContainerDescription &dsc)
{  
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  Container* cont = new Container(dsc.maxSize);

  std::for_each(dsc.content.begin(), dsc.content.end(), [&](ContainerDescription::Content ca)
  {
    ActorType aId = ca.actorType;
    if( aId != ActorType::Null )
    {
      Actor* nActor = new Actor(aId);

      if (ca.container) nActor->setAfContainer( Container::create( *ca.container ) );
      if (ca.openable)  nActor->setAfOpenable ( Openable::create ( *ca.openable  ) );
      if (ca.pickable)  nActor->setAfPickable ( Pickable::create ( *ca.pickable  ) );
      if (ca.fighter)   nActor->setAfFighter  ( Fighter::create  ( *ca.fighter   ) );
      if (ca.ai)        nActor->setAfAi       ( Ai::create       ( *ca.ai        ) );
      if (ca.wearer)    nActor->setAfWearer   ( Wearer::create   ( *ca.wearer    ) );

      cont->add(nActor);
    }
  });

  return cont;
}

Container *Container::clone()
{
  Container* cloned = new Container( _slotCount );

  std::for_each(_inventory.begin(), _inventory.end(), [&](Actor* a)
  {
    cloned->add( a->clone() );
  });

  return cloned;
}

bool Container::isEqual(ActorFeature *rhs)
{
  bool equal = false;
  Container* crhs = dynamic_cast<Container*>(rhs);
  if (crhs != nullptr)
  {
    equal = (_slotCount == crhs->_slotCount);
    equal &= std::equal(_inventory.begin(), _inventory.end(), crhs->_inventory.begin(),
                        std::mem_fun(&Actor::isEqual));
  }

  return equal;
}

bool Container::add(Actor *actor)
{
  bool added = false;

  //handle stackable
  if ( actor->afPickable() && actor->afPickable()->isStackable() )
  {
    auto invIter = find_if(_inventory.begin(), _inventory.end(), [&](Actor* iItem)
                   {
                     return iItem->isEqual( actor);
                   });

    if (invIter != _inventory.end()) //merge
    {
      Actor* actorToStackWith = *invIter;

      int invAmount = actorToStackWith->afPickable()->getAmount();
      int amountToStack = actor->afPickable()->getAmount();

      actorToStackWith->afPickable()->setAmount( invAmount + amountToStack );

      delete actor;
      actor = nullptr;
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

bool Container::addFront(Actor *actor)
{
  _pushToFront = true;
  bool r = add(actor);
  _pushToFront = false;

  return r;
}

bool Container::pushNewItem(Actor *actor)
{
  bool slotsAvail = (_inventory.size() < _slotCount);

  if (slotsAvail)
  {
    _pushToFront ? _inventory.push_front(actor) : _inventory.push_back(actor);
  }

  return slotsAvail;
}

bool Container::remove(Actor *actor)
{

  auto aIter = std::find(_inventory.begin(), _inventory.end(),actor);
  bool found = (aIter != _inventory.end());

  if (found)
  {
    _inventory.erase(aIter);
  }

  return found;
}

std::vector<Actor *> Container::content(std::function<bool(Actor*)>* filterFun/*bool(*filterFun)(Actor*)*/ )
{
  std::vector<Actor *> items;

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

void Container::performActionOnActors(std::function<void(Actor *)> fun)
{
  std::for_each(_inventory.begin(), _inventory.end(), fun);
}

void Container::sort(std::function<bool(Actor*, Actor*)> pred)
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
