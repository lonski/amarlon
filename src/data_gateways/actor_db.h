#ifndef ACTORDB_H
#define ACTORDB_H

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <libtcod.hpp>
#include "xml/rapidxml.hpp"
#include "actor_descriptions.h"
#include "actor_feature.h"
#include "parsers/actor_parser.h"

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
  std::shared_ptr<T> getFeature(ActorType type);

  FeatureMap getAllFeatures(ActorType type);

  /**
   * @brief loads given file, parses xml and creates actor descriptions
   * @param path to file to be loaded
   */
  void loadActors(const std::string& fn);

private:
  typedef std::shared_ptr<Description> DescriptionPtr;
  typedef std::map<ActorFeature::Type, DescriptionPtr> FeatureDescriptionMap;

  std::map<ActorType, FeatureDescriptionMap> _featureDscs;
  std::map<ActorType, DescriptionPtr>        _actorDscs;

  ActorParser _actorParser;

  void parseActors(std::vector<char>& dataToParse);
  void parseActor(rapidxml::xml_node<>* actorNode);
  void parseActorFeatures(ActorType actorId);

  template<typename T>
  T getParam(ActorType type, T ActorDescription::*field, T defValue);

  template<typename T>
  DescriptionPtr findDescription(ActorType actorType);

};

// === IMPLEMENTATION === //

template<typename T>
std::shared_ptr<T> ActorDB::getFeature(ActorType actorType)
{
  DescriptionPtr featureDescription = findDescription<T>(actorType);
  return featureDescription ? T::create(featureDescription) : std::shared_ptr<T>();
}

template<typename T>
T ActorDB::getParam(ActorType type, T ActorDescription::*field, T defValue)
{
  auto it = _actorDscs.find(type);
  ActorDescriptionPtr dsc = it != _actorDscs.end() ? std::dynamic_pointer_cast<ActorDescription>( it->second ) : nullptr;

  return dsc ? (*dsc).*field : defValue;
}

template<typename T>
DescriptionPtr ActorDB::findDescription(ActorType actorType)
{
  DescriptionPtr dsc;

  auto descriptionsIt = _featureDscs.find(actorType);
  if ( descriptionsIt != _featureDscs.end() )
  {
    FeatureDescriptionMap& actorDescriptions = descriptionsIt->second;
    auto dscIt = actorDescriptions.find(T::featureType);

    if (dscIt != actorDescriptions.end())
    {
      dsc = dscIt->second;
    }
  }

  return dsc;
}

}
#endif // ACTORDB_H
