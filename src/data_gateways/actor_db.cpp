#include "actor_db.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include "utils/utils.h"
#include "actor/actor.h"
#include "actor/effects/effect.h"
#include "world/map.h"

namespace amarlon {

using namespace std;
using namespace rapidxml;

ActorDB::ActorDB()
{
}

string ActorDB::getName(ActorType type)
{
  return getParam<std::string>(type, &ActorDescription::name, "No name");
}

unsigned char ActorDB::getChar(ActorType type)
{
  return getParam<unsigned char>(type, &ActorDescription::character, 'X');
}

TCODColor ActorDB::getColor(ActorType type)
{
  return getParam<TCODColor>(type, &ActorDescription::color, TCODColor::white);
}

bool ActorDB::blocks(ActorType type)
{
  return getParam<bool>(type, &ActorDescription::blocks, false);
}

bool ActorDB::isFovOnly(ActorType type)
{
  return getParam<bool>(type, &ActorDescription::fovOnly, false);
}

bool ActorDB::isTransparent(ActorType type)
{
  return getParam<bool>(type, &ActorDescription::transparent, false);
}

int ActorDB::getTileRenderPriority(ActorType type)
{
  int piority = getParam<int>(type, &ActorDescription::tilePriority, -1);

  //not set in xml, set default prority for particural actor type
  if ( piority == -1 )
  {
    switch( type )
    {
      case ActorType::DoorOpen:
      case ActorType::DoorClosed:
      {
        piority = Tile::defaultItemRenderPriority + 1;
      }
      break;
      default:;
    }
  }

  return piority;
}

// === GET ALL FEATURES === //

class FeatureGetter
{
public:
  FeatureGetter(ActorDB* actorDB)
    : _actorDB(actorDB)
  {}

  FeatureMap get(ActorType type)
  {
    _features.clear();
    _aType = type;

    for (int f = ActorFeature::FT_NULL+1; f != ActorFeature::FT_END; ++f )
    {
      ActorFeature::Type fType = static_cast<ActorFeature::Type>(f);

      //TODO: find out more elegant and generic way
      switch(fType)
      {
        case ActorFeature::AI:
          addFeature<Ai>();
          break;
        case ActorFeature::CONTAINER:
          addFeature<Container>();
          break;
        case ActorFeature::FIGHTER:
          addFeature<Fighter>();
          break;
        case ActorFeature::OPENABLE:
          addFeature<Openable>();
          break;
        case ActorFeature::PICKABLE:
          addFeature<Pickable>();
          break;
        case ActorFeature::WEARER:
          addFeature<Wearer>();
          break;
        default:;
      }
    }

    return _features;
  }

private:
  template<typename T>
  void addFeature()
  {
    T* t = _actorDB->getFeature<T>(_aType);
    if ( t != nullptr ) _features[T::featureType] = ActorFeaturePtr(t);
  }

  ActorDB* _actorDB;
  FeatureMap _features;
  ActorType _aType;

};

FeatureMap ActorDB::getAllFeatures(ActorType type)
{
  return FeatureGetter(this).get(type);
}

// === LOAD ACTORS === //

void ActorDB::loadActors(const string &fn)
{
  ifstream ifs(fn);

  if (ifs.is_open())
  {
    vector<char> buffer;
    buffer.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    buffer.push_back('\0');

    parseActors(buffer);
  }
}

void ActorDB::parseActors(vector<char>& dataToParse)
{
  xml_document<> doc;
  doc.parse<0>(&dataToParse[0]);

  xml_node<>* root = doc.first_node("Actors");
  if (root != nullptr)
  {
    xml_node<>* actorNode = root->first_node("Actor");

    while( actorNode != nullptr )
    {
      parseActor(actorNode);
      actorNode = actorNode->next_sibling();
    }
  }

  doc.clear();
}

void ActorDB::parseActor(xml_node<>* actorNode)
{
  _actorParser.setSource( actorNode );

  ActorDescription* actorDsc = _actorParser.parseActorDsc();
  if ( actorDsc != nullptr )
  {
    _actorDscs[actorDsc->id] = DescriptionPtr(actorDsc);
    parseActorFeatures(actorDsc->id);
  }
}

void ActorDB::parseActorFeatures(ActorType actorId)
{
  FeatureDescriptionMap actorDescriptions;

  for (int f = ActorFeature::FT_NULL+1; f != ActorFeature::FT_END; ++f )
  {
    ActorFeature::Type fType = static_cast<ActorFeature::Type>(f);

    DescriptionPtr featureDsc( _actorParser.parseFeatureDsc(fType) );
    if ( featureDsc ) actorDescriptions[ fType ] = featureDsc;
  }

  _featureDscs[actorId] = actorDescriptions;
}

}
