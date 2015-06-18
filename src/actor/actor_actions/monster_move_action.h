#ifndef MONSTER_MOVE_ACTION_H
#define MONSTER_MOVE_ACTION_H

#include <move_action.h>

namespace amarlon {

class Character;
typedef std::shared_ptr<Character> CharacterPtr;

class MonsterMoveAction : public MoveAction
{
public:
  MonsterMoveAction(int dx, int dy);
  virtual ~MonsterMoveAction();

  virtual bool perform(ActorPtr performer);
  virtual ActorActionUPtr clone();

private:
  int _moveCost;
  int _currentMovePoints;

  bool doMove(CharacterPtr mob);
  void calculateMovePoints(CharacterPtr mob);

};

typedef std::shared_ptr<MonsterMoveAction> MonsterMoveActionPtr;
typedef std::unique_ptr<MonsterMoveAction> MonsterMoveActionUPtr;

}

#endif // MONSTER_MOVE_ACTION_H
