#ifndef RPG_DB_H
#define RPG_DB_H

#include <memory>
#include <vector>
#include <race.h>
#include <character_class.h>
#include <rpg_parser.h>

namespace amarlon {

class RpgDB
{
public:
  RpgDB();
  ~RpgDB();

  const std::vector<RacePtr> getRaces() const;
  RacePtr getRace(RaceType id) const;

  const std::vector<CharacterClassPtr> getCharacterClasses() const;
  CharacterClassPtr getCharacterClass(CharacterClassType id) const;

  bool load(const std::string& fn);

private:
  RpgParser _parser;
  std::vector<RacePtr> _races;
  std::vector<CharacterClassPtr> _classes;

};

}

#endif // RPG_DB_H
