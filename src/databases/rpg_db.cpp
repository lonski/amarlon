#include "rpg_db.h"
#include <fstream>

namespace amarlon {

RpgDB::RpgDB()
{
}

RpgDB::~RpgDB()
{
}

const std::vector<RacePtr> RpgDB::getRaces() const
{
  return _races;
}

RacePtr RpgDB::getRace(RaceType id) const
{
  auto it = std::find_if(_races.begin(), _races.end(), [&id](RacePtr r){
    return r->getType() == id;
  });

  return it != _races.end() ? (*it)->clone() : nullptr;
}

const std::vector<CharacterClassPtr> RpgDB::getCharacterClasses() const
{
  return _classes;
}

CharacterClassPtr RpgDB::getCharacterClass(CharacterClassType id) const
{
  auto it = std::find_if(_classes.begin(), _classes.end(), [&id](CharacterClassPtr c){
    return c->getType() == id;
  });

  return it != _classes.end() ? (*it)->clone() : nullptr;
}

bool RpgDB::load(const std::string &fn)
{
  std::ifstream ifs(fn);

  if (ifs.is_open())
  {
    std::vector<char> buf;
    buf.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    buf.push_back('\0');

    rapidxml::xml_document<> doc;
    doc.parse<0>(&buf[0]);

    rapidxml::xml_node<>* root = doc.first_node("Rpg");
    if ( root != nullptr )
    {
      _parser.setSource( root );
      _races = _parser.parseRaces();
      _classes = _parser.parseCharacterClasses();
    }

    return true;
  }
  return false;
}

}
