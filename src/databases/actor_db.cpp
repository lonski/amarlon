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

ActorPtr ActorDB::fetch(int type)
{
  ActorPtr a = fetch(type, _pluginDescriptions);
  return a ? a : fetch(type, _descriptions);
}

ActorDescriptionPtr ActorDB::fetchDescription(int type)
{
  ActorDescriptionPtr a = fetchDescription(type, _pluginDescriptions);
  return a ? a : fetchDescription(type, _descriptions);
}

ActorPtr ActorDB::fetch(int type, std::vector<ActorDescriptionPtr>& src)
{
  ActorPtr actor;

  auto it = std::find_if(src.begin(), src.end(),
                         [type](ActorDescriptionPtr a){ return a->id == (int)type; });
  if (it != src.end())
  {
    if ( (*it)->prototype )
    {
      actor = Actor::create( *(*it)->prototype );
      actor->upgrade(*it);
    }
    else
    {
      actor = Actor::create(*it, false);
    }
  }

  return actor;
}

ActorDescriptionPtr ActorDB::fetchDescription(int type, std::vector<ActorDescriptionPtr>& src)
{
  auto it = std::find_if(src.begin(), src.end(),
                         [type](ActorDescriptionPtr a){ return a->id == (int)type; });
  return it != src.end() ? *it : nullptr;
}

void ActorDB::load(const string &fn)
{
  ifstream ifs(fn);

  if (ifs.is_open())
  {
    vector<char> buffer;
    buffer.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    buffer.push_back('\0');

    parseActors(buffer, _descriptions);
  }
}

void ActorDB::loadPlugin(const string &fn)
{
  ifstream ifs(fn);

  if (ifs.is_open())
  {
    vector<char> buffer;
    buffer.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    buffer.push_back('\0');

    parseActors(buffer, _pluginDescriptions);
  }
}

void ActorDB::parseActors(std::vector<char>& dataToParse, std::vector<ActorDescriptionPtr>& dst)
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
      if ( dsc ) dst.push_back( dsc );

      actorNode = actorNode->next_sibling();
    }
  }

  doc.clear();
}

}

