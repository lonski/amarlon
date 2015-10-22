#ifndef RPG_DB_H
#define RPG_DB_H

#include <memory>
#include <vector>
#include <race.h>
#include <rpg_parser.h>

namespace amarlon {

class RpgDB
{
public:
  RpgDB();
  virtual ~RpgDB();

  const std::vector<RacePtr> getRaces() const;

  virtual bool load(const std::string& fn);

private:
  RpgParser _parser;
  std::vector<RacePtr> _races;

};

}

#endif // RPG_DB_H
