#ifndef ACTOR_ACTION_RESULT
#define ACTOR_ACTION_RESULT

namespace amarlon {

enum class ActorActionResult
{
  Ok,
  Nok,
  AlreadyEquiped,
  NoProperSlot,
  IncorrectTarget,
  ItemsMissing,
  InventoryFull,
  NotEquipped,
  SlotBlocked,
  InvalidObject,
  MissingAI,
  CursedItem
};

}
#endif // ACTOR_ACTION_RESULT

