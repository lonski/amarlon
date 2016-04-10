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
  auto it = _actors.find(id);
  return it != _actors.end() ? it->second : nullptr;
}

void ActorsDatabase::load(const std::string &fn)
{
  std::ifstream ifs(fn);

  if (ifs.is_open())
  {
    std::vector<char> buffer;
    buffer.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    buffer.push_back('\0');

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
}

std::map<int, ActorDescriptionPtr> ActorsDatabase::getActors() const
{
  return _actors;
}

}}
