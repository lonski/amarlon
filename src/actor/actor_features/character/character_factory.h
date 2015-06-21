#ifndef CHARACTER_FACTORY_H
#define CHARACTER_FACTORY_H

#include <memory>
#include <vector>
#include <character.h>

namespace amarlon{

class CharacterFactory
{
public:
  CharacterFactory();
  CharacterPtr produce(CharacterDescriptionPtr dsc);

private:
  std::vector< std::shared_ptr<Character::Creator> > _creators;

};

}

#endif // CHARACTER_FACTORY_H
