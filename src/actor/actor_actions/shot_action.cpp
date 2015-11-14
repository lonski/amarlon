#include "shot_action.h"
#include <actor.h>
#include <dices.h>
#include <direct_path.h>
#include <map.h>
#include <console_utils.h>
#include <engine.h>
#include <chrono>
#include <thread>

namespace amarlon {

ShotAction::ShotAction(ActorPtr target)
  : _target(target)
{
}

ShotAction::~ShotAction()
{
}

bool ShotAction::perform(ActorPtr performer)
{
  _performer = performer;
  MapPtr map = _performer->getMap();
  bool success = false;

  if ( isTargetCorrect() && isReadyToShot() && map )
  {
    success = true;
    ActorPtr missile = pickOneMissile();
    DirectPathPtr path = calculatePath();

    while ( !path->isEmpty() )
    {
      Point currentPoint = path->walk();
      Point previousPoint = path->previous();

      renderMissile(previousPoint, currentPoint, missile);
      std::this_thread::sleep_for(std::chrono::milliseconds(40));

      if ( currentPoint.isNonZero() && map->isBlocked(currentPoint)  ) //obstacle on the path
      {
        ActorPtr hitActor = getTarget(currentPoint);
        if ( hitActor )
        {
          if ( rangeAttack(hitActor) )
          {
            tryDropMissile(missile, currentPoint);
            break;
          }
        }
        else
        {
          tryDropMissile(missile, previousPoint );
          break;
        }
      }
    }
  }

  return success;
}

bool ShotAction::rangeAttack(ActorPtr actor)
{
  bool hit = false;
  int dieRoll = dices::roll( dices::D20 );

  if ( dieRoll != dices::NATURAL_ONE ) //natural one is always a failure
  {
    CharacterPtr attacker = _performer->getFeature<Character>();
    CharacterPtr attacked = actor->getFeature<Character>();

    int attackRoll = dieRoll +
                     attacker->getMissileAttackBonus() +
                     calculateAttackBonusModifier();

    if ( ( dieRoll == dices::NATURAL_TWENTY ) || //natural 20 is always a hit
         ( attackRoll >= attacked->getArmorClass()) ) //hit success
    {
      hit = true;
      attacked->takeDamage(attacker->getDamage(), _performer);
    }
  }

  if ( !hit )
  {
    actor->notify(Event(EventId::Actor_Dodged,{{"attacker",_performer->getName()}}));
  }

  return hit;
}

void ShotAction::renderMissile(const Point& prev, const Point& current, ActorPtr missile)
{
  Engine::instance().render();
  setTile(current, missile->getSymbol(), missile->getColor());
  TCODConsole::root->flush();
}

ActorPtr ShotAction::getTarget(const Point& p)
{
  MapPtr map = _performer->getMap();
  auto actors = map->getActors(p,[](ActorPtr a){
      return a->isAlive();
  });
  return actors.empty() ? nullptr : actors.front();
}

void ShotAction::tryDropMissile(ActorPtr missile, const Point &p)
{
  if ( p.isNonZero() &&
       missile       &&
       dices::roll(dices::D100) > 50 ) //50% to destroy the missile
  {
    MapPtr map = _performer->getMap();
    missile->setPosition(p);
    map->addActor(missile);
  }
}

ActorPtr ShotAction::pickOneMissile()
{
  return getAmunition()->spilt(1);
}

DirectPathPtr ShotAction::calculatePath()
{
  DirectPathPtr path(new DirectPath( _performer->getMap() ) );

  path->compute(_performer->getX(), _performer->getY(),
                _target->getX(), _target->getY(), true);

  return path;
}

int ShotAction::calculateAttackBonusModifier()
{
  const int CLOSE_RANGE = 2;

  enum ModifierByRange
  {
    CLOSE  = -5,
    SHORT  = 1,
    MEDIUM = 0,
    LONG   = -2
  };

  int modifier = CLOSE;

  int distance = calculateDistance(_performer, _target);
  if ( distance > CLOSE_RANGE )
  {
    float relativeDistance = distance / getWeapon()->getRange();

    if ( relativeDistance < 0.5 )
      modifier = SHORT;
    else if ( relativeDistance > 1.5 )
      modifier = LONG;
    else
      modifier = MEDIUM;
  }

  return modifier;
}

bool ShotAction::isTargetCorrect()
{
  if ( _performer && _target )
  {
    CharacterPtr attacker = _performer->getFeature<Character>();
    CharacterPtr attacked = _target->getFeature<Character>();

    return attacker && attacked && attacker != attacked;
  }
  return false;
}

bool ShotAction::isReadyToShot()
{
  PickablePtr weapon = getWeapon();
  PickablePtr amunition = getAmunition();

  return weapon    &&
         amunition &&
         amunition->getAmount() > 0 &&
         amunition->getItemType().amunition == weapon->getItemType().amunition;
}

PickablePtr ShotAction::getWeapon()
{
  WearerPtr wearer = _performer->getFeature<Wearer>();
  ActorPtr weaponActor = wearer->equipped( ItemSlotType::MainHand );
  return weaponActor ? weaponActor->getFeature<Pickable>() : nullptr;
}

PickablePtr ShotAction::getAmunition()
{
  WearerPtr wearer = _performer->getFeature<Wearer>();
  ActorPtr amunitionActor = wearer->equipped( ItemSlotType::Amunition );
  return amunitionActor ? amunitionActor->getFeature<Pickable>() : nullptr;
}

ActorActionUPtr ShotAction::clone()
{
  ShotActionUPtr cloned = std::make_unique<ShotAction>(_target);
  cloned->_performer = _performer;

  return std::move(cloned);
}

}

