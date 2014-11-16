#ifndef ACTORDB_H
#define ACTORDB_H

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <libtcod.hpp>
#include <xml/rapidxml.hpp>
#include <ActorDescriptions.h>
#include <ActorFeature.h>
#include <Parsers/ActorParser.h>

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
  auto it = _actorDscs.find(type);
  ActorDescription* dsc = it != _actorDscs.end() ? dynamic_cast<ActorDescription*>( it->second.get() ) : nullptr;

  return dsc ? dsc->*field : defValue;
}

template<typename T>
Description* ActorDB::findDescription(ActorType actorType)
{
  Description* dsc = nullptr;

  auto descriptionsIt = _featureDscs.find(actorType);
  if ( descriptionsIt != _featureDscs.end() )
  {
    FeatureDescriptionMap& actorDescriptions = descriptionsIt->second;
    auto dscIt = actorDescriptions.find(T::featureType);

    if (dscIt != actorDescriptions.end())
    {
      dsc = dscIt->second.get();
    }
  }

  return dsc;
}

}
#endif // ACTORDB_H
