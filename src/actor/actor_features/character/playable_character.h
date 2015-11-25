#ifndef PLAYABLE_CHARACTER_H
#define PLAYABLE_CHARACTER_H

#include <character.h>

namespace amarlon {

struct LevelData;

class PlayableCharacter : public Character
{
public:

  PlayableCharacter();
  PlayableCharacter(DescriptionPtr dsc);
  virtual DescriptionPtr toDescriptionStruct(ActorFeaturePtr cmp = nullptr);
  ~PlayableCharacter();

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

  /* overriden functions */
  virtual int modifyExperience(int modifier);

  /* class specific functions */
  virtual void advanceLevel();

private:
  void advanceLevel(LevelData data);

};

typedef std::shared_ptr<PlayableCharacter> PlayableCharacterPtr;

}

#endif // PLAYABLE_CHARACTER_H
