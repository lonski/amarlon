#include "actors_database.h"
#include <fstream>
#include <vector>
#include <xml/rapidxml.hpp>
#include <actor_parser.h>

using namespace rapidxml;

namespace amarlon { namespace map_editor {

ActorsDatabase::ActorsDatabase()
{

}

ActorDescriptionPtr ActorsDatabase::fetch(int id)
{
  ActorDescriptionPtr dsc;

  auto it = _actors.find(id);

  if ( it != _actors.end() )
  {
    if ( it->second->prototype )
    {
      ActorDescriptionPtr a = it->second;
      dsc.reset( new ActorDescription );
      auto it_proto = _actors.find(*a->prototype);
      *dsc = *it_proto->second;

      if ( a->color ) dsc->color = *a->color;
      if ( a->blocks ) dsc->blocks = *a->blocks;
      if ( a->fovOnly ) dsc->fovOnly = *a->fovOnly;
      if ( a->inscription ) dsc->inscription = *a->inscription;
      if ( a->name ) dsc->name = *a->name;
      if ( a->prototype ) dsc->prototype = *a->prototype;
      if ( a->symbol ) dsc->symbol = *a->symbol;
      if ( a->tilePriority ) dsc->tilePriority = *a->tilePriority;
      if ( a->transparent ) dsc->transparent = *a->transparent;
    }
    else
    {
      dsc = it->second;
    }
  }

  return dsc;
}

void ActorsDatabase::parse(std::vector<char> buffer)
{
  xml_document<> doc;
  doc.parse<0>(&buffer[0]);

  xml_node<>* root = doc.first_node("Actors");
  if (root != nullptr)
  {
    ActorParser parser;
    xml_node<>* actorNode = root->first_node("Actor");

    while( actorNode != nullptr )
    {
      parser.setSource( actorNode );
      auto dsc = parser.parseDescription();
      if ( dsc ) _actors[ *dsc->id ] = dsc;

      actorNode = actorNode->next_sibling();
    }
  }

  doc.clear();
}

void ActorsDatabase::load(const std::string &fn)
{
  std::ifstream ifs(fn);

  if (ifs.is_open())
  {
    std::vector<char> buffer;
    buffer.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    buffer.push_back('\0');

    parse(buffer);
  }
}

void ActorsDatabase::loadPlugin(const std::string &fn)
{
  load(fn);
}

std::map<int, ActorDescriptionPtr> ActorsDatabase::getActors() const
{
  return _actors;
}

}}
