#include "actor_db.h"
#include <fstream>
#include <algorithm>
#include <utils.h>
#include <actor_descriptions.h>
#include <xml/rapidxml.hpp>
#include <actor.h>
#include <actor_parser.h>

namespace amarlon {

using namespace std;
using namespace rapidxml;

ActorDB::ActorDB()
{
}

ActorPtr ActorDB::fetch(ActorType type)
{
  ActorPtr actor;

  auto it = std::find_if(_descriptions.begin(), _descriptions.end(), [type](ActorDescriptionPtr a){ return a->id == type; });
  if (it != _descriptions.end())
  {
    if ( (*it)->prototype )
    {
      actor = Actor::create(*(*it)->prototype);
      actor->upgrade(*it);
    }
    else
    {
      actor = Actor::create(*it, false);
    }
  }

  return actor;
}

ActorDescriptionPtr ActorDB::fetchDescription(ActorType type)
{
  auto it = std::find_if(_descriptions.begin(), _descriptions.end(), [type](ActorDescriptionPtr a){ return a->id == type; });
  return it != _descriptions.end() ? *it : nullptr;
}

void ActorDB::load(const string &fn)
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

void ActorDB::parseActors(std::vector<char>& dataToParse)
{
  xml_document<> doc;
  doc.parse<0>(&dataToParse[0]);

  xml_node<>* root = doc.first_node("Actors");
  if (root != nullptr)
  {
    ActorParser parser;
    xml_node<>* actorNode = root->first_node("Actor");

    while( actorNode != nullptr )
    {
      parser.setSource( actorNode );
      auto dsc = parser.parseDescription();
      if ( dsc ) _descriptions.push_back( dsc );

      actorNode = actorNode->next_sibling();
    }
  }

  doc.clear();
}

}

