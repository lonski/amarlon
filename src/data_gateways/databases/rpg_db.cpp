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
    }

    return true;
  }
  return false;
}

}
