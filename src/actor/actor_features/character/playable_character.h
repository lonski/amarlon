#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#include <character.h>

namespace amarlon {

struct LevelData;

class PlayableCharacter : public Character
{
public:

  PlayableCharacter();
  PlayableCharacter(const PlayableCharacter& rhs);

  ~PlayableCharacter();

  /* overriden functions */
  virtual int modifyExperience(int modifier);

  /* class specific functions */
  virtual void advanceLevel();

protected:
  friend class Character;
  PlayableCharacter(const CharacterData& data);

private:
  void advanceLevel(LevelData data);

};

typedef std::shared_ptr<PlayableCharacter> PlayableCharacterPtr;

}

#endif // PLAYABLE_CHARACTER_H
