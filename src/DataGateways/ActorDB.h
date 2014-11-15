#ifndef ACTORDB_H
#define ACTORDB_H

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <typeinfo>
#include <libtcod.hpp>
#include <xml/rapidxml.hpp>
#include <ActorDescriptions.h>

namespace amarlon {

class Actor;

class ActorDB
{
public:
  ActorDB();

  std::string getName(ActorType type);
  unsigned char getChar(ActorType type);
  TCODColor getColor(ActorType type);
  bool blocks(ActorType type);
  bool isFovOnly(ActorType type);
  bool isTransparent(ActorType type);
  int getTileRenderPriority(ActorType type);

  template<typename T>
  T* getFeature(ActorType type);

  bool loadActors(std::string fn);

private:
  typedef std::shared_ptr<Description> DescriptionPtr;
  typedef std::map<std::string, DescriptionPtr> DescriptionMap;

  std::map<ActorType, DescriptionMap> _descriptions;

  template<typename T>
  T getParam(ActorType type, T ActorDescription::*field, T defValue);

  template<typename T>
  Description* findDescription(ActorType actorType);

};

// === IMPLEMENTATION === //

template<typename T>
T* ActorDB::getFeature(ActorType actorType)
{
  Description* featureDescription = findDescription<T>(actorType);
  return featureDescription ? T::create(featureDescription) : nullptr;
}

template<typename T>
T ActorDB::getParam(ActorType type, T ActorDescription::*field, T defValue)
{
  ActorDescription* dsc = dynamic_cast<ActorDescription*>(findDescription<Actor>(type));
  return dsc ? dsc->*field : defValue;
}

template<typename T>
Description* ActorDB::findDescription(ActorType actorType)
{
  Description* dsc = nullptr;

  auto descriptionsIt = _descriptions.find(actorType);
  if ( descriptionsIt != _descriptions.end() )
  {
    DescriptionMap& actorDescriptions = descriptionsIt->second;
    auto dscIt = actorDescriptions.find(typeid(T).name());

    if (dscIt != actorDescriptions.end())
    {
      dsc = dscIt->second.get();
    }
  }

  return dsc;
}

}
#endif // ACTORDB_H
