#include "idle.h"

namespace amarlon {

namespace state{

Idle::Idle()
{

}

FSMStateType Idle::getType() const
{
  return FSMStateType::IDLE;
}

int Idle::update(Ai*)
{
  return 0;
}

}}
