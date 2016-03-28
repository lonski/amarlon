#ifndef AI_STATE_TYPE
#define AI_STATE_TYPE

namespace amarlon {

enum class FSMStateType
{
  WANDERING            = 1,
  CAST_BUFF_SELF       = 2,
  MELEE_ATTACK         = 3,
  CAST_OFFENSIVE_SPELL = 4,
  ATTACK_RANGE         = 5,
  MOVE_TO_TARGET       = 6,
  EVADING              = 7,
  HEAL                 = 8,
  IDLE                 = 9,
  PLAYER_CONTROLLED    = 10,
  END
};

inline FSMStateType operator++(FSMStateType& x) { return x = (FSMStateType)(std::underlying_type<FSMStateType>::type(x) + 1); }
inline FSMStateType operator*(FSMStateType c) {return c;}
inline FSMStateType begin(FSMStateType) {return FSMStateType::WANDERING;}
inline FSMStateType end(FSMStateType)   {return FSMStateType::END;}

}

#endif // AI_STATE_TYPE

