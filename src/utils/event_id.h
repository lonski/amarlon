#ifndef EVENT_ID
#define EVENT_ID

namespace amarlon {

enum class EventId
{
  Null,
  Actor_Died,
  Actor_GotHit,
  Actor_ReceivedDamage,
  Actor_ExperienceGained,
  Actor_ExperienceLost,
  Actor_LeveledUp,
  Actor_Missed,
  Actor_Pick,
  Actor_Drop,
  Actor_Healed,
  Actor_Locked,
  Actor_Unlocked,
  Actor_Put,
  Player_Look_At,
  Actor_EffectAdded,
  Actor_EffectRemoved,
  Actor_DodgedTrap,
  Actor_TriggeredTrap,
  TrapDisarmed,
  TrapArmed,
  Actor_Hidden,
  Actor_CancelHidden,
  Item_Removed,
  Item_Added,
  Actor_Dodged

};

}

#endif // EVENT_ID

