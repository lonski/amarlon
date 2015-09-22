#include "character_factory.h"
#include <monster.h>
#include <playable_character.h>

namespace amarlon {

CharacterFactory::CharacterFactory()
{
  _creators.push_back( std::make_shared<Monster::Creator>() );
  _creators.push_back( std::make_shared<PlayableCharacter::Creator>() );
}

CharacterPtr CharacterFactory::produce(CharacterDescriptionPtr dsc)
{
  CharacterPtr c = nullptr;

  if ( dsc != nullptr )
  {
    for ( auto creator : _creators )
    {
      c = creator->create(dsc);
      if ( c != nullptr ) break;
    }
  }

  return c;
}

}

